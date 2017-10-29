/*
 * Postman.cpp
 */
#include "Postman.h"

unsigned int Postman::nextID = 1;

Postman::Postman(): id(0) {}

Postman::Postman(string name){
	this->name = name;
	this->id = this->nextID;
	nextID++;
}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

