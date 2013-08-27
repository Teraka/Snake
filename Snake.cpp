#include "Snake.h"

int Snake::snake_count = 0;

Snake::Snake(int *n_frame, TileGrid *n_collisionGrid, sf::Vector2f n_pos, Direction n_dir, sf::Texture *n_tileset, sf::Color n_color)
{
    id = ++snake_count;
    frame = n_frame;
    commandList = intArray();
    commandList.set(0, n_dir);
    lastCommand = 0;
    tileset = n_tileset;
    buried_timer = 0;
    growth = 0;
    length = 1;
    alive = true;
    changed_dir = false;
    head = new Bloc(n_pos, NULL, NULL, n_color, false);
    collisionGrid = n_collisionGrid;
    Bloc *tmp = head;
    for (int i = 1; i < D_MIN_SNAKE_LENGTH; i++)
    {
        n_pos -= intToDir(n_dir);
        tmp = new Bloc(n_pos, tmp, NULL, n_color, true);
        length++;
    }
    updateCollisionGrid();
    tail = tmp;
}

void Snake::turn(int n_dir, bool bypass)
{
    if (n_dir % 2 == commandList.get(lastCommand) % 2 && !bypass) return;
    commandList.set(++lastCommand, n_dir);
}

void Snake::bury()
{
    if (buried_timer > -2 - D_BURY_COOLDOWN) return;
    buried_timer = D_BURIED_TIME;
    for (int i = 0; i < D_BURIED_TIME + 2; i++)
    {
        commandList.set(*frame + i, commandList.get(*frame-1));
    }
    lastCommand = *frame + D_BURIED_TIME + 1;
}

void Snake::updateCollisionGrid()
{
    if (!alive) return;
    Bloc *current = head;
    while (current)
    {
        if (!current->buried) collisionGrid->set_at(current->getToricPos(), id);
        current = current->next;
    }
}

void Snake::step()
{
    if (!alive)
    {
        growth += DEATH_GROWTH_RATE;
        if (length <= D_MIN_SNAKE_LENGTH)
        { //Resurrection
            alive = true;
            Bloc *current = head;
            while (current)
            {
                current->setAlpha(255);
                current = current->next;
            }
        }
    }
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
    while (lastCommand < *frame)
    {
        commandList.set(lastCommand+1, commandList.get(lastCommand));
        lastCommand++;
    }
    tail->pos = head->pos + intToDir(commandList.get(*frame)); //Move the new head.
    tail->buried = buried_timer > 0;
    buried_timer--;
    head = tail; //Rebind pointers.
    tail = tmp;
    head->update();
    head->next->update();
    tail->update();
    tail->prev->update();
    if (collisionGrid->getCollision(head->getToricPos()))
    { //Death
        alive = false;
        Bloc *current = head;
        while (current)
        {
            current->setAlpha(128);
            current = current->next;
        }
    }
    updateCollisionGrid();
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

void Snake::grow(float g)
{
    if (!alive) return;
    growth += g;
}
