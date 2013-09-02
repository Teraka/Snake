#include "TileGrid.h"
#define TG_LENGTH int(size.x * size.y)
#define TG_INTTOCOORD(i) sf::Vector2f(i % int(size.x), i / int(size.x))
#define TG_COORDTOINT(v) int(v.y) * int(size.y) + int(v.x)

TileGrid::TileGrid(sf::Vector2f n_size)
{
    size = n_size;
    collisionGrid = new int[TG_LENGTH];
    nextGrid = new int[TG_LENGTH];
    tileGrid = new Tile[TG_LENGTH];
    for (int i = 0; i < TG_LENGTH; i++)
    {
        collisionGrid[i] = 0;
        nextGrid[i] = 0;
        tileGrid[i] = Tile(TG_INTTOCOORD(i), sf::Vector2f(0, 0), 0, sf::Color::Blue);
    }
}

int TileGrid::getCollision(sf::Vector2f pos)
{
    return collisionGrid[TG_COORDTOINT(pos)];
}

void TileGrid::set_at(sf::Vector2f pos, int v)
{
    nextGrid[TG_COORDTOINT(pos)] |= 1 << v;
}

void TileGrid::update(sf::Vector2f pos)
{
    int i = collisionGrid[TG_COORDTOINT(pos)];
    tileGrid[TG_COORDTOINT(pos)].setColor(sf::Color(((i & 0x4) >> 2) * 255, ((i & 0x2) >> 1) * 255, (i & 0x1) * 255));
}

void TileGrid::flip()
{
    int *tmp = collisionGrid;
    collisionGrid = nextGrid;
    nextGrid = tmp;
    for (int i = 0; i < TG_LENGTH; i++)
    {
        nextGrid[i] = 0;
        //update(TG_INTTOCOORD(i));
    }
}
