#include "Bloc.h"

void Bloc::print_bloc()
{
    std::cout << "[t:" << this << "],[" << pos.x << "," << pos.y << "]," << buried << "," << rot << std::endl;
    std::cout << "[p:" << prev << "],[n:" << next << "]" << std::endl << std::endl;
}

Bloc::Bloc(sf::Vector2f n_pos, int n_dir, Bloc* n_prev, Bloc* n_next, sf::Color n_color, bool n_buried) : Tile(n_pos, sf::Vector2f(0, 0), 0, n_color)
{
    buried = n_buried;
    dir = n_dir;
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

void Bloc::update() //Bloc type and rotation are *only* used for the sprite.
{
    if (buried)
    {
        texPos = sf::Vector2f(0, 0);
        return;
    }
    int buryId = (prev && prev->buried) | ((next && next->buried) << 1);
    texPos.y = (next == NULL ? 3 : (prev == NULL ? 2 : int(dir != next->dir))); //Define bloc type : 0:straight, 1:corner, 2:head, 3:tail.
    switch(int(texPos.y))
    {
    case 0:
        texPos.x = buryId == 0 ? 1 : 2;
        if (buryId == 2) rot = (dir + 2) % 4;
        else rot = dir;
        break;
    case 1:
        if (!next->buried && !prev->buried)
            texPos.x = 0;
        else
            texPos.x = 1 + int((dir + 1) % 4 == next->dir ^ next->buried);
        rot = ((dir + 1) % 4 == next->dir) ? (next->dir + 2) % 4 : dir;
        break;
    case 2:
    case 3:
        texPos.x = buryId;
        rot = dir;
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
