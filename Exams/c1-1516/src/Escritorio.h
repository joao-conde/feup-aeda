/*
 * Escritorio.h
 *
 *  Created on: Oct 4, 2015
 *      Author: arocha
 */

#ifndef ESCRITORIO_H_
#define ESCRITORIO_H_

#include <vector>
#include <string>
#include <iostream>
using namespace std;


class Documento {
  int numPaginas;
  float pPreto, pAmarelo;
public:
   Documento(int nPag, float pP, float pA);
   ~Documento();
   int getNumPaginas() const;
   float getPercentagemPreto() const;
   float getPercentagemAmarelo() const;


   friend Documento& operator+(Documento &doc1, Documento &doc2){
	   int npages = doc1.numPaginas + doc2.numPaginas;

	   float pP = (doc1.pPreto*doc1.numPaginas + doc2.pPreto*doc2.numPaginas)/npages;

	   float pA = (doc1.pAmarelo*doc1.numPaginas + doc2.pAmarelo*doc2.numPaginas)/npages;

	   Documento* d3 = new Documento(npages,pP,pA);

	   return *d3;
   }
};

class Impressora {
protected:
  const string codigo;
  const int ano;
  vector<Documento> docsImpressos;
public:
	Impressora(string cod, int a);
	virtual ~Impressora();
	string getCodigo() const;
	int getAno() const;
	vector<Documento> getDocumentosImpressos() const;

	virtual bool imprime(Documento doc1) = 0;
};

class ImpressoraPB: public Impressora {
  int numPagImprimir;
public:
   ImpressoraPB(string cod, int a, int toner);
   int getNumPaginasImprimir() const;

   bool imprime(Documento doc1);
};

class ImpressoraCores: public Impressora {
  float numPagImprimirPreto;
  float numPagImprimirAmarelo;
public:
   ImpressoraCores(string cod, int a, int toner);
   int getNumPaginasImprimir() const;

   bool imprime(Documento doc1);
};

class Funcionario {
  string codigo;
  vector<Impressora *> impressoras;
public:
  Funcionario(string cod);
  ~Funcionario();
  string getCodigo() const;
  void adicionaImpressora(Impressora *i1);
  vector<Impressora *> getImpressoras() const;
	// …
};

class Escritorio {
  vector<Impressora *> impressoras;
  vector<Funcionario> funcionarios;
public:
  Escritorio();
  ~Escritorio();
  void adicionaImpressora(Impressora *i1);
  void adicionaFuncionario(Funcionario f1);
  vector<Impressora *> getImpressoras() const;

  int numImpressorasSemResponsavel() const;
  vector<Impressora *> retiraImpressoras(int ano1);
  Impressora * imprimeDoc(Documento doc1) const;
  vector<Impressora *> tonerBaixo() const;

  string operator()(const string& cod);

};






#endif /* ESCRITORIO_H_ */
