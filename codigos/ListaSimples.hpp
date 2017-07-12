#ifndef LISTASIMPLES_HPP
#define LISTASIMPLES_HPP

#include "Nodetype.hpp"
#include <iostream>
#include <time.h>
#include <ctime>
using namespace std;

//implementação da classe Lista Simples

class ListaSimples
{
public:
	ListaSimples();
	~ListaSimples();

	void Cria(Nodetype *x);
	bool Vazia();
	void Insere(Nodetype *x);
	void InsereADireita(Nodetype *x);
	void ProcuraRemove(int x, bool &DeuCerto);
    void DeletaTudo();

	Nodetype* PegaElementoN(int n) const; // pega o N-esimo elemento da lista
	int QuantidadeElementos() const; // conta a quantidade de elementos da lista

    Nodetype *P; // Indica sempre o primeiro da Lista

private:

	void Remove(Nodetype *Premove, bool &DeuCerto); // metodo privado pois quem deve ser chamado eh o procura remove
};


ListaSimples::ListaSimples(){
	P = NULL;
}

ListaSimples::~ListaSimples(){
    
}

void ListaSimples::Cria(Nodetype *x){
	P = new Nodetype();
	P = x;
	P->set_next(NULL);
}

bool ListaSimples::Vazia(){
	if(P==NULL){
		return true;
	}else{
		return false;
	}
}

void ListaSimples::Insere(Nodetype *x){
	if(Vazia()==true){
		Cria(x);
	}else{
		InsereADireita(x);
	}
}

void ListaSimples::InsereADireita(Nodetype *x){
	Nodetype *Paux;
	Nodetype *Paux2 = new Nodetype();
	Paux2 = x;
	Paux2->set_next(NULL);
	Paux = P;
	while(Paux->get_next()!=NULL){
		Paux = Paux->get_next();
	}
	Paux->set_next(Paux2);
}

void ListaSimples::ProcuraRemove(int x, bool &DeuCerto){
	Nodetype *Paux;
	if(Vazia()){
		DeuCerto = false;
	}
	else if(P->get_id()==x){
		DeuCerto = true;
		Paux = P;
		P = P->get_next();
		delete Paux;
	}
	else{
		Paux = P;
		while((Paux->get_next()->get_id()!=x)&&(Paux->get_next()!=NULL)){
			Paux = Paux->get_next();

		}
		if(Paux->get_next()!=NULL){
			Remove(Paux, DeuCerto);
		}
	}
}


void ListaSimples::Remove(Nodetype *Premove, bool &DeuCerto){
	Nodetype *Paux2;
	DeuCerto = true;
	Paux2 = Premove;
	Premove = Premove->get_next();
	Paux2->set_next(Paux2->get_next()->get_next());
	delete Premove;
}

void ListaSimples::DeletaTudo(){
    bool ok;
    while(QuantidadeElementos()!=0){
        ProcuraRemove(P->get_id(), ok);
    }
}

int ListaSimples::QuantidadeElementos() const {
	Nodetype *Paux;
	Paux = P;
	int q = 0;
	while(Paux!=NULL){
		q += 1;
		Paux = Paux->get_next();
	}

	return q;
}


Nodetype* ListaSimples::PegaElementoN(int n) const{
	Nodetype *Paux;
	Paux = P;
	int i;

	for(i=1;i<n;i++){
		Paux = Paux->get_next();
	}

	return Paux;
}

#endif
