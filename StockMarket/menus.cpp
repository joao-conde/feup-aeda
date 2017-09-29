#include <iomanip>
#include "Market.h"
#include "menus.h"
#include "utils.h"


bool initialInfo(string & clientsFile, string & transactionsFile, string & ordersFile, string & companysFile) {
	cout << TAB_BIG; showTitle("Stock Market");
	cout << "\n Type the name of the files where information is stored (FileName.txt): \n" << endl;
	cout << setw(21) << "Clients' file: "; setcolor(14); cin >> clientsFile;
	setcolor(15); cin.ignore(INT_MAX, '\n'); // clear the end-of-line character from the cin stream buffer

	cout << setw(21) << "Transactions' file: "; setcolor(14); cin >> transactionsFile;
	setcolor(15); cin.ignore(INT_MAX, '\n');

	cout << setw(21) << "Orders' file: "; setcolor(14); cin >> ordersFile;
	setcolor(15); cin.ignore(INT_MAX, '\n');	

	cout << setw(21) << "Companys' file: "; setcolor(14); cin >> companysFile;
	setcolor(15); cin.ignore(INT_MAX, '\n');

	return (validFile(clientsFile) && validFile(transactionsFile) && validFile(ordersFile) && validFile(companysFile) 
		&& !cin.fail());
}

/******************************************
 * Gestao de Clientes
 ******************************************/
unsigned short int clientOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Client Menu");
	cout << TAB << "1 - Show Information" << endl;
	cout << TAB << "2 - Show Transaction History" << endl;
	cout << TAB << "3 - Show unfulfilled Orders" << endl;
	cout << TAB << "4 - Delete a unfullfilled Order" << endl;
	cout << TAB << "5 - Exit menu" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 5, msg);

	if (option == 5)
		return false;	// false == 0

	return option;
}

void clientMenu() {
	unsigned short int option;
	cout << endl;

	while ((option = clientOptions())) {
		switch (option) {
		case 1: //Show Info
			Market::instance()->showClientInfo();
			break;
		case 2: //Show Client History
			cout << endl << TAB << "Client's transaction History:\n\n";
			Market::instance()->showClientHistory();
			break;
		case 3:
			cout << endl << TAB << "Client's unfulfilled Orders:\n";
			Market::instance()->showClientOrders();
			break;
		case 4:
			int choice;
			Market::instance()->showClientOrders();
			cout << endl << TAB << "Select the Order you wish to erase: (example: 1 for first, 2 for second,...)\n" << TAB << "Your option: ";
			cin >> choice; cin.ignore();

			if (Market::instance()->eraseClientOrder(choice))
				cout << TAB << "Order successfully erased!\n\n";
			else
				cout << TAB << "Failed to erase Order!\n\n";
			break;
		}
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
	}

	Market::instance()->saveChanges();
}


/******************************************
* Gestao de Transacoes
******************************************/
unsigned short int transactionOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Transactions Menu");
	cout << TAB << "1 - List ALL transactions" << endl;
	cout << TAB << "2 - List client's transactions" << endl;
	cout << TAB << "3 - List transactions of a specific Stock" << endl;
	cout << TAB << "4 - List transactions between 2 days" << endl;
	cout << TAB << "5 - List daily transactions " << endl;
	cout << TAB << "6 - Exit sub-menu" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 6, msg);

	if (option == 6)
		return false;	// false == 0

	return option;
}

void transactionMenu() {
	unsigned short int option; string str; Date d;
	cout << endl;

	while ((option = transactionOptions())) {
		switch (option) {
		case 1: //list all transactions
			cout << endl;
			Market::instance()->printTransactions();
			break;
		case 2: //list client's transactions
			cout << endl;
			Market::instance()->showClientHistory();
			break;
		case 3: //list transactions of a specific Stock
			cout << endl << TAB << setw(10) << "Stock: ";
			getline(cin, str); trim(str); cout << endl;
			Market::instance()->printTransactions(str);
			break;
		case 4: //list transactions between 2 days
			d = getDate("First day: "); cout << endl;
			Market::instance()->printTransactions(d, getDate("Last day: "));
			break;
		case 5: //list daily transactions
			cout << endl;
			Market::instance()->printTransactions(getDate("Transaction day: "));
			break;
		}
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
	}

	Market::instance()->saveChanges();
}


/******************************************
* Gestao de Empresas
******************************************/
unsigned short int companyOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Company Menu");
	cout << TAB << "1 - Show all market companys" << endl;
	cout << TAB << "2 - Show companys related to a business area" << endl;
	cout << TAB << "3 - Insert new company into market" << endl;
	cout << TAB << "4 - Delete an existing company from the market" << endl;
	cout << TAB << "5 - Change an existing company highest transaction value" << endl;
	cout << TAB << "6 - Exit menu" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 6, msg);

	if (option == 6)
		return false;	// false == 0

	return option;
}

void companyMenu() {
	unsigned short int option;
	cout << endl;

	while ((option = companyOptions())) {
		switch (option) {
		case 1: //Show Info
			Market::instance()->showClientInfo();
			break;
		case 2: //Show Client History
			cout << endl << TAB << "Client's transaction History:\n\n";
			Market::instance()->showClientHistory();
			break;
		case 3:
			cout << endl << TAB << "Client's unfulfilled Orders:\n";
			Market::instance()->showClientOrders();
			break;
		case 4:
			int choice;
			Market::instance()->showClientOrders();
			cout << endl << TAB << "Select the Order you wish to erase: (example: 1 for first, 2 for second,...)\n" << TAB << "Your option: ";
			cin >> choice; cin.ignore();

			if (Market::instance()->eraseClientOrder(choice))
				cout << TAB << "Order successfully erased!\n\n";
			else
				cout << TAB << "Failed to erase Order!\n\n";
			break;
		}
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
	}

	Market::instance()->saveChanges();
}




/******************************************
* Gestao de Ordens
******************************************/
unsigned short int orderOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Orders Menu");
	cout << TAB << "1 - List ALL buy orders" << endl;
	cout << TAB << "2 - List ALL sell orders" << endl;
	cout << TAB << "3 - Add buy order" << endl;
	cout << TAB << "4 - Add sell order" << endl;
	cout << TAB << "5 - Exit sub-menu" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 5, msg);

	if (option == 5)
		return false;	// false == 0

	return option;
}

void orderMenu() {
	unsigned short int option;
	string stock;
	double val;
	unsigned quantity;
	Order * newOrder;
	cout << endl;

	while ((option = orderOptions())) {
		switch (option) {
		case 1: //list all buy orders
			Market::instance()->listBuyOrders();
			break;
		case 2: //list all sell orders
			Market::instance()->listSellOrders();
			break;
		case 3: 
			cout << TAB << "Adding a new Buy Order...\n\n";
			setcolor(14); cout << TAB << setw(20) << "Stock: "; setcolor(15);
			getline(cin, stock); trim(stock);
			val = getValue<double>("Stock's value: ", 20);
			quantity = getValue<unsigned int>("Quantity: ", 20);

			newOrder = new BuyOrder(stock, val, quantity, Market::instance()->getCurrentNIF());
			addOrder(newOrder);
			break;
		case 4: 
			cout << TAB << "Adding a new Sell Order...\n\n";
			setcolor(14); cout << TAB << setw(20) << "Stock: "; setcolor(15);
			getline(cin, stock); trim(stock);
			val = getValue<double>("Stock's value: ", 20);
			quantity = getValue<unsigned int>("Quantity: ", 20);

			newOrder = new SellOrder(stock, val, quantity, Market::instance()->getCurrentNIF());
			addOrder(newOrder);
			break;
		}
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
	}

	Market::instance()->saveChanges();
}



/******************************************
* Menu Inicial
******************************************/
unsigned short int homeOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Home Menu");
	cout << TAB << "1 - Manage clients" << endl;
	cout << TAB << "2 - Manage transactions" << endl;
	cout << TAB << "3 - Manage orders" << endl;
	cout << TAB << "4 - Manage companys" << endl;
	cout << TAB << "5 - Statistic Information" << endl;
	cout << TAB << "6 - Sign Out" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 6, msg);
	cout << endl << endl;

	if (option == 6) {
		Market::instance()->signOut();
		return false;
	}

	return option;
}

void homeMenu() {
	unsigned int option;
	cout << endl;

	while ((option = homeOptions()))
		switch (option) {
		case 1: clientMenu();
			break;
		case 2: transactionMenu();
			break;
		case 3: orderMenu();
			break;
		case 4: companyMenu();
			break;
		case 5:
			cout << *(Market::instance());
			cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
			break;

		}

	Market::instance()->saveChanges();
}

/******************************************
* Menu de Inicialização
******************************************/
unsigned short int initialOptions() {
	unsigned short int option;

	clearScreen();
	showTitle("Initial Menu");
	cout << TAB << "1 - Sign In" << endl;
	cout << TAB << "2 - Sign Up" << endl;
	cout << TAB << "3 - Exit program" << endl << endl;
	string msg = TAB; msg += "Your option: ";
	option = getUnsignedShortInt(1, 3, msg);
	cout << endl << endl;

	if (option == 3) {
		setcolor(14);
		cout << TAB << "Thank you for using our software!\n" << TAB << "Developed by Andre Cruz, Edgar Carneiro and Joao Conde\n" << endl;
		setcolor(15);
		cout << endl << TAB << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
		return false;
	}

	return option;
}

void initialMenu() {
	unsigned int option;
	string name;
	nif_t nif;
	cout << endl;
	
	while ((option = initialOptions()))
		switch (option) {
		case 1:
			setcolor(14);
			cout << TAB << setw(10) << "Name: ";
			setcolor(15);
			getline(cin, name, '\n'); trim(name);
			nif = getValue<nif_t>("NIF: ", 10);

			if (Market::instance()->signIn(name, nif)) {
				cout << endl << TAB_BIG << "Signed In successfully!\n";
				cout << endl << TAB_BIG << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
				homeMenu();
			}
			else {
				cout << endl << TAB_BIG << "Sign In Unsuccessful.\n";
				cout << endl << TAB_BIG << "Press ENTER to continue..."; cin.ignore(INT_MAX, '\n');
			}
			break;
		case 2:
			cout << TAB << setw(10) << "Name: ";
			getline(cin, name); trim(name);
			nif = getValue<nif_t>("NIF: ", 10);
		
			try {
				Market::instance()->signUp(name,nif);
			}
			catch (Client::InvalidNIF & e) {
				cout << TAB <<"\nInvalidNIF: " << e.getNIF() << endl;
			}
			cout << TAB << "\nPress ENTER to continue..."; cin.ignore(INT_MAX, '\n');
			break;
		}

	Market::instance()->saveChanges();
}

/* Generic Helper Function for Handling New Orders */
void addOrder(Order * newOrder)
{
	unsigned originalQuantity = newOrder->getQuantity();
	auto result = Market::instance()->placeOrder(newOrder);

	bool fullfilled = true;
	unsigned transactioned = 0;
	for (auto it = result.first; it != result.second; ++it) {
		transactioned += (*it)->getQuantity();
	}

	cout << endl << TAB;
	if (0 == transactioned) {
		cout << "StockMarket was unable to fulfill your Order and was put on hold till compatible orders are found.\n\n";
		return;
	} else if (transactioned != originalQuantity) {
		cout
			<< "Your order was partially fullfilled. Waiting for more Buy Orders to completely fullfill it!\n"
			<< TAB << "Transactioned stocks: " << transactioned << ".\n\n\n";
	} else {
		cout << "Your order was instantly fullfilled!\n";
	}

	cout << TAB_BIG << "Transactions generated:\n\n";
	while (result.first != result.second)
		cout << TAB << *(*(result.first++));
}
