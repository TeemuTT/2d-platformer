#ifndef __GAMESCREEN__
#define __GAMESCREEN__

#include "GameState.h"
#include "Entity.h"
#include "Level.h"
#include "Player.h"

#include "SFML/Audio.hpp"
#include <string>

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
    sf::Music music;
    sf::Clock clock;
    sf::RectangleShape fillRect;
    sf::Font font;
    sf::Text scoretext;
    int alpha{ 255 };
    float delta;
    float timer;
    int fps;
    int score;
    bool cleared{ false };
    bool starting{ true };
    bool alive{ true };
    bool abort{ false };
    bool fade(bool fadein);
    void center_view(Player *p);
};

#endif