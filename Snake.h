#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include "Defines.h"
#include "Bloc.h"
#include "TileGrid.h"
#include <iostream>

#define DEATH_GROWTH_RATE -1/3.0

//NOTE: You can use function pointers to make different resurrection conditions.

class Snake : public sf::Drawable, sf::Transformable
{
public: //Change that back to private later, setting to public now for debugging purposes.
    static int snake_count;
    int id;
    Bloc *head;
    Bloc *tail;
    intArray commandList;
    int lastCommand;
    int *frame;
    int prev_dir;
    int dir;
    int next_dir;
    bool changed_dir;
    int buried_timer;
    float growth;
    int length;
    bool alive;
    TileGrid *collisionGrid;
    sf::Texture *tileset;
    void updateCollisionGrid();

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
    Snake(int *, TileGrid *, sf::Vector2f, Direction, sf::Texture*, sf::Color); //param: Initial pos, dir, color and tileset
    void grow(float); //makes the snake grow by that size (or shrink if param is negative)
    void step(); //param: Commands (bit field)
    void turn(int n_dir , bool bypass = false);
    void bury();
    void printSnake();
    int getLength() {return length;} //Debug
};

#endif // SNAKE_H
