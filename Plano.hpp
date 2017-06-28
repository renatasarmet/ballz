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
    void desenha_todos_plano(sf::RenderWindow& window);
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
    	no->set_posicao(no->get_x(),no->get_y()-93); // NAO SERA 1 DE VERDADE, TEM Q VER OS PIXELS.. MAS QUEREMOS DESCER PARA A PROXIMA LINHA
    	if(no->get_y()==LIMITE_PLANO){
    		DeletaTudo();
    		//IMPLEMENTAR GRAFICAMENTE: DIZER AO USUARIO QUE O JOGO ACABOU

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
			no->carregar("imagens/ovo.png");
			no->set_id(quantidadeJaInseridaID);
			no->set_valor(valor);
			_y = 510; // ISSO NAO EH 1 DE VERDADE, EH O VALOR QUE CORRESPONDE A PRIMEIRA LINHA DO QUADRADO
			_x = i * 50 + 35; // AQUI TEREMOS QUE SUBSTITUIR PELOS PIXELS CORRESPONDESTES, ISTO EH, i * (distancia entre um ovo e outro) + (centro do primeiro ovo)
			no->set_posicao(_x, _y);
			cout << "Inseri com i = " << i << endl;
			
			Insere(no);
		}
	}


}

// REFAZER COM A PARTE GRAFICA
void Plano::desenha_todos_plano(sf::RenderWindow& window)
{
	Nodetype *Paux;

    if (QuantidadeElementos() > 0)
        Paux = PegaElementoN(1);
    else
        Paux = NULL;

    while (Paux != NULL)
    {
		Paux->desenhar(window);
        Paux = Paux->get_next();
    }
}

