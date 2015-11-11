
#include "GameScreen.h"


GameScreen::GameScreen()
{

}

GameScreen::~GameScreen()
{
    std::cout << "GameScreen destroyed\n";
}

void GameScreen::update()
{

}

void GameScreen::draw(sf::RenderWindow &window)
{
    sf::CircleShape circle;
    circle.setPosition(240, 180);
    circle.setFillColor(sf::Color::Green);
    circle.setRadius(20);
    window.draw(circle);
}