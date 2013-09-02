#ifndef TILEGRID_H
#define TILEGRID_H

#include <SFML/Graphics.hpp>
#include "Defines.h"
#include "Tile.h"

class TileGrid : public sf::Drawable, sf::Transformable
{
private:
    Tile *tileGrid;
    int *collisionGrid;
    int *nextGrid;
    int removed; //Bitmap of all bits to remove in the next iteration.
    sf::Vector2f size;
    void update(sf::Vector2f pos); //Debug

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::VertexArray vertices(sf::Quads, size.x * size.y * 4);
        for (int i = 0; i < size.x * size.y; i++)
        {
            sf::VertexArray tmp = tileGrid[i].getQuad();
            for (int i = 0; i < 4; i++)
                vertices.append(tmp[i]);
        }
        states.transform *= getTransform();
        states.texture = NULL;
        target.draw(vertices, states);
    }

public:
    TileGrid(sf::Vector2f n_size);
    void set_at(sf::Vector2f pos, int v);
    int getCollision(sf::Vector2f pos);
    void flip();
};

#endif // TILEGRID_H
