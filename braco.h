#ifndef BRACO_H
#define BRACO_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "pokeball.h"

using namespace std;

class braco
{
public:
	//CONSTRUTOR
	braco();

	//DESTRUTOR
	~braco();

	void update_todos();
	void update();

	enum estado_braco {
		Rotacionando, Pokebola_Lancada, Acertou
	}; // estado que o jogo pode estar durante a partida

	virtual void desenhar(sf::RenderWindow& window);

	virtual float get_rotacao() const;

	pokeball _pokeball;

	sf::Sprite _sprite;

	static estado_braco _estado_braco;

private:
	sf::Sprite pokeball;
	sf::Texture _imagem;
	std::string nome_arquivo;
	float direcao_rotacao;

	sf::Clock clock;
	float timeDelta;

	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;
};
#endif
