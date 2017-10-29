#include "Escritorio.h"
#include <iostream>
#include <algorithm>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }



//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }



//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }


bool ImpressoraPB::imprime(Documento doc1){

	if(doc1.getNumPaginas() <= this->numPagImprimir){
		this->numPagImprimir -= doc1.getNumPaginas();
		this->docsImpressos.push_back(doc1);
		return true;
	}

	return false;
}



//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo)
		return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}

bool ImpressoraCores::imprime(Documento doc1){

	int paginasPretas = doc1.getNumPaginas() * doc1.getPercentagemPreto();
	int paginasAmarelas = doc1.getNumPaginas() * doc1.getPercentagemAmarelo();

	if(paginasPretas <= this->numPagImprimirPreto &&
			paginasAmarelas <= this->numPagImprimirAmarelo){

		numPagImprimirPreto -= paginasPretas;
		numPagImprimirAmarelo -= paginasAmarelas;
		this->docsImpressos.push_back(doc1);
		return true;
	}

	return false;
}


//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }

int Escritorio::numImpressorasSemResponsavel() const{

	int freePrinters = 0;
	int found;

	//ciclo para iterar pelas impressoras
	for(int i = 0; i < impressoras.size(); i++){
		Impressora * currentPrinter = impressoras.at(i);
		found = false;
		//ciclo para iterar pelos funcionarios e verificar se possuem esta impressora
		for(int k = 0; k < funcionarios.size(); k++){
			vector<Impressora *> printers = funcionarios.at(k).getImpressoras();

			if(find(printers.begin(), printers.end(), currentPrinter) != printers.end()){
				found = true;
				break;
			}
		}

		if(!found) freePrinters++;
	}

	return freePrinters;
}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1){

	vector<Impressora *> removedPrinters;

	for(int i = 0; i < impressoras.size(); i++){
		if(impressoras.at(i)->getAno() < ano1){
			removedPrinters.push_back(impressoras.at(i));
			impressoras.erase(impressoras.begin() + i);
			i--;
		}
	}

	return removedPrinters;
}

Impressora * Escritorio::imprimeDoc(Documento doc1) const{

	for(int i = 0; i < impressoras.size(); i++){
		if(impressoras.at(i)->imprime(doc1)){
			return impressoras.at(i);
		}
	}

	return new ImpressoraPB("inexistente",0,0);
}

vector<Impressora *> Escritorio::tonerBaixo() const{

	vector<Impressora *> lowToner;

	for(int i = 0; i < impressoras.size(); i++){
		Impressora * printer = impressoras.at(i);

		if(ImpressoraPB* pbptr = dynamic_cast<ImpressoraPB*>(printer)){
			if(pbptr->getNumPaginasImprimir() < 30){
				lowToner.push_back(pbptr);
			}

		}else{
			ImpressoraCores* coresptr = dynamic_cast<ImpressoraCores*>(printer);
			if(coresptr->getNumPaginasImprimir() < 20)
				lowToner.push_back(coresptr);
		}
	}

	return lowToner;
}

string Escritorio::operator()(const string& cod){

	for(int i=0; i < funcionarios.size(); i++){
		for(int j=0; j < funcionarios.at(i).getImpressoras().size(); j++){
			if(funcionarios.at(i).getImpressoras().at(j)->getCodigo() == cod){
				return funcionarios.at(i).getCodigo();
			}
		}
	}

	return "nulo";
}
