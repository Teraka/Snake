#ifndef BLOC_H
#define BLOC_H

#include <SFML/Graphics.hpp>
#include "Defines.h"
#include "Tile.h"
#include <iostream>

class Bloc : public Tile
{
private:
    Bloc *prev;
    Bloc *next;
    bool buried;
    int dir;
    void rebind_next(Bloc*);
    void rebind_prev(Bloc*);
    void update();
    friend class Snake;

public:
    Bloc(sf::Vector2f, int, Bloc*, Bloc*, sf::Color, bool);
    ~Bloc();
    void print_bloc();
};

#endif // BLOC_H
