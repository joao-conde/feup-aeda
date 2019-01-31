#include <iomanip>
#include "Order.h"
#include "utils.h"

/* Order Implementation */
Order::Order(ifstream & in) {
	char dummy;
	getline(in, stock, ';'); trim(stock);
	in >> valuePerStock >> dummy;
	in >> quantity >> dummy;
	in >> datePlaced >> dummy;
}

Order::Order(string stock, double value, unsigned quantity) : stock(stock), quantity(quantity)
{
	if (value > 0)
		this->valuePerStock = value;
	else
		throw InvalidValue(value);
}

Date Order::getDatePlaced() const {
	return datePlaced;
}

string Order::getStock() const {
	return stock;
}

double Order::getValue() const {
	return valuePerStock;
}

unsigned Order::getQuantity() const {
	return quantity;
}

void Order::saveChanges(ofstream & out) const {
	out << stock << " ; " << valuePerStock << " ; " << quantity << " ; " << datePlaced << " ; ";
}

void Order::printInfo() const {
	cout << "Stock: " << setw(15) << stock << ". Quantity: " << setw(5) << quantity << ". Price per stock: " << setw(5) << valuePerStock << ". Date placed: " << datePlaced << ".\n";
}
/// ///

/* BuyOrder Implementation */
BuyOrder::BuyOrder(ifstream & in) : Order(in) {
	in >> buyerNIF; in.ignore(3, '\n');
}

BuyOrder::BuyOrder(string stock, double val, unsigned quantity, nif_t buyerNIF) : Order(stock, val, quantity), buyerNIF(buyerNIF) {}

nif_t BuyOrder::getClientNIF() const {
	return buyerNIF;
}

Transaction * BuyOrder::operator()(Order* ord) {
	SellOrder * sellOrd = NULL;

	if (ord->getStock() == this->stock && ord->getValue() <= this->valuePerStock && (sellOrd = dynamic_cast<SellOrder*>(ord)) != NULL) {
		double effectiveVal = (this->valuePerStock + sellOrd->valuePerStock) / 2;
		unsigned effectiveQuant = quantity < sellOrd->quantity ? quantity : sellOrd->quantity;

		Transaction * result = new Transaction(sellOrd->sellerNIF, buyerNIF, stock, effectiveVal, effectiveQuant);

		quantity -= effectiveQuant;
		sellOrd->quantity -= effectiveQuant;

		return result;
	}
	else
		return NULL;
}

void BuyOrder::saveChanges(ofstream & out) const {
	out << "B ";
	Order::saveChanges(out);
	out << buyerNIF << endl;
}

/// ///

/* SellOrder Implementation */
SellOrder::SellOrder(ifstream & in) : Order(in) {
	in >> sellerNIF; in.ignore(3, '\n');
}

SellOrder::SellOrder(string stock, double val, unsigned quantity, nif_t sellerNIF) : Order(stock, val, quantity), sellerNIF(sellerNIF) {}

nif_t SellOrder::getClientNIF() const {
	return sellerNIF;
}

Transaction * SellOrder::operator()(Order* ord) {
	BuyOrder * buyOrd = NULL;

	if (ord->getStock() == this->stock && ord->getValue() >= this->valuePerStock && (buyOrd = dynamic_cast<BuyOrder*>(ord)) != NULL) {
		double effectiveVal = (this->valuePerStock + buyOrd->valuePerStock) / 2;
		unsigned effectiveQuant = quantity < buyOrd->quantity ? quantity : buyOrd->quantity;

		Transaction * result = new Transaction(buyOrd->buyerNIF, sellerNIF, stock, effectiveVal, effectiveQuant);

		quantity -= effectiveQuant;
		buyOrd->quantity -= effectiveQuant;

		return result;
	}
	else
		return NULL;
}

void SellOrder::saveChanges(ofstream & out) const {
	out << "S ";
	Order::saveChanges(out);
	out << sellerNIF << endl;
}
/// ///