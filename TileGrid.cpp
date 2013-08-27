#include "TileGrid.h"

TileGrid::TileGrid(sf::Vector2f n_size)
{
    size = n_size;
    collisionGrid = new int[int(size.x * size.y)];
    nextGrid = new int[int(size.x * size.y)];
    grid = new Tile[int(size.x * size.y)];
    for (int i = 0; i < size.x * size.y; i++)
    {
        collisionGrid[i] = 0;
        nextGrid[i] = 0;
        grid[i] = Tile(sf::Vector2f(i % int(size.x), i / int(size.x)), sf::Vector2f(0, 0), 0, sf::Color::Blue);
    }
}

bool TileGrid::getCollision(sf::Vector2f coord)
{
    return collisionGrid[int(coord.y * size.y + coord.x)] != 0;
}

void TileGrid::set_at(sf::Vector2f pos, int v)
{
    nextGrid[int(pos.y * size.y + pos.x)] |= 1 << v;
}

void TileGrid::update(sf::Vector2f pos)
{
    int i = collisionGrid[int(pos.y * size.y + pos.x)];
    grid[int(pos.y * size.y + pos.x)].setColor(sf::Color(((i & 0x4) >> 2) * 255, ((i & 0x2) >> 1) * 255, (i & 0x1) * 255));
}

void TileGrid::flip()
{
    int *tmp = collisionGrid;
    collisionGrid = nextGrid;
    nextGrid = tmp;
    for (int i = 0; i < size.x * size.y; i++)
    {
        nextGrid[i] = 0;
        update(sf::Vector2f(i % int(size.x), i / int(size.x)));
    }
}
