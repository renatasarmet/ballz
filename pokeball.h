#ifndef pokeball_H
#define pokeball_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <math.h>


using namespace std;

class pokeball
{
public:
	pokeball();
	virtual ~pokeball();
	void Update(float);

	virtual void pokebola();
	virtual void desenhar(sf::RenderWindow& window);
	virtual void set_posicao();
	virtual void set_estado();
	virtual void set_estado_false();
	virtual bool verifica_estado();

	virtual sf::Rect<float> get_bounding_rect();

	virtual float get_x();
	virtual float get_y();

	static double dir;
	static bool lancado;

private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;
	bool existe_pokeball;

	sf::Sprite _sprite;
	sf::Texture _imagem;
};
#endif // !pokeball_H
