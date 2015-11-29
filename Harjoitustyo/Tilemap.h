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
    void draw(sf::RenderWindow &window);
    void update();
    std::vector<Tile> getTiles();
    sf::FloatRect getBounds();
private:
    std::vector<Tile> tiles;
    sf::RenderStates states;
    sf::Texture tileset;
    sf::VertexArray vertices;
};

#endif

