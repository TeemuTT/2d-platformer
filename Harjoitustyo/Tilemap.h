#ifndef __TILEMAP__
#define __TILEMAP__


#include <string>
#include <vector>

#include "SFML/Graphics.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include "Entity.h"
#include "Tile.h"

class Tilemap : public Entity
{
public:
    Tilemap();
    bool load(const std::string &filename, sf::Vector2u tileSize, int width, int height);
    virtual void draw(sf::RenderWindow &window);
    virtual void update();
private:
    std::vector<Tile> tiles;
    sf::RenderStates states;
    sf::Texture tileset;
    sf::VertexArray vertices;
};

#endif

