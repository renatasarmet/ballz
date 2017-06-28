#ifndef Plano_hpp
#define Plano_hpp

#include <iostream>
#include "ListaSimples.hpp"
#include "Nodetype.hpp"
#include <time.h>
#include <ctime>
//#include "feitico.h"
#define TAMANHO 8
#define LIMITE_PLANO 10

using namespace std;

class Plano : public ListaSimples{
public:
    Plano();
    ~Plano();
    void InsereNplano(int rodadaAtual);
//    void desenha_todos_plano(sf::RenderWindow& window);
private:
	int contador;
	int quantidadeJaInseridaID;
};

#endif /* Plano_hpp */


Plano::Plano() : ListaSimples(){
	contador = 0;
	quantidadeJaInseridaID = 0;
}

Plano::~Plano(){

}

void Plano::InsereNplano(int rodadaAtual)
{
	int i,entraOuNao, r, valor;
	bool DeuCerto;
	float _x, _y;
    Nodetype *no;
    no = P;
    while(no != NULL){
    	no->set_posicao(no->get_x(),no->get_y()+1); // NAO SERA 1 DE VERDADE, TEM Q VER OS PIXELS.. MAS QUEREMOS DESCER PARA A PROXIMA LINHA
    	if(no->get_y()==LIMITE_PLANO){
    		ProcuraRemove(no->get_id(), DeuCerto); // ISSO SERA SUBSTITUIDO DEPOIS PELO GAME OVER
    		// GAME OVER AQUI .. IMPLEMENTAR
    	}
    	no = no->get_next();
    }

	for(i=0;i<TAMANHO;i++){
		entraOuNao = rand() % 2;
		if(entraOuNao==1){
			r = (rand() % 2 + 1);
			valor = rodadaAtual*r; // valor a ser inserido
			// INSERE
			quantidadeJaInseridaID +=1;
			no = new Nodetype();
			no->set_id(quantidadeJaInseridaID);
			no->set_valor(valor);
			_y = 1; // ISSO NAO EH 1 DE VERDADE, EH O VALOR QUE CORRESPONDE A PRIMEIRA LINHA DO QUADRADO
			_x = i * 1 + 1; // AQUI TEREMOS QUE SUBSTITUIR PELOS PIXELS CORRESPONDESTES, ISTO EH, i * (distancia entre um ovo e outro) + (centro do primeiro ovo)
			no->set_posicao(_x,_y);
			Insere(no);
		}
	}


}

// REFAZER COM A PARTE GRAFICA
//void Plano::desenha_todos_plano(sf::RenderWindow& window)
//{
//	Nodetype *Paux;
//	float _x, _y;
//
//    if (QuantidadeElementos() > 0)
//        Paux = PegaElementoN(1);
//    else
//        Paux = NULL;
//
//    while (Paux != NULL)
//    {
//
//		if (Paux->get_info() == "imagens/pomo1.png")
//		{
//			Paux->move(x, 0);
//
//			if (Paux->get_x() >= 924 || Paux->get_x() <= 100)
//			{
//				x = -x;
//			}
//		}
//
//		if (Paux->get_info() == "imagens/voldemort.png")
//		{
//			contador += 1;
//			if ((contador == 100) && (feitico::lancado == false)) {
//				_x = (rand() % 919);
//				_y = (rand() % 300 + 321);
//				Paux->set_posicao(_x, _y);
//				contador = 0;
//			}
//			else if (contador == 100)
//				contador = 0;
//		}
//
//        Paux->desenhar(window);
//        Paux = Paux->get_next();
//    }
//}

