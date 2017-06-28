#ifndef NODETYPE_HPP
#define NODETYPE_HPP

//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
//#include "feitico.h"

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
//	virtual void carregar(std::string nomearquivo);
//	virtual void desenhar(sf::RenderWindow& renderWindow);
//	virtual bool colidiu(feitico& _feitico);

	float get_x() const;
	float get_y() const;

	void set_posicao(float _x, float _y);
	void set_origem(float x, float y);
	//virtual void move(float x, float y);

//	virtual sf::Rect<float> get_bounding_rect();

	Nodetype* get_next() const;
	void set_next(Nodetype *);
//	string get_info() const;
//	void set_info(string);
	int get_id() const;
	void set_id(int);
	void ExibeInformacoes() const;
	void CopiaNode(Nodetype *original);
	void set_valor(int);
	int get_valor() const;

//	sf::Sprite _sprite;

private:
	Nodetype *next;
	int id;
	int valor;
	//string info;
//	bool carregou;
//	sf::Texture _imagem;
	//std::string nome_arquivo;
	float x, y; // vai ter q apagar o x e y depois
};


Nodetype::Nodetype(){
	next = NULL;
	id = 0;
	//info = "vazia";
	valor = 0;
	x = 0;
	y = 0;
}

Nodetype::~Nodetype(){
	//cout << "GAME OVER NO DESTRUTOR DO ID = " << get_id() <<endl;
}

//void Nodetype::carregar(std::string nomearquivo)
//{
//	if (_imagem.loadFromFile(nomearquivo) == false)
//	{
//		nome_arquivo = "";
//		carregou = false;
//	}
//	else
//	{
//		nome_arquivo = nomearquivo;
//		_sprite.setTexture(_imagem);
//		carregou = true;
//	}
//}

//void Nodetype::desenhar(sf::RenderWindow & renderWindow)
//{
//    if (carregou)
//		renderWindow.draw(_sprite);
//}

//bool Nodetype::colidiu(feitico& _feitico)
//{
//	if (_feitico.lancado == true)
//	{
//		if(_sprite.getPosition().x - _sprite.getLocalBounds().width/2 <= _feitico.get_bounding_rect().left + _feitico.get_bounding_rect().width
//			&& _sprite.getPosition().x + _sprite.getLocalBounds().width / 2  >= _feitico.get_bounding_rect().left
//			&& _sprite.getPosition().y - _sprite.getLocalBounds().height / 2 <= _feitico.get_bounding_rect().top + _feitico.get_bounding_rect().height
//			&& _sprite.getPosition().y + _sprite.getLocalBounds().height / 2 >= _feitico.get_bounding_rect().top )
//		{
//
//			return true;
//		}
//	}
//	return false;
//}

float Nodetype::get_x() const
{
	//return _sprite.getPosition().x;
	return x;
}

 float Nodetype::get_y() const
{
	//return _sprite.getPosition().y;
	 return y;
}

void Nodetype::set_posicao(float _x, float _y)
{
//	if (carregou)
//		_sprite.setPosition(x, y);

	this->x = _x;
	this->y = _y;

	//ESSA PARTE VAI SER ALTERADA NA PARTE GRAFICA
}

void Nodetype::set_origem(float x, float y)
{
//	_sprite.setOrigin(x, y);
}

//void Nodetype::move(float x, float y)
//{
//	//_sprite.move(x, y);
//	// DAR UMA OLHADA
//}

//sf::Rect<float> Nodetype::get_bounding_rect()
//{
//	sf::Vector2f position = _sprite.getPosition();
//
//	return sf::Rect<float>(position.x - _sprite.getGlobalBounds().width / 2, position.y - _sprite.getGlobalBounds().height / 2, _sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
//}

Nodetype* Nodetype::get_next() const{
	return this->next;
}

void Nodetype::set_next(Nodetype *pnext){
	this->next = pnext;
}
//string Nodetype::get_info() const{
//	return this->info;
//}
//void Nodetype::set_info(string pinfo){
//	this->info = pinfo;
//}
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

void Nodetype::ExibeInformacoes() const{
	cout << "ID = " << get_id() << endl;
	//cout << "INFO = " << get_info() << endl;
	cout << "NEXT = " << get_next() << endl;
	cout << "VALOR = " << get_valor() << endl;
}

void Nodetype::CopiaNode(Nodetype *original){

	this->set_next(original->get_next());
   // cout << endl << endl << "NEXT = " << this->get_next()->get_info() << endl;
	this->set_id(original->get_id());
   // cout << "ID = " << this->get_id() << endl;
//	this->set_info(original->get_info());
//    //cout << "INFO = " << this->get_info() << endl;
	this->set_valor(original->get_valor());
    //cout << "VALOR = " << this->get_valor() << endl;
}



#endif
