#include "menu.h"

Menu::menu_inicial Menu::Mostrar(sf::RenderWindow& window)
{
    //Carrega a imagem do menu de um arquivo
    sf::Texture imagem;
    imagem.loadFromFile("imagens/menu.jpg");
    
    sf::Sprite sprite;
    sprite.setTexture(imagem);
    
    //Areas clicaveis no menu
    
    //coordenadas do botao JOGAR
    Item_Menu botao_jogar;
    botao_jogar.rect.top = 160;
    botao_jogar.rect.height = 250;
    botao_jogar.rect.left = 135;
    botao_jogar.rect.width = 310;
    botao_jogar.action = Jogar;
    
    //Coordenadas do botao SAIR
    Item_Menu botao_sair;
    botao_sair.rect.top = 370;
    botao_sair.rect.height = 435;
    botao_sair.rect.left = 160;
    botao_sair.rect.width = 290;
    botao_sair.action = Sair;
    
    //Coordenadas do botao INSTRUCOES
    Item_Menu botao_instrucoes;
    botao_instrucoes.rect.top = 265;
    botao_instrucoes.rect.height = 340;
    botao_instrucoes.rect.left = 50;
    botao_instrucoes.rect.width = 415;
    botao_instrucoes.action = Instrucoes;
    
    itens_menu.push_back(botao_jogar);
    itens_menu.push_back(botao_sair);
    itens_menu.push_back(botao_instrucoes);
    
    window.draw(sprite);
    window.display();
    
    return obter_resposta_menu(window);
}

Menu::menu_inicial Menu::clique(int x, int y)
{
    std::list<Item_Menu>::iterator it;
    
    for (it = itens_menu.begin(); it != itens_menu.end(); it++)
    {
        sf::Rect<int> item_do_menu = (*it).rect;
        if (item_do_menu.top < y && item_do_menu.height > y && item_do_menu.left < x && item_do_menu.width > x)
            return (*it).action;
    }
    
    return Nada;
}

Menu::menu_inicial Menu::obter_resposta_menu(sf::RenderWindow& window)
{
    sf::Event evento_menu;
    
    while (1 != 0)
    {
        while (window.pollEvent(evento_menu))
        {
            if (evento_menu.type == sf::Event::MouseButtonPressed)
                return clique(int(evento_menu.mouseButton.x), int(evento_menu.mouseButton.y));
            if (evento_menu.type == sf::Event::Closed)
                return Sair;
        }
    }
}