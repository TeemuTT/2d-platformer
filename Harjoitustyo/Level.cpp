
#include "Level.h"

#include <fstream>
#include <vector>
#include <sstream>

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

/*
Load file which contains filepaths of the levels tilemaps. Push the filepaths to a vector
which is used to load the tilemaps in order.
*/
bool Level::load()
{
    std::ifstream file(filename + ".txt");
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            tilemaps.push_back(line);
        }
    }
    return map.load(tilemaps.at(current));    
}

void Level::clear()
{

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

/*
Load the next tilemap.
*/
bool Level::transition()
{
    if (++current >= tilemaps.size()) {
        return false;
    }
    return map.load(tilemaps.at(current));
}

/*
Check whether this was the last tilemap of the level.
*/
bool Level::hasNext()
{
    if (current + 1 >= tilemaps.size()) return false;
    else return true;
}

/*
Read level data such as enemy positions from [levelname]_data.txt and return vector.
*/
std::vector<std::pair<int, int>> Level::getEnemyPositions()
{
    std::vector < std::pair<int, int> > positions;

    // Create filepath.
    std::string path = tilemaps.at(current);
    path = path.substr(0, path.find(".tmx")).append("_data.txt");

    std::ifstream level_data(path);
    if (level_data.is_open()) {
        int x, y;
        while (level_data >> x) {
            level_data >> y;
            positions.emplace_back(x, y);
        }
    }
    return positions;
}