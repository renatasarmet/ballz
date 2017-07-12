#include "pokeball.h"

pokeball::pokeball() :_velocity(50.f), _elapsedTimeSinceStart(0.0f)
{
	existe_pokeball = true;
    colidiuOvo = false;
    qtdRestantePokebola = 1;
    qtdPokebola = 1;
    colidiuEmCimaOuBaixoOvo = false;
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
        if(pokeball::colidiuEmCimaOuBaixoOvo == true){
            dir = 2 * M_PI - dir;
            moveByY = -moveByY;
            pokeball::colidiuEmCimaOuBaixoOvo = false;
        }
        else{ // BATEU NA LATERAL
            dir = M_PI - dir;
            moveByX = - moveByX;
        }
    }
    
    
    if (lancado && (_sprite.getPosition().x <= 0)){
        _sprite.setPosition(1,_sprite.getPosition().y);
       dir = M_PI - dir;
        moveByX = - moveByX;
    }
    
    
    else if (lancado && (_sprite.getPosition().x >= 440)){
        _sprite.setPosition(439,_sprite.getPosition().y);
        dir = M_PI - dir;
        moveByX = - moveByX;
    }

    
    if (lancado && (_sprite.getPosition().y <= 0)){
        lancado = false;
        if (!diminuiRestante()){
            novaRodada = true;
        }
    }
    
    else if (lancado &&(_sprite.getPosition().y >= 580)){
            _sprite.setPosition(_sprite.getPosition().x, 579);
            dir = 2 * M_PI - dir;
            moveByY = -moveByY;
        
    }
    
    _sprite.move(moveByX, moveByY);
}

void pokeball::pokebola()
{
	if (existe_pokeball)
	{
		_imagem.loadFromFile("imagens/pokebola.png");
		_sprite.setTexture(_imagem);
		_sprite.setPosition(10 * cos(dir) + 225, 10 * sin(dir) + 50);
	}
    
    pegouNovaPokeball = 0;
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

bool pokeball::diminuiRestante(){
    qtdRestantePokebola -= 1;
    if(qtdRestantePokebola > 0)
        return true;
    
    else {
        reiniciaRestante();
        return false;
    }
}

void pokeball::aumentaQtdPokebola(){
    qtdPokebola += 1;
}


void pokeball::reiniciaRestante(){
    qtdRestantePokebola = qtdPokebola;
}


int pokeball::get_qtdRestantePokebola() const{
    return qtdRestantePokebola;
}

int pokeball::get_qtdPokebola() const{
    return qtdPokebola;
}


void pokeball::reiniciaQtdPokebola(){
    qtdPokebola = 1;
}
