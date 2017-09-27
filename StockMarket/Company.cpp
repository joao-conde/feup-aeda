#include "Company.h"


Company::Company(string name, string activity, nif_t NIF, double max_transaction) : 
	name(name), business_area(activity), NIF(NIF), max_transaction_value(max_transaction){}

Company::Company(ifstream& in) {
	
	string s;

	// Extract Company Name
	getline(in, s, ';'); trim(s);
	name = s;

	// Extract Company business area
	getline(in, s, ';'); trim(s);
	business_area = s;

	// Extract Company NIF
	getline(in, s, ';'); 
	NIF = stoi(s);

	// Extract highest value transactionned
	getline(in, s, '\n');
	max_transaction_value = stoi(s);

}

void Company::saveChanges(ofstream& out) const {
	out << name << " ; " << business_area << " ; " << NIF << " ; " << max_transaction_value << endl;
}





ostream& operator<<(ostream& out, const Company& c) {
	out << c.name << c.business_area << c.NIF << c.max_transaction_value << endl;
	return out;
}