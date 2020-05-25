#include <SFML/Graphics.hpp>
#include <iostream>

#define size 10
#define DISP_WIDTH 320
#define DISP_FULL_HEIGHT 400

using namespace std;

void drawTick(sf::RenderWindow &window, int x, int y) {
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x * (DISP_WIDTH / size), y * (DISP_WIDTH / size))),
        sf::Vertex(sf::Vector2f((x+1) * (DISP_WIDTH / size), (y + 1) * (DISP_WIDTH / size)))
    };
    window.draw(line, 2, sf::Lines);
    line[0] = sf::Vertex(sf::Vector2f((x + 1) * (DISP_WIDTH / size), y * (DISP_WIDTH / size)));
    line[1] = sf::Vertex(sf::Vector2f(x * (DISP_WIDTH / size), (y + 1) * (DISP_WIDTH / size)));
    window.draw(line, 2, sf::Lines);
}

void drawRound(sf::RenderWindow &window, int x, int y) {
    sf::CircleShape shape((DISP_WIDTH / size) / 2 - 4);
    shape.move(sf::Vector2f(x * (DISP_WIDTH / size) + 4, y * (DISP_WIDTH / size) + 4));

    shape.setOutlineThickness(2.f);
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::White);
    window.draw(shape);
}

void drawWinnerText(sf::RenderWindow &window, string winner) {
    sf::Text text;
    sf::Font font;
    font.loadFromFile("roboto.ttf");
    text.setFont(font);
    text.setString(winner);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.move(10, 340);

    window.draw(text);
}
void drawWinnerText(sf::RenderWindow &window, int state) {
    sf::Text text;
    sf::Font font;
    font.loadFromFile("roboto.ttf");
    text.setFont(font);
    if (state == 1) {
        text.setString("Please wait...");
    } else {
        text.setString("You turn...");
    }
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.move(10, 340);

    window.draw(text);
}

void clearText(sf::RenderWindow &window) {
    sf::RectangleShape rectangle(sf::Vector2f(320.f, 80.f));
    rectangle.move(0, 320);
    rectangle.setFillColor(sf::Color::Black);
    window.draw(rectangle);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(DISP_WIDTH, DISP_FULL_HEIGHT), "Tick Tack Toe");

    window.clear(sf::Color::Black);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            int x, y;
            x = pos.x / (DISP_WIDTH / size);
            y = pos.y / (DISP_WIDTH / size);
            if ((x >= 0) && (y >= 0) && (x < size) && (y < size)) {
                drawTick(window, x, y);
                clearText(window);
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            int x, y;
            x = pos.x / (DISP_WIDTH / size);
            y = pos.y / (DISP_WIDTH / size);
            if ((x >= 0) && (y >= 0) && (x < size) && (y < size)) {
                drawRound(window, x, y);
            }
            string winnner = "jdkFDJKJLFDJHLD";
            drawWinnerText(window, winnner);
        }

        for (int i = 1; i <= 10; i++) {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(i * (DISP_WIDTH / size), 0)),
                sf::Vertex(sf::Vector2f(i * (DISP_WIDTH / size), 320))
            };

            window.draw(line, 2, sf::Lines);
            line[0] = sf::Vertex(sf::Vector2f(0, i * (DISP_WIDTH / size)));
            line[1] = sf::Vertex(sf::Vector2f(320, i * (DISP_WIDTH / size)));
            window.draw(line, 2, sf::Lines);
            
        }
        window.display();
    }

    return 0;
}