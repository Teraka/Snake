#ifndef DEFINES_H
#define DEFINES_H
#include <SFML/Graphics.hpp>

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

#define D_BLOCSIZE 21

#endif // DEFINES_H
