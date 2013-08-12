#include "Tile.h"

Tile::Tile(sf::Vector2f n_pos, sf::Vector2f n_tex_pos, int n_rot = 0, sf::Color n_color = sf::Color.White)
{
    pos = n_pos;
    tex_pos = n_tex_pos;
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

void Tile::set_texture(sf::Vector2f n_tex_pos)
{
    tex_pos = n_tex_pos;
}

void Tile::rotate(int n_rot)
{
    rot += n_rot;
    if (rot < 0)
        rot += 4;
    else
        rot %= 4;
}

void Tile::set_rot(int n_rot)
{
    rot = n_rot;
}

sf::VertexArray *get_quad()
{
    sf::VertexArray *quad = new sf::VertexArray(sf::Quads, 4);
    for (int i = 0; i < 4; i++)
    {
        quad[(i + rot) % 4].position = (int_to_corner(i) + pos) * D_TILESIZE;
        quad[i].texCoords = (int_to_corner(i) + tex_pos) * D_TILESIZE;
        quad[i].color = color;
    }
    return quad;
}
