#include "figura.h"

#ifndef CIRCULO_H
#define CIRCULO_H

class Circulo: public Figura
{
    private:

    public:
    Circulo(int x=0, int y=0);
    virtual ~Circulo();
    virtual void desenhar() const;

};


#endif