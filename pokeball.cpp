#include "pokeball.h"

pokeball::pokeball() :_velocity(50.f), _elapsedTimeSinceStart(0.0f)
{
	existe_pokeball = true;
    colidiuOvo = false;
}

pokeball::~pokeball()
{
	existe_pokeball = false;
}

void pokeball::Update(float elapsedTime, bool colidiuOvo)
{
	_elapsedTimeSinceStart += elapsedTime;

	float moveAmount = _velocity * elapsedTime;

	float moveByX = (10 * cos(dir)) * moveAmount;
	float moveByY = (10 * sin(dir)) * moveAmount;

    
    
    if(colidiuOvo == true){
        pokeball::colidiuOvo = false;
        cout << colidiuOvo << endl;
        dir = 360.0f - (dir - 180.0f);
        moveByY = -moveByY;
    }
    
    
    if (lancado && (_sprite.getPosition().x <= 0)){
        //_sprite.setPosition(450, _sprite.getPosition().y);
        dir = dir + 90.0f;
        moveByX = - moveByX;
        moveByY = - moveByY;
    }
    else if (lancado && (_sprite.getPosition().x >= 400)){
        //_sprite.setPosition(0, _sprite.getPosition().y);
        dir = dir - 90.0f;
        moveByY = - moveByY;
        moveByX = - moveByX;
    }

    
    if (lancado && (_sprite.getPosition().y <= 0)){
        lancado = false;
        novaRodada = true;
        //cout << "rodada atual: " << jogo::rodadaAtual << endl;
    }
    
    else if (lancado &&(_sprite.getPosition().y >= 580)){
        dir = 360.0f - (dir - 180.0f);
//        if(dir > 260.0f && dir < 280.0f) dir += 20.0f;
//        if(dir > 80.0f && dir < 100.0f) dir += 20.0f;
        moveByY = -moveByY;
    }
    
    _sprite.move(moveByX, moveByY);
}

void pokeball::pokebola()
{
	if (existe_pokeball)
	{
		_imagem.loadFromFile(resourcePath() + "imagens/pokebola.png");
		_sprite.setTexture(_imagem);
		_sprite.setPosition(10 * cos(dir) + 225, 10 * sin(dir) + 50);
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

//void pokeball::colidiuComOvo(float elapsedTime){
//    cout << "colidiu com ovo" << endl;
//    colidiuOvo = true;
//    Update(elapsedTime, colidiuOvo);
//}


