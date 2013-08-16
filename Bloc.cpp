#include "Bloc.h"

#define getTexPos(x) sf::Vector2f(type & 0x7, type >> 3)

/*
Think a lot about how to update blocs as little as necessary.
*/

void Bloc::print_bloc()
{
    std::cout << "[t:" << this << "],[" << pos.x << "," << pos.y << "]," << buried << std::endl;
    std::cout << "[p:" << prev << "],[n:" << next << "]" << std::endl << std::endl;
}

Bloc::Bloc(sf::Vector2f n_pos, Bloc* n_prev, Bloc* n_next, sf::Color n_color, bool n_buried) : Tile(n_pos, sf::Vector2f(0, 0), 0, n_color)
{
    buried = n_buried;
    next = NULL;
    prev = NULL;
    rebind_next(n_next);
    rebind_prev(n_prev);
    update();
}

Bloc::~Bloc()
{
    rebind_next(NULL);
    rebind_prev(NULL);
}

//TODO: Tail appears normal where it should be burying. Try to find a way to display the hole above
//the snake rather than having different sprites.
void Bloc::update() //Bloc type and rotation are *only* used for the sprite.
{
    //Defining bloc type
    int type;
    if (prev == NULL && next == NULL) type = bt_null;
    else if (prev == NULL) type = bt_head;
    else if (next == NULL) type = bt_tail;
    else if (abs(pos.x - next->pos.x) +
             abs(pos.y - next->pos.y) != 1) type = bt_disconnected_front;
    else if (abs(pos.x - prev->pos.x) +
             abs(pos.y - prev->pos.y) != 1) type = bt_disconnected_back;
    else if ((next->pos.x + prev->pos.x)/2.0 == pos.x) type = bt_straight;
    else type = bt_corner;

    if (buried) type |= ov_buried;
    else if (prev != NULL && prev -> buried) type |= ov_burying;
    else if (next != NULL && next -> buried) type |= ov_unburying;

    texPos = getTexPos(type);

    //Defining rotation
    switch(type)
    {
    case bt_head:
    case bt_disconnected_front:
        if (pos.y < next->pos.y) rot = 0;
        else if (pos.x > next->pos.x) rot = 3;
        else if (pos.y > next->pos.y) rot = 2;
        else rot = 1;
        break;
    case bt_tail:
    case bt_disconnected_back:
        if (pos.y > prev->pos.y) rot = 0;
        else if (pos.x < prev->pos.x) rot = 3;
        else if (pos.y < prev->pos.y) rot = 2;
        else rot = 1;
        break;
    case bt_straight:
        if (pos.x == next->pos.x) rot = 0;
        else rot = 1;
        break;
    case bt_corner:
        float ax = (pos.x + next->pos.x + prev->pos.x)/3.0;
        float ay = (pos.y + next->pos.y + prev->pos.y)/3.0;
        if (ax > pos.x && ay < pos.y) rot = 0;
        else if (ax > pos.x && ay > pos.y) rot = 3;
        else if (ax < pos.x && ay > pos.y) rot = 2;
        else rot = 1;
        break;
    }
}

void Bloc::rebind_next(Bloc *n_next)
{
    if (next != NULL) //If there is a next bloc
        next->prev = NULL; //Unbind this from next
    next = n_next; //Bind new next to this
    if (next != NULL) //If new next is a bloc
        next->prev = this; //Rebind next bloc to this
}

void Bloc::rebind_prev(Bloc *n_prev)
{
    if (prev != NULL) //If there is a prev bloc
        prev->next = NULL; //Unbind this from prev
    prev = n_prev; //Bind new prev to this
    if (prev != NULL) //If new prev is a bloc
        prev->next = this; //Rebind prev bloc to this
}
