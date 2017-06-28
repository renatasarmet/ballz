#ifndef JOGO_H
#define JOGO_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <time.h>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <locale>

#include "menu.h"
#include "tela_inicial.h"
#include "ganhou.h"
#include "perdeu.h"
#include "braco.h"
#include "pokeball.h"
#include "ListaSimples.hpp"
#include "Nodetype.hpp"
#include "Plano.hpp"
#include "instrucoes.h"

 

using namespace std;

class jogo
{
public:
    static void Start(braco *hook, Plano* plano);
    static void CriandoTudo();
    static void JogarNovamente(braco *hook, Plano* plano);
    
private:
    static bool IsExiting();
    static void loop_jogo(braco *hook, Plano* plano);
    
    static void mostrar_tela_inicial();
    static void mostrar_menu();
	static void mostrar_instrucao();
    static void mostrar_ganhou(braco *hook, Plano* plano);
    static void mostrar_perdeu(braco *hook, Plano* plano);
  
    static bool VerificaGanhou();
    //static bool verifica_passou();
   //static void verifica_colisao(braco*, Plano* plano);
    
    enum GameState {
        Inicializado, Mostrando_Tela_Inicial, Pausado, Mostrando_Menu, Jogando, Saindo, Ganhando, Perdendo, Mostrando_Instrucao, Mostrando_Transicao_Passou, Mostrando_Transicao_Horcrux, Nova_Fase, Fase_Final
    }; // estado que o jogo pode estar durante a partida
    
    static GameState estado_jogo;
    static sf::RenderWindow janela;
    static sf::Sprite background;
    static sf::Text timerText;
    static sf::Text nivelText;
    static sf::Text totalText;
    static sf::Text metaText;
};
#endif // !JOGO_H