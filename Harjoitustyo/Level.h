#ifndef __LEVEL__
#define __LEVEL__

#include "Tilemap.h"
#include <string>
#include <vector>

class Level
{
public:
    Level();
    Level(std::string filename);
    ~Level();

    void draw(sf::RenderWindow &window);
    void load();
    void clear();
    std::vector<Tile> getTiles();
    sf::FloatRect getBounds();
    sf::FloatRect getStart();
    sf::FloatRect getGoal();
    Tilemap* getMap();

    bool transition();
    bool hasNext();

private:
    std::string filename;
    Tilemap map;
    std::vector<std::string> tilemaps;
    int current{ 0 };
};

#endif