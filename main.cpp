#include <iostream>
#include "ListaSimples.hpp"
#include "Nodetype.hpp"
#include "Plano.hpp"

#include <time.h>
#include <ctime>

using namespace std;


void InsereNplano(int n, ListaSimples *plano, ListaSimples *listaGeral){
	int i;
	Nodetype *no;
	Nodetype *noPtr;
	for(i=0;i<n;i++){
		no = listaGeral->PegaElementoAleatorio();
		noPtr = new Nodetype();
		noPtr->CopiaNode(no);
		plano->Insere(noPtr);
	}
}


int main()
{
    Plano plano;
    int rodadaAtual;
    bool DeuCerto;
    srand(time(NULL));

   // Nodetype *no;

    rodadaAtual = 7;


    cout << "ITENS DO PLANO: " << endl;
    plano.ExibeLista();



	cout << "Quantidade de elementos plano: " << plano.QuantidadeElementos() << endl << endl;




//    //Inserindo na lista plano

	cout << "Inserindo... " << endl;

    plano.InsereNplano(rodadaAtual);

    //Exibindo a lista plano
    cout << "DEPOIS DE INSERIR NO PLANO: " << endl;
   plano.ExibeLista();

   cout << "Quantidade de elementos plano de novo: " << plano.QuantidadeElementos() << endl;


   rodadaAtual +=1;

   cout << "Inserindo... " << endl;

   plano.InsereNplano(rodadaAtual);

   //Exibindo a lista plano
   cout << "DEPOIS DE INSERIR DE NOVO NO PLANO: " << endl;
  plano.ExibeLista();

  cout << "Quantidade de elementos plano de novo de novo: " << plano.QuantidadeElementos() << endl;



  cout << "Removendo... " << endl;
  plano.ProcuraRemove(5,DeuCerto);

  //Exibindo a lista plano
    cout << "DEPOIS DE REMOVER NO PLANO: " << endl;
   plano.ExibeLista();

   cout << "Quantidade de elementos plano de novo de novo de novo: " << plano.QuantidadeElementos() << endl;


   rodadaAtual +=1;

   cout << "Inserindo de novo... " << endl;

     plano.InsereNplano(rodadaAtual);

     //Exibindo a lista plano
     cout << "DEPOIS DE INSERIR DE NOVO NO PLANO APOS REMOVER: " << endl;
    plano.ExibeLista();

    cout << "Quantidade de elementos plano de novo de novo de novo: " << plano.QuantidadeElementos() << endl;


    return 0;
}

