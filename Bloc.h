#ifndef BLOC_H
#define BLOC_H
#include <SFML/Graphics.hpp>
#include "Defines.h"
#include <iostream>

class Bloc
{
private:
    Bloc *prev;
    Bloc *next;
    sf::Vector2f pos;
    Bloc_type type;
    bool buried;
    int rot;
    sf::Color color; //Think about whether to implement this here or in the snake's draw function.
    void rebind_next(Bloc*);
    void rebind_prev(Bloc*);
    void update();
    void blit_quad(sf::VertexArray&, int); //Blits its own quad in the array starting from the position given by the int.
    friend class Snake;

public:
    Bloc(sf::Vector2f, Bloc*, Bloc*, sf::Color, bool);
    ~Bloc();
    void print_bloc();
//Think about where to implement the rebind function. Could be either in bloc class, in bloc module or in snake class.
};

#endif // BLOC_H
