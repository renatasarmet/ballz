#include "pokeball.h"

pokeball::pokeball() :_velocity(50.f), _elapsedTimeSinceStart(0.0f)
{
	existe_pokeball = true;
}

pokeball::~pokeball()
{
	existe_pokeball = false;
}

void pokeball::Update(float elapsedTime)
{
	_elapsedTimeSinceStart += elapsedTime;

	float moveAmount = _velocity * elapsedTime;

	float moveByX = (10 * sin(dir)) * moveAmount;
	float moveByY =  (10 * cos(dir)) * moveAmount;

	if (_sprite.getPosition().x + moveByX <= 0 + (_sprite.getLocalBounds().width) / 2 || _sprite.getPosition().x + (_sprite.getLocalBounds().height) / 2 + moveByX >= 450
		|| _sprite.getPosition().y + moveByY <= 0 + (_sprite.getLocalBounds().height) / 2 || _sprite.getPosition().y + (_sprite.getLocalBounds().width) / 2 + moveByY >= 600)
		lancado = false;

	_sprite.move(moveByX, moveByY);
}

void pokeball::pokebola()
{
	if (existe_pokeball)
	{
		_imagem.loadFromFile("imagens/pokebola.png");
		_sprite.setTexture(_imagem);
		_sprite.setPosition(10 * cos(dir) + 230, 10 * sin(dir) + 490);
	}
}

void pokeball::desenhar(sf::RenderWindow & window)
{
	window.draw(_sprite);
}

void pokeball::set_posicao()
{
	_sprite.setPosition(_sprite.getPosition().x + 2 * cos(dir), _sprite.getPosition().y + 2 * sin(dir));
}

void pokeball::set_estado()
{
	lancado = true;
}

void pokeball::set_estado_false()
{
	lancado = false;
}

bool pokeball::verifica_estado()
{
	return existe_pokeball;
}

sf::Rect<float> pokeball::get_bounding_rect()
{
	sf::Vector2f position = _sprite.getPosition();

	return sf::Rect<float>(position.x - _sprite.getGlobalBounds().width / 2, position.y - _sprite.getGlobalBounds().height / 2, _sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
}

float pokeball::get_x()
{
	return _sprite.getPosition().x;
}

float pokeball::get_y()
{
	return _sprite.getPosition().y;
}



