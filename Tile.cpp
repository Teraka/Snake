#include "Tile.h"

Tile::Tile(sf::Vector2f n_pos, sf::Vector2f n_texPos, int n_rot = 0, sf::Color n_color = sf::Color::White)
{
    pos = n_pos;
    texPos = n_texPos;
    rot = n_rot;
    color = n_color;
}

void Tile::move(sf::Vector2f dir)
{
    pos += dir;
}

void Tile::place(sf::Vector2f n_pos)
{
    pos = n_pos;
}

void Tile::setTexture(sf::Vector2f n_texPos)
{
    texPos = n_texPos;
}

void Tile::rotate(int n_rot)
{
    rot += n_rot;
    if (rot < 0)
        rot += 4;
    else
        rot %= 4;
}

void Tile::setRot(int n_rot)
{
    rot = n_rot;
}

sf::Vector2f Tile::getToricPos() //Think about improving that. Probably not the most efficient function ever.
{
    sf::Vector2f result = pos;
    if (pos.x >= D_GRIDSIZE)
        result.x = int(pos.x) % D_GRIDSIZE;
    else while (result.x < 0)
        result.x += D_GRIDSIZE;
    if (pos.y >= D_GRIDSIZE)
        result.y = int(pos.y) % D_GRIDSIZE;
    else while (result.y < 0)
        result.y += D_GRIDSIZE;
    return result;
}

sf::VertexArray Tile::getQuad()
{
    sf::VertexArray quad = sf::VertexArray(sf::Quads, 4);
    sf::Transform t;
    t.scale(D_TILESIZE, D_TILESIZE);
    for (int i = 0; i < 4; i++)
    {
        quad[i].position = t * (intToCorner(i) + getToricPos());
        quad[(i + rot) % 4].texCoords = t * (intToCorner(i) + texPos);
        quad[i].color = color;
    }
    return quad;
}
