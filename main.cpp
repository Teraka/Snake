#include <iostream>
#include <SFML/Graphics.hpp>

//TODO: Make the Bloc constructor, and finish Snake::step.

using namespace std;

void setPosition(sf::VertexArray &quad, int index, int x, int y)
{
    quad[index + 0].position = sf::Vector2f(x*21+10, y*21+10);
    cout << "pos:[" << quad[index].position.x << "," << quad[index].position.y << "]" << endl;
    quad[index + 1].position = sf::Vector2f(x*21+31, y*21+10);
    quad[index + 2].position = sf::Vector2f(x*21+31, y*21+31);
    quad[index + 3].position = sf::Vector2f(x*21+10, y*21+31);
}

void setTexCoords(sf::VertexArray &quad, int index, int x, int y)
{
    quad[index + 0].texCoords = sf::Vector2f(x*21, y*21);
    quad[index + 1].texCoords = sf::Vector2f((x+1)*21, y*21);
    quad[index + 2].texCoords = sf::Vector2f((x+1)*21, (y+1)*21);
    quad[index + 3].texCoords = sf::Vector2f(x*21, (y+1)*21);
}

void setColor(sf::VertexArray &quad, int index, sf::Color color)
{
    quad[index].color = color;
    quad[index + 1].color = color;
    quad[index + 2].color = color;
    quad[index + 3].color = color;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    window.setFramerateLimit(30);
    sf::Texture texture;
    if (!texture.loadFromFile("snake.png"))
    {
        return -1;
    }
    sf::VertexArray sprite(sf::Quads, 16);
    setPosition(sprite, 0, 0, 0);
    setPosition(sprite, 4, 0, 1);
    setPosition(sprite, 8, 1, 1);
    setPosition(sprite, 12, 2, 1);
    setTexCoords(sprite, 0, 0, 0);
    setTexCoords(sprite, 4, 0, 2);
    setTexCoords(sprite, 8, 1, 2);
    setTexCoords(sprite, 12, 2, 2);
    setColor(sprite, 0, sf::Color::Red);
    setColor(sprite, 4, sf::Color::Blue);
    setColor(sprite, 8, sf::Color::Yellow);
    setColor(sprite, 12, sf::Color::Green);
    sf::Color color = sf::Color(0, 0, 0);
    cout << -5%2;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            color.r += 5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            color.g += 5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            color.b += 5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            color.r -= 5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            color.g -= 5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            color.b -= 5;
        window.clear();
        window.draw(sprite, &texture);
        window.display();
    }

    return 0;
}
