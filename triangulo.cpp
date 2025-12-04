#include <iostream>
#include "triangulo.h"

Triangulo::Triangulo(int x, int y): Figura(x, y) {}

Triangulo::~Triangulo() {}

void Triangulo::desenhar() const
{
    std::cout << "A" ;
}