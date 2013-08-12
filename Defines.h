#ifndef DEFINES_H
#define DEFINES_H
#include <SFML/Graphics.hpp>

//These will eventually have to go in a parameter class.
#define D_TILESIZE 25
#define D_MIN_SNAKE_LENGTH 3
#define D_BURIED_TIME 2

enum Bloc_type
{
    bt_head,
    bt_tail,
    bt_straight,
    bt_corner,
    bt_buried,
    bt_burying,
    bt_unburying,
    bt_disconnected_front,
    bt_disconnected_back
};

enum Direction
{
    d_up,
    d_right,
    d_down,
    d_left
};

inline sf::Vector2f int_to_dir(int i)
{
    switch(i)
    {
    case d_up:
        return sf::Vector2f(0, -1);
    case d_right:
        return sf::Vector2f(1, 0);
    case d_down:
        return sf::Vector2f(0, 1);
    case d_left:
        return sf::Vector2f(-1, 0);
    }
}

inline sf::Vector2f int_to_corner(int i)
{
    switch(i)
    {
    case 0:
        return sf::Vector2f(0, 0);
    case 1:
        return sf::Vector2f(1, 0);
    case 2:
        return sf::Vector2f(1, 1);
    case 3:
        return sf::Vector2f(0, 1);
    }
}

inline sf::Vector2f tile_pos_to_coords(sf::Vector2f tile_pos)
{
    return sf::Vector2f(tile_pos.x * D_TILESIZE, tile_pos.y * D_TILESIZE);
}


#define print_vertex(v) "[" << v.position.x << "," << v.position.y << "]"

#endif // DEFINES_H
