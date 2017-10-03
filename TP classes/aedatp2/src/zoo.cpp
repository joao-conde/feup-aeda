#include <climits>
#include "zoo.h"

int Animal::maisJovem = INT_MAX;

//Animal

Animal::Animal(string nome, int idade) :
		nome(nome), idade(idade) {
	if (idade < this->maisJovem)
		this->maisJovem = idade;

	this->vet = NULL;
}

string Animal::getNome() const {
	return nome;
}

int Animal::getIdade() const{
	return this->idade;
}

int Animal::getMaisJovem() {
	return maisJovem;
}

void Animal::setVet(Veterinario *vet) {
	this->vet = vet;
}

Veterinario* Animal::getVet() const{
	return this->vet;
}

//Veterinario

Veterinario::Veterinario(string nome, int cod) :
		nome(nome), codOrdem(cod) {
}
;

string Veterinario::getNome() const {
	return nome;
}

long Veterinario::getCod() const {
	return this->codOrdem;
}

//Cao

Cao::Cao(string nome, int idade, string raca) :
		Animal(nome, idade), raca(raca) {
}
;

bool Cao::eJovem() const {
	if (idade < 5)
		return true;
	else
		return false;
}

string Cao::getInformacao() const {

	string s = "";

	s += this->nome + ", " + to_string(this->idade) + ", ";

	if (this->vet != NULL) {
		s += vet->getNome() + ", " + to_string(vet->getCod()) + ", ";
	}

	s += this->raca;

	return s;
}

//Voador

Voador::Voador(int vmax, int amax) :
		velocidade_max(vmax), altura_max(amax) {
}

int Voador::getVmax() const {
	return this->velocidade_max;
}

int Voador::getAmax() const {
	return this->altura_max;
}

//Morcego

Morcego::Morcego(string nome, int idade, int vmax, int amax) :
		Animal(nome, idade), Voador(vmax, amax) {
}
;

bool Morcego::eJovem() const {
	if (idade < 4)
		return true;
	else
		return false;
}

string Morcego::getInformacao() const {

	string s = "";

	s += s + this->nome + ", " + to_string(this->idade) + ", "
			+ to_string(getVmax()) + ", " + to_string(getAmax());

	return s;
}

//Zoo

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1) {
	animais.push_back(a1);
}

string Zoo::getInformacao() const {

	string result = "";

	for (int i = 0; i < animais.size(); i++) {
		result += animais.at(i)->getInformacao() + '\n';
	}

	return result;
}

bool Zoo::animalJovem(string nomeA) {

	for (int i = 0; i < animais.size(); i++) {
		if (animais.at(i)->getNome() == nomeA) {
			return animais.at(i)->eJovem();
		}
	}

	return false;
}

void Zoo::alocaVeterinarios(istream &isV) {

	string vet;
	int cod, maxsize;

	while (!isV.eof()) {
		getline(isV, vet, '\n');
		isV >> cod;
		isV.ignore();
		this->veterinarios.push_back(new Veterinario(vet, cod));
	}

	if (veterinarios.size() <= animais.size())
		maxsize = veterinarios.size();
	else
		maxsize = animais.size();

	for (int i = 0; i < maxsize; i++) {
		animais.at(i)->setVet(veterinarios.at(i));
	}

}

bool Zoo::removeVeterinario(string nomeV){


	for(int i = 0; i < animais.size(); i++){
		if(animais.at(i)->getVet() != NULL)
			if(animais.at(i)->getVet()->getNome() == nomeV)
				animais.at(i)->setVet(veterinarios.at(i+1));
	}

	for(int i = 0; i < veterinarios.size(); i++){

		if(veterinarios.at(i)->getNome() == nomeV){
			veterinarios.erase(veterinarios.begin() + i);
			return true;
		}
	}


	return false;
}

vector<Animal *> Zoo::getAnimais() const{
	return this->animais;
}

bool Zoo::operator < (Zoo& zoo2) const{

	int sumofage1 = 0, sumofage2 = 0;

	for(int i = 0; i < this->animais.size(); i++)
		sumofage1 += animais.at(i)->getIdade();

	for(int i = 0; i < zoo2.getAnimais().size(); i++)
		sumofage2 += zoo2.getAnimais().at(i)->getIdade();

	if(sumofage1 <= sumofage2)
		return true;
	else
		return false;
}
