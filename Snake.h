#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>
#include "Defines.h"
#include "Bloc.h"
#include <iostream>

//TODO: Separate controls from the step function.
//TODO: Make it so that the snake can't bury while turning, or turn while buried.
//TODO: While head is buried or if it buried at this frame, disregard turn orders.

class Snake : public sf::Drawable, sf::Transformable
{
private:
    static int snake_count;
    Bloc *head;
    Bloc *tail;
    int dir;
    int buried_timer;
    float growth;
    int length;
    sf::Texture *tileset;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::VertexArray vertices(sf::Quads, length*4);
        Bloc *current = tail;
        for (int b = 0; current != NULL; b++)
        {
            //current->print_bloc();
            //current->blit_quad(vertices, b*4);
            sf::VertexArray tmp = current->getQuad();
            for (int i = 0; i < 4; i++)
                vertices.append(tmp[i]);
            current = current->prev;
        }
        states.transform *= getTransform();
        states.texture = tileset;
        target.draw(vertices, states);
    }

public:
    Snake(sf::Vector2f, Direction, sf::Texture*, sf::Color); //param: Initial pos, dir, color and tileset
    void grow(int); //makes the snake grow by that size (or shrink if param is negative)
    void step(int); //param: Commands (bit field)
    int getLength() {return length;} //Debug
};

#endif // SNAKE_H
