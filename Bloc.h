#ifndef BLOC_H
#define BLOC_H
#include <SFML/Graphics.hpp>
#include "Defines.h"

class Bloc
{
private:
    Bloc *prev;
    Bloc *next;
    sf::Vector2i pos;
    Bloc_type type;
    bool buried;
    int rot;
    sf::Color color; //Think about whether to implement this here or in the snake's draw function.
    friend class Snake;

public:
    Bloc()
    void update();
    void rebind_next(Bloc*);
    void rebind_prev(Bloc*);
    void set_pos(sf::Vector2i);
    sf::Vector2i get_pos();
    void set_buried(bool);
    void blit_quad(sf::VertexArray&, int); //Blits its own quad in the array starting from the position given by the int.
//Think about where to implement the rebind function. Could be either in bloc class, in bloc module or in snake class.
};

#endif // BLOC_H
