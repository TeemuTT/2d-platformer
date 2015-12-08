#ifndef __GAMESCREEN__
#define __GAMESCREEN__

#include <string>
#include <random>

#include "SFML/Audio.hpp"

#include "Level.h"
#include "Entity.h"
#include "Player.h"
#include "GameState.h"

class GameScreen : public GameState
{
public:
    GameScreen(Game* game, std::string filename);
    ~GameScreen();

    virtual GameState* update();
    virtual void draw(sf::RenderWindow &window);
    virtual void transition();

    void quitfrompausemenu();
    void change_score(int change);

private:
    sf::Font font;
    sf::Music music;
    sf::Clock clock;
    sf::Text scoretext;
    sf::RectangleShape fillRect;
    std::default_random_engine gen;

    int alpha{ 255 }, score;
    float delta, timer;
    bool alive{ false };
    bool fade(bool fadein);
    
    void center_view(Player *p);

    enum Status {
        START, NORMAL, END, QUIT
    };

    Status status{ START };
};

#endif