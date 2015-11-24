
#include "Game.h"
#include "GameScreen.h"
#include "MainMenu.h"

int main()
{
    Game game;
    game.push_state(new MainMenu(&game));
    game.run();

    return 0;
}
//
//
//#include "SFML/Graphics.hpp"
//
//int main()
//{
//    const int SPEED = 5;
//
//    sf::RenderWindow window(sf::VideoMode(640, 480), "PELI");
//    window.setFramerateLimit(60);
//
//    sf::RectangleShape pelaaja;
//    pelaaja.setFillColor(sf::Color::Red);
//    pelaaja.setSize(sf::Vector2f(50, 50));
//    pelaaja.setPosition(320, 240);
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
//            pelaaja.setPosition(pelaaja.getPosition().x, pelaaja.getPosition().y - SPEED);
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
//            pelaaja.setPosition(pelaaja.getPosition().x, pelaaja.getPosition().y + SPEED);
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
//            pelaaja.setPosition(pelaaja.getPosition().x - SPEED, pelaaja.getPosition().y);
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
//            pelaaja.setPosition(pelaaja.getPosition().x + SPEED, pelaaja.getPosition().y);
//        }
//
//
//
//        window.clear();
//        window.draw(pelaaja);
//        window.display();
//
//    }
//
//    return 0;
//}