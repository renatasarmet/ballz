//
//  instrucoes.cpp
//  HarryApp
//
//  Created by Renata Sarmet Smiderle Mendes on 22/06/17.
//  Copyright © 2017 Renata Sarmet Smiderle Mendes. All rights reserved.
//

#include "instrucoes.h"

Instrucoes::instrucoes_opcoes Instrucoes::Mostrar(sf::RenderWindow& window)
{       
    std::string aux2 = std::to_string(get_k());
    aux2 =  "imagens/tutorial" + aux2 + ".jpg";

    imagem_tutorial.loadFromFile(aux2);
    tutorial.setTexture(imagem_tutorial);

	sf::Sprite sprite;
	sprite.setTexture(imagem_tutorial);
    
    //Areas clicaveis
    
    //coordenadas do botao JOGAR
    Item_Instrucoes botao_jogar;
    botao_jogar.rect.top = 460;
    botao_jogar.rect.height = 500;
    botao_jogar.rect.left = 190;
    botao_jogar.rect.width = 260;
    botao_jogar.action = Jogar;
    
    //coordenadas do botao PROXIMO
    Item_Instrucoes botao_proximo;
    botao_proximo.rect.top = 430;
    botao_proximo.rect.height = 460;
    botao_proximo.rect.left = 330;
    botao_proximo.rect.width = 435;
    botao_proximo.action = Proximo;
    
    //coordenadas do botao ANTERIOR
    Item_Instrucoes botao_anterior;
    botao_anterior.rect.top = 430;
    botao_anterior.rect.height = 460;
    botao_anterior.rect.left = 6;
    botao_anterior.rect.width = 120;
    botao_anterior.action = Anterior;
    
    //Coordenadas do botao VOLTAR
    Item_Instrucoes botao_menu;
    botao_menu.rect.top = 515;
    botao_menu.rect.height = 540;
    botao_menu.rect.left = 200;
    botao_menu.rect.width = 250;
    botao_menu.action = Menu;
    
    itens_instrucao.push_back(botao_jogar);
    itens_instrucao.push_back(botao_menu);
	itens_instrucao.push_back(botao_proximo);
	itens_instrucao.push_back(botao_anterior);
    
    window.draw(sprite);
    window.display();
    
    return obter_resposta_instrucao(window);
}

void Instrucoes::set_k(int j)
{
    if((j >= 1) && (j < QUANT_INSTRUCOES))
        k = j;
}

void Instrucoes::proximo_k()
{
    if(k<QUANT_INSTRUCOES)
        k = k + 1;
}

void Instrucoes::anterior_k()
{
    if(k>1)
        k = k - 1;
}

int Instrucoes::get_k() const
{
    return k;
}

Instrucoes::instrucoes_opcoes Instrucoes::clique(int x, int y)
{
    std::list<Item_Instrucoes>::iterator it;
    
    for (it = itens_instrucao.begin(); it != itens_instrucao.end(); it++)
    {
        sf::Rect<int> item_da_instrucao = (*it).rect;
        if (item_da_instrucao.top < y && item_da_instrucao.height > y && item_da_instrucao.left < x && item_da_instrucao.width > x)
            return (*it).action;
    }
    
    return Nada;
}

Instrucoes::instrucoes_opcoes Instrucoes::obter_resposta_instrucao(sf::RenderWindow& window)
{
    sf::Event evento_instrucao;
    
    while (1 != 0)
    {
        while (window.pollEvent(evento_instrucao))
        {
            if (evento_instrucao.type == sf::Event::MouseButtonPressed)
                return clique(int(evento_instrucao.mouseButton.x), int(evento_instrucao.mouseButton.y));
            if (evento_instrucao.type == sf::Event::Closed)
                return Sair;
        }
    }
}