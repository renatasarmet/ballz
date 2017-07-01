#ifndef NODETYPE_HPP
#define NODETYPE_HPP

#include <iostream>
#include <string>
#include "pokeball.h"

using namespace std;

// Nó - Representa um elemento da lista

class Nodetype
{
public:
	//CONSTRUTOR
	Nodetype();

	//DESTRUTOR
	~Nodetype();

	//FUNCOES
	virtual void carregar(std::string nomearquivo);
	virtual void desenhar(sf::RenderWindow& renderWindow);
    virtual bool colidiu(pokeball& _pokeball);

	float get_x() const;
	float get_y() const;

	void set_posicao(float _x, float _y);

	Nodetype* get_next() const;
	void set_next(Nodetype *);
	int get_id() const;
	void set_id(int);
	void CopiaNode(Nodetype *original);
	void set_valor(int);
	int get_valor() const;

	sf::Sprite _sprite;
    static sf::Text valorText;
    
private:
	Nodetype *next;
	int id;
	int valor;
	bool carregou;
    
    sf::Font fonte;
    sf::Texture _imagem;
	std::string nome_arquivo;
};


Nodetype::Nodetype(){
	next = NULL;
	id = 0;
	valor = 0;
    
    
    //LOAD FONT AND TEXT
    fonte.loadFromFile(resourcePath() + "imagens/pokemon.ttf");
    valorText.setCharacterSize(25);
    valorText.setFillColor(sf::Color::Black);
    valorText.setFont(fonte);
    valorText.setOrigin(_sprite.getLocalBounds().width/2, _sprite.getLocalBounds().height/2);
}

Nodetype::~Nodetype(){
    
}

void Nodetype::carregar(std::string nomearquivo)
{
	if (_imagem.loadFromFile(nomearquivo) == false)
	{
		nome_arquivo = "";
		carregou = false;
	}
	else
	{
		nome_arquivo = nomearquivo;
		_sprite.setTexture(_imagem);
		_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
		carregou = true;
	}
}

void Nodetype::desenhar(sf::RenderWindow & renderWindow)
{
    if (carregou){
		renderWindow.draw(_sprite);
        renderWindow.draw(valorText);
    }
    
}

bool Nodetype::colidiu(pokeball& _pokeball)
{
	bool deucerto;
	if (_pokeball.lancado == true)
	{
		if(_sprite.getPosition().x - _sprite.getLocalBounds().width/2 <= _pokeball.get_bounding_rect().left + _pokeball.get_bounding_rect().width
			&& _sprite.getPosition().x + _sprite.getLocalBounds().width / 2  >= _pokeball.get_bounding_rect().left
			&& _sprite.getPosition().y - _sprite.getLocalBounds().height / 2 <= _pokeball.get_bounding_rect().top + _pokeball.get_bounding_rect().height
			&& _sprite.getPosition().y + _sprite.getLocalBounds().height / 2 >= _pokeball.get_bounding_rect().top )
		{
			return true;
        }
	}
	return false;
}

float Nodetype::get_x() const
{
	return _sprite.getPosition().x;
}

 float Nodetype::get_y() const
{
	return _sprite.getPosition().y;
}

void Nodetype::set_posicao(float _x, float _y)
{
	if (carregou)
	{
		_sprite.setPosition(_x, _y);
	}
}

Nodetype* Nodetype::get_next() const{
	return this->next;
}

void Nodetype::set_next(Nodetype *pnext){
	this->next = pnext;
}

int Nodetype::get_id() const{
	return this->id;
}
void Nodetype::set_id(int pid){
	if(pid>=0)
		this->id = pid;
}

void Nodetype::set_valor(int pvalor)
{
    this->valor = pvalor;
}

int Nodetype::get_valor() const
{
    return this->valor;
}


void Nodetype::CopiaNode(Nodetype *original){

	this->set_next(original->get_next());
	this->set_id(original->get_id());
	this->set_valor(original->get_valor());
}



#endif
