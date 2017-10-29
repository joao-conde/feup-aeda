/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name){

	vector<Mail *> result;

	for(int i = 0; i < this->postmen.size(); i++){
		if(postmen.at(i).getName() == name){
			result = postmen.at(i).getMail();
			postmen.erase(postmen.begin()+i);
			return result;
		}
	}

	return result;
}


vector<Mail *> PostOffice::endOfDay(unsigned int &balance){

	vector<Mail *> ret;
	balance = 0;

	for(int i = 0; i < this->mailToSend.size(); i++){

		balance += mailToSend.at(i)->getPrice();

		if(mailToSend.at(i)->getZipCode() <= this->lastZipCode &&
				mailToSend.at(i)->getZipCode() >= this->firstZipCode){
			this->addMailToDeliver(mailToSend.at(i));
		}
		else{
			ret.push_back(mailToSend.at(i));
		}
		mailToSend.erase(mailToSend.begin() + i);
		i--;
	}

	return ret;
}


Postman PostOffice::addMailToPostman(Mail *m, string name){

	for(int i = 0; i < postmen.size(); i++){
		if(postmen.at(i).getName() == name){
			postmen.at(i).addMail(m);
			return postmen.at(i);
		}
	}

	throw NoPostmanException(name);
}

