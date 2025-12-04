#include "figura.h"

#ifndef TRIANGULO_H
#define TRIANGULO_H

class Triangulo : public Figura
{
    private:

    public:
    Triangulo(int x=0, int y=0);
    virtual ~Triangulo();

    virtual void desenhar() const;
};

#endif