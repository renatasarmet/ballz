#ifndef FILA_HPP
#define FILA_HPP

#include "pokeball.h"
#include <iostream>


class Fila
{
public:
    
    //CONSTRUTOR
    Fila();
    
    //DESTRUTOR
    ~Fila();
    
    //METODOS
    bool Vazia() const;
    void Insere(pokeball X, bool &DeuCerto);
    void Retira(int &X, bool &DeuCerto);
    void InicializaElementos();
    
    //METODOS GET E SET
    void proximo_primeiro();
    int get_primeiro() const;
    void proximo_ultimo();
    int get_ultimo() const;
    void set_primeiro(int);
    int get_NroElementos() const;
    void diminui_NroElementos();
    void aumenta_NroElementos();
    void set_elemento_ultimo(int);
    int get_elemento_ultimo() const;
    int get_elemento_primeiro() const;
    
    //so para teste
    int get_elemento_X(int X) const;
private:
    
    int Elementos[QUANT_CARTAS];
    int NroElementos;
    int Primeiro;
    int Ultimo;
};



Fila::Fila()
{
    InicializaElementos();
}

Fila::~Fila()
{
}

void Fila::InicializaElementos()
{
    bool DeuCerto;
    
    NroElementos = 0;
    Primeiro = -1;
    Ultimo = -1;
    
    
  }


bool Fila::Vazia() const
{
    if (get_NroElementos() == 0)
        return true;
    else
        return false;
}

void Fila::Insere(int X, bool &DeuCerto)
{
    if (Vazia())
        proximo_primeiro();
        
    DeuCerto = true;
    aumenta_NroElementos();
    proximo_ultimo();
    set_elemento_ultimo(X);
}

void Fila::Retira(int &X, bool &DeuCerto)
{
    if (Vazia())
        DeuCerto = false;
    else
    {
        DeuCerto = true;
        diminui_NroElementos();
        X = get_elemento_primeiro();
        proximo_primeiro();
    }
}

void Fila::proximo_primeiro()
{
    this->Primeiro += 1;
}

void Fila::proximo_ultimo()
{
    this->Ultimo += 1;
}

int Fila::get_primeiro() const
{
    return this->Primeiro;
}

int Fila::get_ultimo() const
{
    return this->Ultimo;
}

void Fila::set_elemento_ultimo(int novo)
{
    this->Elementos[this->Ultimo] = novo;
}

void Fila::diminui_NroElementos()
{
    this->NroElementos -= 1;
}

void Fila::aumenta_NroElementos()
{
    this->NroElementos += 1;
}

int Fila::get_elemento_primeiro() const
{
    return this->Elementos[this->Primeiro];
}

int Fila::get_elemento_ultimo() const
{
    return this->Elementos[this->Ultimo];
}

int Fila::get_NroElementos() const
{
    return this->NroElementos;
}

void Fila::set_primeiro(int X) 
{
    this->Primeiro = X;
}

int Fila::get_elemento_X(int X) const
{
    return this->Elementos[X];
}

#endif /* FILA_HPP */