#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
private:
    sf::Vector2f pos;
    sf::Vector2f tex_pos;
    int rot; //Unit : quarter-turns
    sf::Color color;
public:
    Tile(sf::Vector2f n_pos, sf::Vector2f n_tex_pos, int n_rot, sf::Color n_color);
    void move(sf::Vector2f dir);
    void place(sf::Vector2f n_pos);
    void set_texture(sf::Vector2f n_tex_pos);
    void rotate(int n_rot);
    void set_rot(int n_rot);
    sf::VertexArray *get_quad();
};

#endif // TILE_H
