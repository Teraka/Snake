#include <iostream>
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "TileGrid.h"
#include "Defines.h"

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
    TileGrid grid = TileGrid(sf::Vector2f(D_GRIDSIZE, D_GRIDSIZE));
    Snake snake = Snake(&frame, &grid, sf::Vector2f(0, 0), d_right, &texture, sf::Color::Green);
    //Snake snake2 = Snake(&frame, &grid, sf::Vector2f(0, 10), d_right, &texture, sf::Color::Red);
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
                /*case sf::Keyboard::W:
                    snake2.turn(d_up);
                    break;
                case sf::Keyboard::S:
                    snake2.turn(d_down);
                    break;
                case sf::Keyboard::D:
                    snake2.turn(d_right);
                    break;
                case sf::Keyboard::A:
                    snake2.turn(d_left);
                    break;
                case sf::Keyboard::F:
                    snake2.bury();
                    break;*/
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
        if (!pause)
        {
            //snake.grow(1);
            //snake2.grow(1);
            snake.step();
            //snake2.step();
            grid.flip();
            snake.checkCollision();
            //snake2.checkCollision();
        }
        if (snake.getLength() > 75)
            snake.grow(-100);
        //if (snake2.getLength() > 75)
        //    snake2.grow(-100);
        sf::Time elapsed = clock.restart();
        std::cout << 1/elapsed.asSeconds() << "fps" << std::endl;
        std::cout << "frame " << frame << std::endl;
        std::cout << snake.getLength() << std::endl;
        std::cout << snake.growth << std::endl;
        snake.printSnake();
        frame++;
        window.clear();
        window.draw(grid);
        window.draw(snake);
        //window.draw(snake2);
        window.display();
    }

    return 0;
}
