/*
 * Agencia.h
 */

#ifndef AGENCIA_H_
#define AGENCIA_H_

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Cliente;

class Conta {
protected:
  int numConta;
  float saldo;
  int numTransacoes;
  Cliente *titular2;
public:
	Conta(int nConta, float sd=0, int nTrans=0);
	int getNumConta() const;
	float getSaldo() const;
	int getNumTransacoes() const;
	Cliente *getTitular2() const;
	void setTitular2(Cliente *cli2);

	virtual bool levantamento(float valor){};
	void deposito(float valor);

};

class Normal: public Conta {
public:
   Normal(int nConta, float sd=0, int nTrans=0);
   bool levantamento(float valor);

};


class DeOperacao: public Conta {
  float taxa;
public:
  DeOperacao(int nConta, float tx, float sd=0, int nTrans=0);
  bool levantamento(float valor);

};


class Cliente {
  string nome;
  vector<Conta *> contas;
public:
  Cliente(string nm);
  string getNome() const;
  vector<Conta *> getContas() const;
  void adicionaConta(Conta *c1);

};


class Gerente {
  int ID;
  string nome;
  vector<Cliente *> meusClientes;
public:
  Gerente(string nm);
  int getID() const;
  string getNome() const;
  void setID(int id){
	  this->ID = id;
  }

};


class Agencia {
  static int nextGerenteID;
  string designacao;
  vector<Cliente *> clientes;
  vector<Gerente> gerentes;
public:
  Agencia(string desig);
  string getDesignacao() const;
  vector<Cliente *> getClientes() const;
  vector<Gerente> getGerentes() const;
  void adicionaCliente(Cliente *cli1);

  Conta *levantamento(string nomeCli, float valor);
  float fimMes() const;
  vector<Conta*> removeCliente(string nomeCli);

  int operator()(string nome);

  void setGerenteID (int IDinicio);
  void adicionaGerente(string nomeGer);

  friend bool operator<(Agencia &a1, Agencia &a2){

	 unsigned int sum1 = 0, sum2 = 0;

	 for(int i=0; i<a1.clientes.size(); i++){
		 for(int k = 0; k < a1.clientes.at(i)->getContas().size(); k++){
			 sum1 += a1.clientes.at(i)->getContas().at(k)->getSaldo();
		 }
	 }

	 for(int i=0; i<a2.clientes.size(); i++){
		 for(int k = 0; k < a2.clientes.at(i)->getContas().size(); k++){
			 sum2 += a2.clientes.at(i)->getContas().at(k)->getSaldo();
		 }
	 }

	 return (sum1/a1.clientes.size() < sum2/a2.clientes.size());
  }

};



#endif /* AGENCIA_H_ */
