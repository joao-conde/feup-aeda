#ifndef PARQUE_H_
#define PARQUE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class InfoCartao {
public:
	string nome;
	bool presente;
	int frequencia;
	bool operator == (const InfoCartao &ic1) const;
	bool operator < (const InfoCartao &ic1) const;
};

class ParqueEstacionamento {
	unsigned int vagas;
	const unsigned int lotacao;
	unsigned int numClientes;
	const unsigned int numMaximoClientes;
	vector<InfoCartao> clientes;
public:
	ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli);
	~ParqueEstacionamento();
	vector<InfoCartao> getClientes() const;
	bool adicionaCliente(const string & nome);
	bool retiraCliente(const string & nome);
	bool entrar(const string & nome);
	bool sair(const string & nome);
	unsigned int getNumLugares() const;
	unsigned int getNumLugaresOcupados() const;
	int posicaoCliente(const string & nome) const;
	int getFrequencia(const string &nome) const;
	InfoCartao getClienteAtPos(vector<InfoCartao>::size_type p) const;
	void ordenaClientesPorFrequencia();
	void ordenaClientesPorNome();
	vector<string> clientesGamaUso(int n1, int n2);

	friend ostream& operator <<(ostream & os, const ParqueEstacionamento & pe){
		for(int i=0; i < pe.clientes.size(); i++){
			cout << "CLIENT NAME: " << pe.clientes.at(i).nome << endl;
			if(pe.clientes.at(i).presente)
				cout << "IN THE PARK" << endl;
			else
				cout << "OUT OF THE PARK" << endl;
			cout << "IN/OUT FREQUENCY: " << pe.clientes.at(i).frequencia << endl << endl;
		}
	}

};


class ClienteNaoExistente{
	string nome;
public:
	ClienteNaoExistente(string nome){
		this->nome = nome;
	}

	string getNome(){
		return this->nome;
	}
};

class PosicaoNaoExistente{
	vector<InfoCartao>::size_type index;
public:
	PosicaoNaoExistente(vector<InfoCartao>::size_type i){
		this->index = i;
	}

	vector<InfoCartao>::size_type getValor(){
		return this->index;
	}
};


#endif /*PARQUE_H_*/
