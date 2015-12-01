#ifndef __TILEMAP__
#define __TILEMAP__


#include <string>
#include <vector>

#include "SFML/Graphics.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include "Tile.h"

class Tilemap
{
public:
    Tilemap();
    bool load(std::string filename, std::string tileset, int width, int height);
    bool load(std::string filename);
    void draw(sf::RenderWindow &window);
    void update();
    void clear();
    std::vector<Tile> getTiles();
    sf::FloatRect getBounds();
    sf::FloatRect getStart();
    sf::FloatRect getGoal();
private:
    std::vector<Tile> tiles;
    sf::RenderStates states;
    sf::Texture tileset;
    sf::VertexArray vertices;
    sf::FloatRect start, goal;
};

#endif

