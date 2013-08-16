#include "Snake.h"

Snake::Snake(sf::Vector2f n_pos, Direction n_dir, sf::Texture *n_tileset, sf::Color n_color)
{
    tileset = n_tileset;
    buried_timer = 0;
    growth = 0;
    length = 1;
    prev_dir = -1;
    dir = n_dir;
    next_dir = -1;
    changed_dir = false;
    head = new Bloc(n_pos, NULL, NULL, n_color, false);
    Bloc *tmp = head;
    for (int i = 1; i < D_MIN_SNAKE_LENGTH; i++)
    {
        n_pos -= intToDir(dir);
        tmp = new Bloc(n_pos, tmp, NULL, n_color, true);
        length++;
    }
    tail = tmp;
}

void Snake::turn(int n_dir)
{
    if (buried_timer > -2) return;
    if (n_dir % 2 == dir % 2) return; //Will be true if inverse or equal directions.
    if (!changed_dir)
    {
        prev_dir = dir;
        dir = n_dir;
        changed_dir = true;
    }
    else if (next_dir == -1)
    {
        next_dir = n_dir;
    }
}

void Snake::bury()
{
    if (buried_timer > -5) return;
    buried_timer = D_BURIED_TIME;
    if (changed_dir)
        dir = prev_dir;
}

void Snake::step()
{
    Bloc *tmp = tail->prev; //Keep a pointer to the future tail.
    tail->rebind_prev(NULL); //Make tail the new head.
    tail->rebind_next(head);
    if (growth >= 1)
    {
        Bloc *b = new Bloc(tail->pos, tmp, NULL, tail->color, tail->buried);
        tmp = b;
        growth--; //Maybe implement a max_decay_rate, but dunno how yet...
        length++;
    }
    else if (growth <= -1 && length > D_MIN_SNAKE_LENGTH)
    {
        tmp = tmp->prev;
        delete tmp->next;
        growth++;
        length--;
    }
    tail->pos = head->pos + intToDir(dir); //Move the new head.
    if (buried_timer > 0)
    {
        tail->buried = true;
    }
    else
        tail->buried = false;
    buried_timer--;
    head = tail; //Rebind pointers.
    tail = tmp;
    head->update();
    head->next->update();
    tail->update();
    tail->prev->update();
    if (next_dir != -1)
    {
        dir = next_dir;
        next_dir = -1;
        changed_dir = true;
    }
    else
        changed_dir = false;
    //printSnake();
}

void Snake::printSnake()
{
    system("cls");
    Bloc *tmp = head;
    while (tmp != NULL)
    {
        tmp->print_bloc();
        tmp = tmp->next;
    }
}

void Snake::grow(int g)
{
    growth += g;
}
