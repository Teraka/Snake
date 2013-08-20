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
    int frame = 0;
    Snake snake = Snake(&frame, sf::Vector2f(0, 0), d_right, &texture, sf::Color::Green);
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
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
        system("cls");
        if (!pause) snake.step();
        snake.grow(0.2);
        if (snake.getLength() > 100)
            snake.grow(-100);
        sf::Time elapsed = clock.restart();
        std::cout << 1/elapsed.asSeconds() << "fps" << std::endl;
        std::cout << "frame " << frame << std::endl;
        frame++;
        //std::cout << snake.getLength() << std::endl;
        //std::cout << snake.growth << std::endl;
        window.clear();
        window.draw(snake);
        window.display();
    }

    return 0;
}
