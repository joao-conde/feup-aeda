#include <iomanip>
#include "Transaction.h"
#include "utils.h"
#include "defs.h"

Transaction::Transaction(nif_t buyerNIF, nif_t sellerNIF, string stock, double value, unsigned quantity) :
	sellerNIF(sellerNIF), buyerNIF(buyerNIF), stock(stock), value(value), quantity(quantity) {}

// Constructs Transaction from Input FileStream
Transaction::Transaction(ifstream& in) {
	string s;
	
	// Extract Stock Name
	getline(in, s, ';'); trim(s);
	stock = s;

	// Extract Clients' NIFs
	in.ignore(5, 'S'); // Extract 'S' (Seller)
	in >> sellerNIF;
	in.ignore(5, 'B'); // Extract 'B' (Buyer)
	in >> buyerNIF;
	in.ignore(5, ';');

	// Extract Value
	in >> value;
	in.ignore(5, ';');

	// Extract Quantity
	in >> quantity;
	in.ignore(5, ';');

	// Extract Date
	in >> time_stamp;
	in.ignore(5, '\n');
}

void Transaction::saveChanges(ofstream & out) const {
	out << stock << " ; " << 'S' << sellerNIF << " ; " << 'B' << buyerNIF << " ; "
		<< value << " ; " << quantity << " ; " << time_stamp << endl;
}

string Transaction::getStock() const {
	return stock;
}

double Transaction::getValue() const {
	return value;
}

nif_t Transaction::getBuyerNIF() const {
	return buyerNIF;
}

nif_t Transaction::getSellerNIF() const {
	return sellerNIF;
}

unsigned Transaction::getQuantity() const {
	return quantity;
}

Date Transaction::getDate() const {
	return time_stamp;
}

ostream& operator<<(ostream & out, const Transaction & t) {
	out << t.time_stamp << " -- Transactioned " << setw(3) << t.quantity << " stocks of " << t.stock << " at " << t.value << " each." << endl;
	return out;
}