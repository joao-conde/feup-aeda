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


bool operator<(const Company &c1, const Company &c2) {
	
	//order alphabetically by bussiness area
	if (c1.business_area.compare(c2.business_area) < 0)
		return true;
	else
		if (c1.business_area.compare(c2.business_area) > 0)
			return false;


	//order alphabetically by company name (UNIQUE ID: no different companys with the same name)
	if (c1.name.compare(c2.name) < 0)
		return true;
	else
		if (c1.name.compare(c2.name) > 0)
			return false;
}