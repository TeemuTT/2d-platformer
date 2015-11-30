
#include "Level.h"

#include <fstream>

Level::Level()
{

}

Level::Level(std::string filename)
{
    this->filename = filename;
}

Level::~Level()
{

}

void Level::load()
{
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            tilemaps.push_back(line);
        }
    }
    map.load(tilemaps.at(current));
}

std::vector<Tile> Level::getTiles()
{
    return map.getTiles();
}

sf::FloatRect Level::getBounds()
{
    return map.getBounds();
}

sf::FloatRect Level::getStart()
{
    return map.getStart();
}

sf::FloatRect Level::getGoal()
{
    return map.getGoal();
}

void Level::draw(sf::RenderWindow &window)
{
    map.draw(window);
}

Tilemap* Level::getMap()
{
    return &map;
}

bool Level::transition()
{
    if (++current >= tilemaps.size()) {
        return false;
    }
    return map.load(tilemaps.at(current));
}