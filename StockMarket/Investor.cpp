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


ostream& operator<<(ostream& out, const Investor &i) {
	out << TAB << i.name << ", " << i.phone << ", " << i.maxInvestment << ", " << i.availableBudget << endl;
	return out;
}

bool operator<(const Investor &i1, const Investor &i2) {

	if (i1.availableBudget < i2.availableBudget)
		return true;
	else return false;

	return true;
}