#include "Investor.h"


Investor::Investor(ifstream& in) {
	string s;

	// Extract Investor name
	getline(in, s, ';'); trim(s);
	name = s;

	// Extract Investor contact
	getline(in, s, ';');
	phone = stoi(s);

	// Extract Investor value of max investment
	getline(in, s, ';');
	maxInvestment = stoi(s);

	// Extract Investor budget
	getline(in, s, '\n');
	availableBudget = stoi(s);
}

Investor::Investor(string name, tlmv_t phone, double maxInvest, double budget) : name(name),
phone(phone), maxInvestment(maxInvest), availableBudget(budget){}

double Investor::getBudget() const{
	return availableBudget;
}

double Investor::getMaxInv() const{
	return maxInvestment;
}

tlmv_t Investor::getPhoneNumber() const {
	return phone;
}

void Investor::debitInvest(double value) {
	availableBudget -= value;
}

void Investor::addBudget(double loan) {
	availableBudget += loan;
}

void Investor::updatePhoneN(tlmv_t phone) {
	this->phone = phone;
}


ostream& operator<<(ostream& out, const Investor &i) {
	out << TAB << setw(10) << i.name << TAB << "Phone number: " << setw(10) << i.phone << TAB << "Highest Investment Value Possible: " << i.maxInvestment << TAB << "Available Budget: " << i.availableBudget << endl;
	return out;
}

bool operator==(const Investor &i1, const Investor &i2) {
	
	if (i1.name == i2.name)
		if (i1.phone == i2.phone)
			return true;

	return false;
}

bool operator<(const Investor &i1, const Investor &i2) {

	if (i1.availableBudget > i2.availableBudget)
		return true;
	else return false;

	return true;
}