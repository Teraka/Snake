#include "Snake.h"

void Snake::step(int command)
{
    Bloc *tmp = tail->next;
    tail->rebind_prev(NULL);
    tail->rebind_next(head);
    switch(dir)
    {
    case d_right:
        tail->set_pos(head->get_pos() + sf::Vector2i(1, 0));
        break;
    case d_left:
        tail->set_pos(head->get_pos() + sf::Vector2i(-1, 0));
        break;
    case d_down:
        tail->set_pos(head->get_pos() + sf::Vector2i(0, 1));
        break;
    case d_up:
        tail->set_pos(head->get_pos() + sf::Vector2i(0, -1));
        break;
    }
    if (buried_timer > 0)
    {
        tail->set_buried(true);
        buried_timer--;
    }
    if (growth >= 1)
    {

    }
}
