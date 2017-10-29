/*
 * Agencia.cpp
 */

#include "Agencia.h"

//Conta
Conta::Conta(int nConta, float sd, int nTrans) :
		numConta(nConta), saldo(sd), numTransacoes(nTrans), titular2(NULL) {
}

int Conta::getNumConta() const {
	return numConta;
}

float Conta::getSaldo() const {
	return saldo;
}

int Conta::getNumTransacoes() const {
	return numTransacoes;
}

void Conta::setTitular2(Cliente *cli2) {
	titular2 = cli2;
}

Cliente *Conta::getTitular2() const {
	return titular2;
}

void Conta::deposito(float valor) {
	this->numTransacoes++;
	this->saldo += valor;
}

Normal::Normal(int nConta, float sd, int nTrans) :
		Conta(nConta, sd, nTrans) {
}

bool Normal::levantamento(float valor) {
	if (valor > this->saldo)
		return false;

	this->saldo -= valor;
	this->numTransacoes++;

	return true;
}

DeOperacao::DeOperacao(int nConta, float tx, float sd, int nTrans) :
		Conta(nConta, sd, nTrans), taxa(tx) {
}

bool DeOperacao::levantamento(float valor) {
	if (valor > this->saldo)
		return false;

	if (valor > 30)
		this->saldo -= (valor + this->taxa);
	else
		this->saldo -= valor;

	this->numTransacoes++;
	return true;
}

//Cliente
Cliente::Cliente(string nm) :
		nome(nm) {
}

string Cliente::getNome() const {
	return nome;
}

vector<Conta *> Cliente::getContas() const {
	return contas;
}

void Cliente::adicionaConta(Conta *c1) {
	contas.push_back(c1);
}

//Agencia

int Agencia::nextGerenteID = 0;

Agencia::Agencia(string desig) :
		designacao(desig) {
}

string Agencia::getDesignacao() const {
	return designacao;
}

vector<Cliente *> Agencia::getClientes() const {
	return clientes;
}

vector<Gerente> Agencia::getGerentes() const {
	return gerentes;
}

void Agencia::adicionaCliente(Cliente *cli1) {
	clientes.push_back(cli1);
}

Conta * Agencia::levantamento(string nomeCli, float valor) {

	for (int i = 0; i < this->clientes.size(); i++) {

		if (clientes.at(i)->getNome() == nomeCli) {
			for (int j = 0; j < this->clientes.at(i)->getContas().size(); j++) {
				if (clientes.at(i)->getContas().at(j)->levantamento(valor)) {
					return clientes.at(i)->getContas().at(j);
				}
			}
		}
	}

	return new Conta(-1);
}

float Agencia::fimMes() const {

	float accumulator = 0;

	for (int i = 0; i < clientes.size(); i++) {
		for (int j = 0; j < clientes.at(i)->getContas().size(); j++) {
			Conta* ptr = clientes.at(i)->getContas().at(j);
			if (dynamic_cast<Normal*>(ptr)) {
				Normal* nptr = dynamic_cast<Normal*>(ptr);
				nptr->levantamento(1.5);
			}

			accumulator += ptr->getSaldo();
		}
	}

	return accumulator;
}
/* NOT WORKING :/
vector<Conta*> Agencia::removeCliente(string nomeCli) {

	vector<Conta*> removedAccs;

	for (int i = 0; i < clientes.size(); i++) {
		vector<Conta*> accs = clientes.at(i)->getContas();

		if (clientes.at(i)->getNome() == nomeCli) {
			for (int k = 0; k < accs.size(); k++) {
				if (accs.at(k)->getTitular2() == nullptr) {
					removedAccs.push_back(accs.at(k));
				} else {
					accs.at(k)->getTitular2()->adicionaConta(accs.at(k));

				}

			}
		}

		for (int j = 0; j < accs.size(); j++) {
			//remove-o de 2º titular
			if (accs.at(j)->getTitular2()->getNome() == nomeCli)
				accs.at(j)->setTitular2(new Cliente("nulo"));
		}
	}

	return removedAccs;
}*/

int Agencia::operator()(string nome) {

	unsigned int total = 0;
	bool found = false;

	for (int i = 0; i < clientes.size(); i++) {

		if (clientes.at(i)->getNome() == nome) {
			found = true;
			for (int j = 0; j < clientes.at(i)->getContas().size(); j++) {
				total += clientes.at(i)->getContas().at(j)->getSaldo();
			}
		}
	}

	if (found)
		return total;
	else
		return -1;
}


void Agencia::setGerenteID (int IDinicio){
	this->nextGerenteID = IDinicio;
}

void Agencia::adicionaGerente(string nomeGer){
	Gerente g(nomeGer);
	g.setID(Agencia::nextGerenteID);
	this->gerentes.push_back(g);
	Agencia::nextGerenteID++;
}

//Gerente

Gerente::Gerente(string nm){
	this->nome = nm;
}

int Gerente::getID() const {
	return ID;
}

string Gerente::getNome() const {
	return nome;
}

