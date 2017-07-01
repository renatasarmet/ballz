#ifndef pokeball_H
#define pokeball_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <math.h>
#include "ResourcePath.hpp"

using namespace std;

class pokeball
{
public:
	pokeball();
	virtual ~pokeball();
	void Update(float, bool);

	virtual void pokebola();
	virtual void desenhar(sf::RenderWindow& window);
	virtual void set_posicao();
	virtual void set_estado();
	virtual void set_estado_false();
	virtual bool verifica_estado();
    void set_id(int id);
    int get_id() const;
    
    
    static bool diminuiRestante();
    static void aumentaQtdPokebola();
    static void reiniciaRestante();
    static void reiniciaQtdPokebola();
    
    int get_qtdRestantePokebola() const;
    int get_qtdPokebola() const;

    
    
    void colidiuComOvo(float elapsedTime); //muda a direcao após colisao

	virtual sf::Rect<float> get_bounding_rect();

	virtual float get_x();
	virtual float get_y();

	static double dir;
	static bool lancado;
    static bool colidiuOvo;
    static bool novaRodada;

private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;
	bool existe_pokeball;
    bool pegouNovaPokeball;
    static int qtdPokebola;
    static int qtdRestantePokebola;
    

	sf::Sprite _sprite;
	sf::Texture _imagem;
};
#endif // !pokeball_H
