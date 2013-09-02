#ifndef DEFINES_H
#define DEFINES_H

#include <SFML/Graphics.hpp>
#include <iostream>

//These will eventually have to go in a parameter class.
#define D_TILESIZE 25
#define D_GRIDSIZE 30
#define D_MIN_SNAKE_LENGTH 5

#define D_BURIED_TIME 1
#define D_BURY_COOLDOWN 2

#define DEATH_GROWTH_RATE -1

enum Bloc_type
{
    bt_null,
    bt_head,
    bt_tail,
    bt_straight,
    bt_corner,
    bt_disconnected_front,
    bt_disconnected_back
};

enum Overlay
{
    ov_null = 0x0,
    ov_buried = 0x8,
    ov_burying = 0x10,
    ov_unburying = 0x18
};

enum Direction
{
    d_up,
    d_right,
    d_down,
    d_left
};

inline sf::Vector2f intToDir(int i)
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

inline sf::Vector2f intToCorner(int i)
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

inline sf::Vector2f tilePosToCoords(sf::Vector2f tile_pos)
{
    return sf::Vector2f(tile_pos.x * D_TILESIZE, tile_pos.y * D_TILESIZE);
}

class intArray
{
static const int arraySize = 10;
private:
    int *l;
    intArray *next;
public:
    int index;
    intArray()
    {
        l = new int[arraySize];
        for (int i = 0; i < arraySize; i++)
            l[i] = 0;
        index = 0;
        next = NULL;
    }
    /*int operator[] (int i)
    {
        if (i >= arraySize)
        {
            if (!next)
                next = new intArray();
            return next[i-arraySize];
        }
        else return l[i];
    }*/
    int get(int i)
    {
        if (i >= arraySize)
        {
            if (!next)
                next = new intArray();
            return next->get(i-arraySize);
        }
        else return l[i];
    }
    void set(int i, int v)
    {
        if (i >= arraySize)
        {
            if (!next)
                next = new intArray();
            next->set(i-arraySize, v);
        }
        else l[i] = v;
    }
    void append(int v)
    {
        if (index >= arraySize)
        {
            if (!next)
                next = new intArray();
            next->append(v);
        }
        else l[index] = v;
        index++;
    }
    void printList()
    {
        std::cout << "[t:" << this << ",n:" << next << "]" << std::endl;
        for (int i = 0; i < arraySize; i++)
        {
            std::cout << "l[" << i << "]:" << l[i] << std::endl;
        }
        std::cout << std::endl;
    }
};

#define print_vertex(v) "[" << v.position.x << "," << v.position.y << "]"

#endif // DEFINES_H
