#include "Bloc.h"

/*
Think a lot about how to update blocs as little as necessary.
*/

void Bloc::update() //Bloc type and rotation are *only* used for the sprite.
{
    //Defining bloc type
    if (buried) type = bt_buried;
    else if (prev == NULL) type = bt_head;
    else if (next == NULL) type = bt_tail;
    else if (abs(pos.x - next->pos.x) +
             abs(pos.y - next->pos.y) != 1) type = bt_disconnected_front;
    else if (abs(pos.x - prev->pos.x) +
             abs(pos.y - prev->pos.y) != 1) type = bt_disconnected_back;
    else if (prev->buried) type = bt_burying;
    else if (next->buried) type = bt_unburying;
    else if ((next->pos.x + prev->pos.x)/2.0 == pos.x) type = bt_straight;
    else type = bt_corner;

    //Defining rotation
    switch(type)
    {
    case bt_head:
    case bt_burying:
    case bt_disconnected_front:
        if (pos.y < next->pos.y) rot = 0;
        else if (pos.x > next->pos.x) rot = 1;
        else if (pos.y > next->pos.y) rot = 2;
        else rot = 3;
        break;
    case bt_tail:
    case bt_unburying:
    case bt_disconnected_back:
        if (pos.y > prev->pos.y) rot = 0;
        else if (pos.x < prev->pos.x) rot = 1;
        else if (pos.y < prev->pos.y) rot = 2;
        else rot = 3;
        break;
    case bt_straight:
        if (pos.x == next->pos.x) rot = 0;
        else rot = 1;
        break;
    case bt_corner:
        float ax = (pos.x + next->pos.x + prev->pos.x)/3.0;
        float ay = (pos.y + next->pos.y + prev->pos.y)/3.0;
        if (ax > pos.x && ay < pos.y) rot = 0;
        else if (ax > pos.x && ay > pos.y) rot = 1;
        else if (ax < pos.x && ay > pos.y) rot = 2;
        else rot = 3;
        break;
    }
}

void Bloc::rebind_next(Bloc *n_next)
{
    if (next != NULL) //If there is a next bloc
        next->prev = NULL; //Unbind this from next
    next = n_next;
    if (next != NULL) //If new next is a bloc
        next->prev = this; //Rebind next bloc to this
}

void Bloc::rebind_prev(Bloc *n_prev)
{
    if (prev != NULL)
        prev->next = NULL;
    prev = n_prev;
    if (prev != NULL)
        prev->next = this;
}

void Bloc::set_pos(sf::Vector2i n_pos)
{
    pos = n_pos;
}

sf::Vector2i Bloc::get_pos()
{
    return pos;
}

void Bloc::set_buried(bool b)
{
    buried = b;
}

void Bloc::blit_quad(sf::VertexArray &quad, int index)
{
    sf::Vector2f corners[4] = {sf::Vector2f(pos.x*D_BLOCSIZE, pos.y*D_BLOCSIZE),
                               sf::Vector2f((pos.x+1)*D_BLOCSIZE, pos.y*D_BLOCSIZE),
                               sf::Vector2f((pos.x+1)*D_BLOCSIZE, (pos.y+1)*D_BLOCSIZE),
                               sf::Vector2f(pos.x*D_BLOCSIZE, (pos.y+1)*D_BLOCSIZE)};
    for (int v=0; v<4; v++)
    {
        quad[index+v].position = corners[v];
        quad[index+v].texCoords = corners[((v+4)-rot)%4];
    }
}
