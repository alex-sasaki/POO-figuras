#ifndef FIGURA_H
#define FIGURA_H

class Figura
{
    private:
        int x;
        int y;

    public:
        Figura(int x=0, int y=0);
        virtual ~Figura();


        void set_x(int x);
        void set_y(int y);
        void set_posicao(int x, int y);

        int get_x() const;
        int get_y() const;

        virtual void desenhar() const = 0;
};

#endif