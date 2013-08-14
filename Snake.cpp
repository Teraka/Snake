#include "Snake.h"

Snake::Snake(sf::Vector2f n_pos, Direction n_dir, sf::Texture *n_tileset, sf::Color n_color)
{
    tileset = n_tileset;
    head = new Bloc(n_pos, NULL, NULL, n_color, false);
    Bloc *tmp = head;
    buried_timer = 0;
    growth = 0;
    length = 1;
    for (int i = 1; i < D_MIN_SNAKE_LENGTH; i++)
    {
        tmp = new Bloc(n_pos, tmp, NULL, n_color, true);
        length++;
    }
    tail = tmp;
}

void Snake::step(int command)
{
    dir = command & 0x3; //Change that later for something more usable, like handling u-turns and delayed commands.
    if (command & 0x4)
        buried_timer = D_BURIED_TIME;
    Bloc *tmp = tail->prev;
    tail->rebind_prev(NULL);
    tail->rebind_next(head);
    if (growth >= 1)
    {
        Bloc *b = new Bloc(tail->pos, tmp, NULL, tail->color, false);
        tmp = b;
        growth--; //Maybe implement a max_decay_rate, but dunno how yet...
        length++;
    }
    else if (growth <= -1)
    {
        tmp = tmp->prev;
        delete tmp->next;
        growth++;
        length--;
    }
    tail->pos = head->pos + intToDir(dir);
    if (buried_timer > 0)
    {
        tail->buried = true;
        buried_timer--;
    }
    else
        tail->buried = false;
    head = tail;
    tail = tmp;
    head->update();
    head->next->update();
    tail->update();
    tail->prev->update();
    //std::cout << "head pos:" << head->pos.x << "," << head->pos.y << std::endl;
}

void Snake::grow(int g)
{
    growth += g;
}
