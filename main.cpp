#include <iostream>
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Defines.h"

//TODO: Make a collision grid class and have all snakes have a pointer to the same.

int main()
{
    sf::RenderWindow window(sf::VideoMode(D_GRIDSIZE * D_TILESIZE, D_GRIDSIZE * D_TILESIZE), "SFML works!");
    window.setFramerateLimit(10);
    sf::Texture texture;
    if (!texture.loadFromFile("snake25.png"))
    {
        return -1;
    }
    Snake snake = Snake(sf::Vector2f(0, 0), d_right, &texture, sf::Color::Red);
    Snake snake2 = Snake(sf::Vector2f(1, 1), d_right, &texture, sf::Color::Green);
    Snake snake3 = Snake(sf::Vector2f(2, 2), d_right, &texture, sf::Color::Blue);
    int frame = 0;
    int dir = d_right;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                case sf::Keyboard::Up:
                    dir = d_up;
                    break;
                case sf::Keyboard::Down:
                    dir = d_down;
                    break;
                case sf::Keyboard::Right:
                    dir = d_right;
                    break;
                case sf::Keyboard::Left:
                    dir = d_left;
                    break;
                }
                break;
            default:
                break;
            }
        }
        if (frame % 7 == 0)
        {
            snake.step(dir | 0x4);
            snake2.step(dir | 0x4);
            snake3.step(dir | 0x4);
        }
        else
        {
            snake.step(dir);
            snake2.step(dir);
            snake3.step(dir);
        }
        /*if (frame % 4 == 3)
        {
            dir += 1;
            if (dir > 3)
                dir = 0;
        }*/
        if (frame % 10 == 0 && frame < 100)
        {
            snake.grow(1);
            snake2.grow(1);
            snake3.grow(1);
        }
        frame++;
        window.clear();
        window.draw(snake);
        window.draw(snake2);
        window.draw(snake3);
        window.display();
    }

    return 0;
}
