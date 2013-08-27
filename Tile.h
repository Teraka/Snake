#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Defines.h"

class Tile
{
protected:
    sf::Vector2f pos;
    sf::Vector2f texPos;
    int rot; //Unit : quarter-turns
    sf::Color color;

public:
    Tile();
    Tile(sf::Vector2f n_pos, sf::Vector2f n_texPos, int n_rot, sf::Color n_color);
    void move(sf::Vector2f dir);
    void place(sf::Vector2f n_pos);
    void setTexture(sf::Vector2f n_texPos);
    void rotate(int n_rot);
    void setRot(int n_rot);
    void setColor(sf::Color n_color);
    void setAlpha(int alpha);
    sf::Vector2f getToricPos();
    sf::VertexArray getQuad();
};

#endif // TILE_H
