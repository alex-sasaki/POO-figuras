#include "figura.h"
#include <iostream>


Figura::Figura(int x, int y): x(x), y(y) {}

Figura::~Figura()
{

}

void Figura::set_posicao(int x, int y)
{
    set_x(x);
    set_y(y);

    return ;
}

int Figura::get_x() const
{
    return x;
}

int Figura::get_y() const
{
    return y;
}

void Figura::set_x(int x)
{
    this->x = x;
}

void Figura::set_y(int y)
{
    this->y = y;
}
