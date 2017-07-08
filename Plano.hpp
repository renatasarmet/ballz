#ifndef Plano_hpp
#define Plano_hpp

#include <iostream>
#include "ListaSimples.hpp"
#include "Nodetype.hpp"
#include <time.h>
#include <ctime>
#define TAMANHO 8
#define LIMITE_PLANO 60

using namespace std;

class Plano : public ListaSimples{
public:
    Plano();
    ~Plano();
    void InsereNplano(int rodadaAtual);
    void desenha_todos_plano(sf::RenderWindow& window);
    bool get_perdeu() const;
    void reseta_perdeu_false();
private:
	int contador;
	int quantidadeJaInseridaID;
    bool perdeu;
    bool jaTeveNovaPokeball;
};

#endif /* Plano_hpp */


Plano::Plano() : ListaSimples(){
	contador = 0;
	quantidadeJaInseridaID = 0;
    perdeu = 0;
    jaTeveNovaPokeball = 0;
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
    
    jaTeveNovaPokeball = 0;
    while(no != NULL){
        no->valorText.setString(to_string(no->get_valor()));
    	no->set_posicao(no->get_x(),no->get_y()-93);
        no->valorText.setPosition(no->get_x(),no->get_y());

        if(no->get_y()<=LIMITE_PLANO){
            if(no->get_valor()==-1)
                ProcuraRemove(no->get_id(), DeuCerto);
            else{
                DeletaTudo();
                perdeu = 1;
            }
    	}
    	no = no->get_next();
    }
    
    if(!perdeu){
        for(i=0;i<TAMANHO;i++){
            entraOuNao = rand() % 2;
            if(entraOuNao==1){
                r = (rand() % 2 + 1);
                valor = rodadaAtual*r; // valor a ser inserido
                quantidadeJaInseridaID +=1;
                no = new Nodetype();
                no->carregar("imagens/ovo.png");
                no->set_id(quantidadeJaInseridaID);
                no->set_valor(valor);
                no->valorText.setString(to_string(no->get_valor()));
                _y = 510; // valor correspondente à primeira linha de ovos
                _x = i * 50 + 45; // i * (distancia entre um ovo e outro) + (centro do primeiro ovo)
                no->set_posicao(_x, _y);
                if(no->get_valor() >= 20)
                    no->valorText.setPosition(no->get_x(), no->get_y());
                else
                    no->valorText.setPosition(no->get_x(),no->get_y());
			
                Insere(no);
            }
            else{
                int a;
                a = (rand() % 3);
                if(!jaTeveNovaPokeball && a == 1){
                    jaTeveNovaPokeball = 1;
                    
                    valor = -1;
                    quantidadeJaInseridaID +=1;
                    no = new Nodetype();
                    no->carregar("imagens/pokebola.png");
                    no->set_id(quantidadeJaInseridaID);
                    no->set_valor(valor);
                    no->valorText.setString("");
                    _y = 510; // valor correspondente à primeira linha de ovos
                    _x = i * 50 + 45; // i * (distancia entre um ovo e outro) + (centro do primeiro ovo)
                    no->set_posicao(_x, _y);
                    no->valorText.setPosition(no->get_x(),no->get_y());
                    
                    Insere(no);
                }
            }
        }
    }
}


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
       
        if (Paux->get_valor() != -1){
            Paux->valorText.setString(to_string(Paux->get_valor()));
            Paux->valorText.setPosition(Paux->get_x() -10,Paux->get_y() - 10);
            window.draw(Paux->valorText);
        }
        Paux = Paux->get_next();
    }
}


bool Plano::get_perdeu() const {
    return this->perdeu;
}

void Plano::reseta_perdeu_false() {
    this->perdeu = false;
}
