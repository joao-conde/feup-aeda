#include "Parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot,
		unsigned int nMaxCli) :
		lotacao(lot), numMaximoClientes(nMaxCli) {
	vagas = nMaxCli;
}

unsigned int ParqueEstacionamento::getNumLugares() const {
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
	return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const {

	for (int i = 0; i < clientes.size(); i++) {
		if (clientes.at(i).nome == nome)
			return i;
	}

	return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {

	if (vagas == 0)
		return false;

	InfoCartao newclient;
	newclient.nome = nome;
	newclient.presente = false;

	clientes.push_back(newclient);

	vagas--;

	return true;
}

bool ParqueEstacionamento::entrar(const string &nome) {

	int currentLotation = 0;

	for(int i = 0; i < clientes.size(); i++){
		if(clientes.at(i).presente)
			currentLotation++;
	}

	if(currentLotation == lotacao)
		return false;

	for(int i = 0; i < clientes.size(); i++){
		if(clientes.at(i).nome == nome && clientes.at(i).presente == false){
			clientes.at(i).presente = true;
			return true;
		}
	}

	return false;
}

bool ParqueEstacionamento::retiraCliente(const string &nome) {

for (int i = 0; i < clientes.size(); i++) {
	if (clientes.at(i).nome == nome) {
		if (clientes.at(i).presente)
			return false;
		else{
			clientes.erase(clientes.begin() + i);
			return true;
		}
	}
}

vagas++;
return false;
}

bool ParqueEstacionamento::sair(const string &nome) {

	for(int i = 0; i < clientes.size(); i++){
		if(clientes.at(i).nome == nome)
			if(!clientes.at(i).presente)
				return false;
			else{
				vagas++;
				clientes.erase(clientes.begin()+i);
				return true;
			}
	}

	return false;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const{

	int presentdrivers = 0;

	for(int i = 0; i < clientes.size(); i++){
		if(clientes.at(i).presente)
			presentdrivers++;
	}

	return presentdrivers;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const{
	return clientes.size();
}

vector<InfoCartao> ParqueEstacionamento::getClientes() const{
	return clientes;
}

const ParqueEstacionamento &ParqueEstacionamento::operator+=(const ParqueEstacionamento &p2){

	int clientstoadd = 0;

	if(this->numMaximoClientes - this->getNumClientesAtuais() > p2.getNumClientesAtuais())
		clientstoadd = p2.getNumClientesAtuais();
	else
		clientstoadd = this->numMaximoClientes - this->getNumClientesAtuais();



	for(int i = 0; i < clientstoadd; i++){
		this->adicionaCliente(p2.getClientes().at(i).nome);
	}

	return *this;
}

