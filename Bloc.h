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
    Bloc_type type;
    bool buried;
    void rebind_next(Bloc*);
    void rebind_prev(Bloc*);
    void update();
    friend class Snake;

public:
    Bloc(sf::Vector2f, Bloc*, Bloc*, sf::Color, bool);
    ~Bloc();
    void print_bloc();
//Think about where to implement the rebind function. Could be either in bloc class, in bloc module or in snake class.
};

#endif // BLOC_H
