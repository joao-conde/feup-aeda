/*
 * Postman.h
 */

#ifndef SRC_POSTMAN_H_
#define SRC_POSTMAN_H_

#include "Mail.h"
#include "utils.h"
#include <string>
#include <vector>



class Postman {

	static unsigned int nextID;
	unsigned int id;
	string name;
	vector<Mail *> myMail;

public:
	Postman();
	Postman(string name);
	void setName(string nm);
	void addMail(Mail *m);
	void addMail(vector<Mail *> mails);
	string getName() const;
	vector<Mail *> getMail() const;
	unsigned int getID() const;

	friend bool operator<(Postman &p1, Postman &p2){

		vector<string> p1zipcodes, p2zipcodes;

		for(int i = 0; i < p1.myMail.size(); i++){
			p1zipcodes.push_back(p1.myMail.at(i)->getZipCode());
		}

		for(int i = 0; i < p2.myMail.size(); i++){
			p2zipcodes.push_back(p2.myMail.at(i)->getZipCode());
		}

		return (numberDifferent(p1zipcodes) < numberDifferent(p2zipcodes));
	}
};


#endif /* SRC_POSTMAN_H_ */
