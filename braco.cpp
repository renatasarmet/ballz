#include "braco.h"

braco::braco() : _velocity(20.f), _elapsedTimeSinceStart(0.0f)
{
	direcao_rotacao = 0.25;
}

braco::~braco()
{
}

void braco::update()
{
	_sprite.setRotation(_sprite.getRotation() + direcao_rotacao);
	if (_sprite.getRotation() == 70 || _sprite.getRotation() == 290)
	{
		direcao_rotacao = - direcao_rotacao;
	}
}

void braco::update_todos()
{
	timeDelta = clock.restart().asSeconds();
    _pokeball.Update(timeDelta, pokeball::colidiuOvo);
}

void braco::desenhar(sf::RenderWindow& renderWindow)
{
	_imagem.loadFromFile("imagens/braco.png");
	_sprite.setTexture(_imagem);
	_sprite.setPosition(225, 50);
	_sprite.setOrigin(8, 2);

	switch (_estado_braco)
	{
	case braco::Rotacionando:
		update();
		break;
	case braco::Pokebola_Lancada:
		_pokeball.pokebola();
		_pokeball.set_estado();
		_pokeball.set_posicao();
		_estado_braco = braco::Rotacionando;
		break;
	case braco::Acertou:
		_estado_braco = braco::Rotacionando;
	default:
		break;
	}

	renderWindow.draw(_sprite);
	_pokeball.desenhar(renderWindow);
}

float braco::get_rotacao() const
{
	return _sprite.getRotation();
}

