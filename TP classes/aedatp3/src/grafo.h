#include <iostream>
#include <vector>

using namespace std;

/**
 * Versão da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);

// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }


//excecao ArestaRepetida
template <class N>
class ArestaRepetida{
public:
	N src, dest;
	ArestaRepetida(N source, N destination){
		src = source;
		dest = destination;
	}
};
template <class N>
ostream& operator <<(ostream& out, const ArestaRepetida<N> &a){
	out << "Aresta repetida: " << a.src << " , " << a.dest;
	return out;
}

//excecao ArestaInexistente
template <class N>
class ArestaInexistente{
public:
	N src, dest;
	ArestaInexistente(N source, N destination){
		src = source;
		dest = destination;
	}
};
template <class N>
ostream& operator <<(ostream& out, const ArestaInexistente<N> &a){
	out << "Aresta inexistente: " << a.src << " , " << a.dest;
	return out;
}



//Grafo

template<class N, class A>
Grafo<N,A>::Grafo(){
}

template<class N, class A>
Grafo<N,A>::~Grafo(){
	for(int i = 0; i < nos.size(); i++)
		delete nos.at(i);
}

template<class N, class A>
int Grafo<N,A>::numNos() const{
	return this->nos.size();
}

template<class N, class A>
int Grafo<N,A>::numArestas() const{

	int counter = 0;

	for(int i = 0; i < nos.size(); i++){
		counter += nos.at(i)->arestas.size();
	}

	return counter;
}

template<class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirNo(const N &dados){

	typename vector<No<N,A>*>::const_iterator it;

	for(it = nos.begin(); it != nos.end(); it++){
		if((*it)->info == dados) throw NoRepetido<N>(dados);
	}

	No<N,A>* newNode = new No<N,A>(dados);
	nos.push_back(newNode);
	return *this;
}

template<class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val){

	bool foundNode1=false;
	bool foundNode2 = false;

	No<N,A> *beginPtr = NULL;
	No<N,A> *endPtr = NULL;

	// NON-ITERATOR VERSION

	//search in "nos" for nodes with same "inicio"
	for(int i = 0; i < nos.size(); i++){
		if(nos.at(i)->info == inicio){
			foundNode1 = true;
			beginPtr = nos.at(i);
			//check if this node has edge to same destination as "fim"
			for(int k = 0; k < nos.at(i)->arestas.size(); k++){
				if(nos.at(i)->arestas.at(k).destino->info == fim)
					throw ArestaRepetida<N>(inicio,fim);
			}
		}else if(nos.at(i)->info == fim){
			foundNode2 = true;
			endPtr = nos.at(i);
		}
	}


	if(!foundNode1) throw NoInexistente<N>(inicio);
	if(!foundNode2) throw NoInexistente<N>(fim);

	Aresta<N,A> aresta1(endPtr,val);
	beginPtr->arestas.push_back(aresta1);


	/*ITERATOR VERSION
	typename vector<No<N,A>*>::iterator itb;
	typename vector<Aresta<N,A>>::iterator ita;

	for(itb=nos.begin() ; itb!=nos.end() ; itb++){
		if((*itb)->info == inicio){
			foundNode1 = true;
			beginPtr = *itb;

			for(ita = (*itb)->arestas.begin(); ita != (*itb)->arestas.end(); ita++){
				if(ita->destino->info == fim)
					throw ArestaRepetida<N>(inicio,fim);
			}
			if(foundNode2)break;
		}
		else if((*itb)->info == fim){
			foundNode2 = true;
			endPtr = *itb;
			if(foundNode1)break;
		}
	}

	if(!foundNode1) throw NoInexistente<N>(inicio);
	if(!foundNode2) throw NoInexistente<N>(fim);

	Aresta<N,A> aresta1(endPtr,val);
	beginPtr->arestas.push_back(aresta1);
	 */
	return *this;
}

template<class N, class A>
A & Grafo<N,A>::valorAresta(const N &inicio, const N &fim){

	for(int i = 0; i < nos.size(); i++){
		if(nos.at(i)->info == inicio){
			for(int k=0; k < nos.at(i)->arestas.size(); k++){
				if(nos.at(i)->arestas.at(k).destino->info == fim)
					return nos.at(i)->arestas.at(k).valor;
			}

			throw ArestaInexistente<N>(inicio,fim);
		}
	}


	throw NoInexistente<N>(inicio);
}


template<class N, class A>
Grafo<N,A> & Grafo<N,A>::eliminarAresta(const N &inicio, const N &fim){

	for(int i = 0; i < nos.size(); i++){
		if(nos.at(i)->info == inicio){
			for(int k = 0; k < nos.at(i)->arestas.size(); k++){
				if(nos.at(i)->arestas.at(k).destino->info == fim){
					nos.at(i)->arestas.erase(nos.at(i)->arestas.begin()+k);
					return *this;
				}
			}

			throw ArestaInexistente<N>(inicio,fim);
		}
	}

	throw NoInexistente<N>(inicio);

}


template<class N, class A>
void Grafo<N,A>::imprimir(std::ostream &os) const{

	string info = "";

	for(int i = 0; i < nos.size(); i++){

		info += "( " + nos.at(i)->info;
		for(int k = 0; k < nos.at(i)->arestas.size(); k++){
			info += "[ " + nos.at(i)->arestas.at(k).destino->info + " "
					+ to_string(nos.at(i)->arestas.at(k).valor) + "] " ;
		}

		info += ") ";
	}

	os << info;

}


template<class N,class A>
ostream & operator<<(ostream &os, const Grafo<N,A> &g){
	g.imprimir(os);
	return os;
}







