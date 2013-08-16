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
    Snake snake = Snake(sf::Vector2f(0, 0), d_right, &texture, sf::Color::Green);
    int frame = 0;
    sf::Clock clock;
    int dir = d_right;
    bool pause = false;
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
                    snake.turn(d_up);
                    break;
                case sf::Keyboard::Down:
                    snake.turn(d_down);
                    break;
                case sf::Keyboard::Right:
                    snake.turn(d_right);
                    break;
                case sf::Keyboard::Left:
                    snake.turn(d_left);
                    break;
                case sf::Keyboard::RControl:
                    snake.bury();
                    break;
                case sf::Keyboard::Space:
                    pause = !pause;
                    break;
                }
                break;
            default:
                break;
            }
        }
        /*if (frame % 7 == 0)
        {
            snake.step(dir | 0x4);
            snake2.step(dir | 0x4);
            snake3.step(dir | 0x4);
        }
        else
        {*/
        if (!pause) snake.step();
        //}
        /*if (frame % 4 == 3)
        {
            dir += 1;
            if (dir > 3)
                dir = 0;
        }*/
        //if (frame % 10 == 0 && frame < 100)
        //{
        snake.grow(1);
        if (snake.getLength() > 100)
            snake.grow(-250);
        //}
        frame++;
        if (frame % 100 == 0)
        {
            sf::Time elapsed = clock.restart();
            system("cls");
            std::cout << frame/elapsed.asSeconds() << "fps" << std::endl << snake.getLength() << std::endl;
            frame = 0;
        }
        window.clear();
        window.draw(snake);
        window.display();
    }

    return 0;
}
