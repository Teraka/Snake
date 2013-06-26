#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>
#include "Defines.h"
#include "Bloc.h"

class Snake : public sf::Drawable, sf::Transformable
{
private:
    static int snake_count;
    Bloc *head;
    Bloc *tail;
    Direction dir;
    int buried_timer;
    float growth;
    int length;
    sf::Texture *texture;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::VertexArray vertices(sf::Quads, length*4);
        Bloc *current = head;
        for (int b=0; current != NULL; b++)
        {
            current->blit_quad(vertices, b*4);
            current = current->next;
        }
        states.transform *= getTransform();
        states.texture = texture;
        target.draw(vertices, states);
    }

public:
    Snake(sf::Vector2i, Direction); //param: Initial pos and dir
    void step(int); //param: Commands (bit field)
};

#endif // SNAKE_H
