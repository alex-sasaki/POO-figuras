#include "circulo.h"
#include <iostream>

Circulo::Circulo(int x, int y): Figura(x, y) {}

Circulo::~Circulo() {}

void Circulo::desenhar() const
{
    std::cout << "o";
}

