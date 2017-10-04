#include <algorithm>
#include "Market.h"
#include "defs.h"
#include "menus.h"
#include "utils.h"


Market* Market::singleton_instance = NULL;

Market::Market() : currentNIF(0) {
	ifstream file_in; string line;
	unsigned numberOfObjects;
	ordersChanged = transactionsChanged = clientsChanged = companysChanged = false;

	while (!initialInfo(clientsFile, transactionsFile, ordersFile, companysFile, investorsFile)) {
		cout << "\nInvalid StockMarket Initialization ! Carefully type the information required! \a\n\n";
		cout << TAB << "\n Press ENTER to retry..."; cin.ignore(INT_MAX, '\n');
		clearScreen();
	}

	/* Populate Data Structures */
	// Clients from file
	file_in.open(clientsFile);
	file_in >> numberOfObjects; file_in.ignore(3, '\n');
	for (unsigned i = 0; i < numberOfObjects; ++i) {
		Client * temp_c = new Client(file_in);
		clients.insert(pair<nif_t, Client*>(temp_c->getNIF(), temp_c));
	}
	file_in.close();

	// Transactions from file
	file_in.open(transactionsFile);
	file_in >> numberOfObjects; file_in.ignore(3, '\n');
	transactions.reserve(numberOfObjects);
	for (unsigned i = 0; i < numberOfObjects; ++i) {
		Transaction * temp_t = new Transaction(file_in);
		transactions.push_back(temp_t);
	}
	file_in.close();
	
	// Sort transactions by chronological order
	sort(transactions.begin(), transactions.end(), [](const Transaction * t1, const Transaction * t2) {return t1->getDate() < t2->getDate(); });

	// Unfulfilled Orders from file
	char c;	// Buy/Sell Char Flag
	file_in.open(ordersFile);
	file_in >> numberOfObjects; file_in.ignore(3, '\n');
	transactions.reserve(numberOfObjects);
	for (unsigned i = 0; i < numberOfObjects; ++i) {
		Order * temp_o;
		file_in >> c;
		switch (c) {
		case 'B':
			temp_o = new BuyOrder(file_in);
			break;
		case 'S':
			temp_o = new SellOrder(file_in);
			break;
		default:
			cerr << "Invalid Order Identifier in File \"" << ordersFile << "\".\n";
			break;
		}
		unfulfilled_orders.push_back(temp_o);
	}
	file_in.close();

	// Sort unfulfilled orders by chronological order
	sort(unfulfilled_orders.begin(), unfulfilled_orders.end(), [](const Order * o1, const Order * o2) {return o1->getDatePlaced() < o2->getDatePlaced(); });

	// Load Companys fom file
	file_in.open(companysFile);
	file_in >> numberOfObjects; file_in.ignore(3, '\n');

	for (unsigned i = 0; i < numberOfObjects; ++i) {
		companys.insert(Company(file_in));
	}

	file_in.close();

	// Load Investors from file
	file_in.open(investorsFile);
	file_in >> numberOfObjects; file_in.ignore(3, '\n');

	for (unsigned int i = 0; i < numberOfObjects; i++) {
		investors.push(Investor(file_in));
	}

	file_in.close();
}

Market::~Market() {
	// Warning: Do Not delete from files

	// Delete Clients from Memory
	for (auto p : clients)
		delete p.second;

	// Delete Transactions from Memory
	for (Transaction * t : transactions)
		delete t;

	// Delete Orders from Memory
	for (Order * o : unfulfilled_orders)
		delete o;
}

Market* Market::instance() {
	if (!singleton_instance)
		singleton_instance = new Market;

	return singleton_instance;
}

bool Market::signIn(string name, nif_t nif) {
	for (auto it = clients.begin(); it != clients.end(); ++it) {
		if ((it->first == nif) && ((it->second)->getName() == name)) {
			currentNIF = nif;
			return true;
		}
	}
	return false;
}

void Market::signOut() {
	currentNIF = 0;
}

bool Market::signUp(string name, nif_t nif) {
	// acrescentar cliente ao map (nif, client*) e mudar currentNIF etc
	Client * newClient = new Client(name, nif);
	auto p = clients.insert(pair<nif_t, Client *>(nif, newClient));
	
	if (false == p.second) { // Clients with the same name can exist, but not with the same NIF
		//cout << endl << TAB << "Account already exists. Are you " << p.first->second->getName() << " ?\n";
		return false;
	}

	currentNIF = nif;
	clientsChanged = true;
	cout << endl << TAB << "New Client created sucessfully!\n";	// Needs to be done here because of the try catch thing
	return true;
}

nif_t Market::getCurrentNIF() const {
	return currentNIF;
}

// Can throw exception, should be handled by higher function
void Market::showClientInfo() const {
	Client * cli = clients.at(currentNIF);

	cout << *cli << endl;
}

// Can throw exception, should be handled by higher function
void Market::showClientHistory() const {
	Client * cli = clients.at(currentNIF);
	for (Transaction * t_ptr : clientHistory(cli))
		cout << *t_ptr;
}

void Market::showClientOrders() const {
	for (unsigned i = 0, j = 0; i < unfulfilled_orders.size(); ++i) {
		if (unfulfilled_orders[i]->getClientNIF() == currentNIF) {
			cout << ++j << ". " << (dynamic_cast<BuyOrder*>(unfulfilled_orders[i]) != NULL ? "Buy Order  -> " : "Sell Order -> ");
			unfulfilled_orders[i]->printInfo();
		}
	}
}

bool Market::eraseClientOrder(unsigned choice) {
	vector<Order *> clientOrders(unfulfilled_orders.size());
	auto it = copy_if(unfulfilled_orders.begin(), unfulfilled_orders.end(), clientOrders.begin(), [=](Order * o) { return o->getClientNIF() == currentNIF; });
	clientOrders.resize(distance(clientOrders.begin(), it));

	if (choice > clientOrders.size())
		return false;

	for (unsigned i = 0; i < unfulfilled_orders.size(); ++i) {
		if (unfulfilled_orders[i] == clientOrders[choice - 1]) {
			delete unfulfilled_orders[i];
			unfulfilled_orders.erase(unfulfilled_orders.begin() + i);
			ordersChanged = true;
			return true;
		}
	}

	return false;
}

vector<Transaction *> Market::clientHistory(Client * c_ptr) const {
	vector<Transaction *> result;
	for (Transaction * t_ptr : transactions) {
		if (t_ptr->getBuyerNIF() == c_ptr->getNIF() || t_ptr->getSellerNIF() == c_ptr->getNIF())
			result.push_back(t_ptr);
	}

	return result;
}

void Market::printTransactions() const {
	for (Transaction * t : transactions) {
		cout << *t;
	}
}

void Market::printTransactions(string stock) const {
	for (Transaction * t : transactions) {
		if (t->getStock() == stock)
			cout << *t;
	}
}

void Market::printTransactions(Date day1, Date day2) const {
	for (size_t i = 0; i < transactions.size(); ++i) {
		if (day1 <= transactions.at(i)->getDate() && transactions.at(i)->getDate() <= day2)
			cout << *transactions.at(i);
	}
}

void Market::printTransactions(Date d) const {

	for (size_t i = 0; i < transactions.size(); i++) {
		if (transactions.at(i)->getDate() == d)
			cout << *transactions.at(i);
	}
}

void Market::listBuyOrders() const {
	for (Order * ptr : unfulfilled_orders) {
		if (dynamic_cast<BuyOrder*>(ptr) != NULL)
			ptr->printInfo();
	}
}

void Market::listSellOrders() const {
	for (Order * ptr : unfulfilled_orders) {
		if (dynamic_cast<SellOrder*>(ptr) != NULL)
			ptr->printInfo();
	}
}

void Market::listCompanys() const {
	for (Company c: companys) {
		cout << c;
	}
}

void Market::listCompanys(string business) const {
	for (Company c : companys) {
		if (c.getArea() == business)
			cout << c;
	}
}

void Market::insertCompany(Company c) {
	
	auto ret = companys.insert(c);
	
	if (ret.second)
		companysChanged = true;
	else
		cout << TAB << "Failed insertion. Company already exists." << endl;

}

void Market::deleteCompany(string name) {
	
	for (auto o : companys) {
		if (o.getName() == name) {
			companys.erase(o);
			companysChanged = true;
			break;
		}
	}
	
}

void Market::changeCompany(string name, double value) {
	
	for (auto c : companys) {
		if (c.getName() == name) {
			if (value > c.getValue()) {
				Company newcomp = c;
				newcomp.setValue(value);
				deleteCompany(name); 
				insertCompany(newcomp);
				companysChanged = true;
				break;
			}
			else
				cout << TAB << "Invalid value. Smaller than the already existant." << endl;
		} 
	}
}



// Returns pair< vector<Transaction *>::iterator, vector<Transaction *>::iterator >
pair< vector<Transaction *>::iterator, vector<Transaction *>::iterator > Market::placeOrder(Order * ptr)
{
	typedef vector<Transaction *>::iterator transIt;
	size_t initialSize = transactions.size();
	unfulfilled_orders.push_back(ptr);

	for (unsigned i = 0; i < unfulfilled_orders.size(); i++) {
		Transaction * trans;
		if ((trans = (*unfulfilled_orders[i])(ptr)) != NULL) {	// Transaction Successful ?
			transactions.push_back(trans);
			
			// Corresponding Buy/Sell Order Fulfilled ?
			if (unfulfilled_orders[i]->getQuantity() == 0) {
				delete unfulfilled_orders[i];
				unfulfilled_orders.erase(unfulfilled_orders.begin() + i--);
			}
			if (0 == ptr->getQuantity()) {
				delete ptr;
				unfulfilled_orders.pop_back();
				break;
			}
		}
	}
	ordersChanged = true;
	if (transactions.size() > initialSize) {
		transactionsChanged = true;
		return pair<transIt, transIt>(transactions.begin() + initialSize, transactions.end());
	}

	return pair<transIt, transIt> (transactions.end(), transactions.end());
}

void Market::saveChanges() const {
	ofstream out;

	// Save Clients if Changed
	if (clientsChanged) {
		out.open(clientsFile);
		out << clients.size() << endl;

		for (auto p : clients)
			p.second->saveChanges(out);

		out.close();
	}

	// Save Transactions if Changed
	if (transactionsChanged) {
		out.open(transactionsFile);
		out << transactions.size() << endl;

		for (Transaction * ptr : transactions)
			ptr->saveChanges(out);

		out.close();
	}

	// Save Orders if Changed
	if (ordersChanged) {
		out.open(ordersFile);
		out << unfulfilled_orders.size() << endl;

		for (Order * ptr : unfulfilled_orders)
			ptr->saveChanges(out);

		out.close();
	}

	//Save Companys if changed
	if (companysChanged) {
		out.open(companysFile);
		out << companys.size() << endl;

		for (Company comp : companys)
			comp.saveChanges(out);

		out.close();
	}
}


ostream& operator<<(ostream & out, const Market & m) {

	size_t n_clients = m.clients.size();
	size_t n_trans = m.transactions.size();
	size_t n_orders = m.unfulfilled_orders.size();
	size_t n_buyOrders = 0, n_sellOrders = 0;

	double average_trans = 0, trans_total = 0;

	map<string, int> stock_occur;
	string most_requested;

	for (size_t i = 0; i < m.unfulfilled_orders.size(); i++) {

		if (dynamic_cast<BuyOrder*>(m.unfulfilled_orders.at(i)) == NULL)
			n_sellOrders++;
		else
			n_buyOrders++;
	}


	for (size_t j = 0; j < m.transactions.size(); j++) {
		trans_total += m.transactions.at(j)->getQuantity() * m.transactions.at(j)->getValue();

		map<string, int>::iterator it;
		it = stock_occur.find(m.transactions.at(j)->getStock());

		if (it == stock_occur.end())
			stock_occur.insert(pair<string, int>(m.transactions.at(j)->getStock(), 1));
		else {
			stock_occur[m.transactions.at(j)->getStock()] = stock_occur[m.transactions.at(j)->getStock()] + 1;
		}

	}

	average_trans = trans_total / n_trans;

	int ocurr = 0;
	map<string, int>::iterator it;
	it = stock_occur.begin();

	while (it != stock_occur.end()) {
		if (it->second > ocurr)
			most_requested = it->first;
		it++;
	}

	clearScreen();
	showTitle("MARKET'S STATISTICS", cout);
	cout << TAB << "Number of clients: " << n_clients << endl
		<< TAB << "Number of transactions: " << n_trans << endl
		<< TAB << "Number of orders: " << n_orders << endl
		<< TAB << "Number of buy orders: " << n_buyOrders << endl
		<< TAB << "Number of sell orders: " << n_sellOrders << endl
		<< TAB << "Average value of transaction: " << average_trans << endl
		<< TAB << "Most transactioned stock: " << most_requested << endl << endl;

	return out;
}