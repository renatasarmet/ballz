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
    static void Start(Plano* plano, braco* hook);
    static void CriandoTudo();
    static void JogarNovamente(Plano* plano, braco* hook);
    
    static int rodadaAtual;
    
private:
    static bool IsExiting();
    static void loop_jogo( Plano* plano, braco* hook);
    
    static void mostrar_tela_inicial();
    static void mostrar_menu();
	static void mostrar_instrucao();
    static void mostrar_perdeu( Plano* plano, braco* hook);
  
    static void verifica_colisao(Plano* plano, braco* hook);
    
    enum GameState {
        Inicializado, Mostrando_Tela_Inicial, Pausado, Mostrando_Menu, Jogando, Saindo, Perdendo, Mostrando_Instrucao, Mostrando_Transicao_Passou, Mostrando_Transicao_Horcrux, Nova_Fase, Fase_Final
    }; // estado que o jogo pode estar durante a partida
    
    static GameState estado_jogo;
    static sf::RenderWindow janela;
    static sf::Sprite background;
    static sf::Text nivelText;
    static sf::Text pokebolaText;
	static pokeball pokebola;


};
#endif // !JOGO_H