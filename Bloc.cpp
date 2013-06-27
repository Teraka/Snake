#include "Bloc.h"

/*
Think a lot about how to update blocs as little as necessary.
*/

void Bloc::print_bloc()
{
    std::cout << "[t:" << this << "],[" << pos.x << "," << pos.y << "]," << buried << std::endl;
    std::cout << "[p:" << prev << "],[n:" << next << "]" << std::endl << std::endl;
}

Bloc::Bloc(sf::Vector2f n_pos, Bloc* n_prev, Bloc* n_next, sf::Color n_color, bool n_buried)
{
    pos = n_pos;
    color = n_color;
    buried = n_buried;
    next = NULL;
    prev = NULL;
    rebind_next(n_next);
    rebind_prev(n_prev);
}

Bloc::~Bloc()
{
    rebind_next(NULL);
    rebind_prev(NULL);
}

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
        else if (pos.x > next->pos.x) rot = 3;
        else if (pos.y > next->pos.y) rot = 2;
        else rot = 1;
        break;
    case bt_tail:
    case bt_unburying:
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

void Bloc::blit_quad(sf::VertexArray &quad, int index)
{
    sf::Transform t;
    t.scale(D_BLOCSIZE, D_BLOCSIZE);
    sf::Vector2f corner[4];
    for (int n = 0; n < 4; n++)
    {
        corner[n] = t * int_to_corner(n);
    }
    sf::Vector2f origin = t * pos;
    sf::Vector2f tex_origin = sf::Vector2f(type & 0x3, type >> 2);
    tex_origin = t * tex_origin;
    for (int v = 0; v < 4; v++)
    {
        quad[index+v].position = origin + corner[v];
        quad[index+v].texCoords = tex_origin + corner[(v + rot) % 4];
        quad[index+v].color = color;
    }
}
