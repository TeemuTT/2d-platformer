
#include <iostream>

#include "Tilemap.h"
#include "Constants.h"

Tilemap::Tilemap()
{
    
}

bool Tilemap::load(std::string filename)
{
    //std::string tilepath = "../Debug/";
    std::string tilepath = "maps/";
    std::string filepath = "maps/" + filename;
    int width, height;

    using namespace rapidxml;
    xml_document<> doc;
    file<> xmlFile(filepath.c_str());
    doc.parse<0>(xmlFile.data());
    xml_node<> *root = doc.first_node("map");
    xml_attribute<> *pAttr = root->first_attribute("width");
    width = atoi(pAttr->value());
    pAttr = root->first_attribute("height");
    height = atoi(pAttr->value());

    pAttr = root->first_attribute("startx");
    start.left = atoi(pAttr->value());
    pAttr = root->first_attribute("starty");
    start.top = atoi(pAttr->value());
    pAttr = root->first_attribute("endx");
    goal.left = atoi(pAttr->value());
    pAttr = root->first_attribute("endy");
    goal.top = atoi(pAttr->value());

    start.width = 64;
    start.height = 64;
    goal.width = 64;
    goal.height = 64;

    xml_node<> *source = root->first_node()->first_node();
    pAttr = source->first_attribute("source");
    tilepath.append(pAttr->value());

    return load(filepath, tilepath, width, height);
}

bool Tilemap::load(std::string filepath, std::string tilepath, int width, int height)
{
    if (!tileset.loadFromFile(tilepath)) return false;
    states.texture = &tileset;
    tiles.clear();

    using namespace rapidxml;

    xml_document<> doc;
    file<> xmlFile(filepath.c_str());
    doc.parse<0>(xmlFile.data());
    xml_node<> *root = doc.first_node("map");
    xml_node<> *tile = root->first_node("layer");
    xml_node<> *layer = tile->next_sibling();
    tile = tile->first_node("data");
    tile = tile->first_node("tile");

    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(width * height * 4);

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            xml_attribute<> *pAttr = tile->first_attribute();
            int tilenumber = atoi(pAttr->value());
            tile = tile->next_sibling();
            if (tilenumber == 0) continue;

            sf::Vertex *quad = &vertices[(j + i * height) * 4];

            quad[0].position = sf::Vector2f(i * TILESIZE, j * TILESIZE);
            quad[1].position = sf::Vector2f((i + 1) * TILESIZE, j * TILESIZE);
            quad[2].position = sf::Vector2f((i + 1) * TILESIZE, (j + 1) * TILESIZE);
            quad[3].position = sf::Vector2f(i * TILESIZE, (j + 1) * TILESIZE);

            tilenumber--;
            int tu = tilenumber % (tileset.getSize().x / TILESIZE);
            int tv = tilenumber / (tileset.getSize().x / TILESIZE);
            quad[0].texCoords = sf::Vector2f(tu * TILESIZE, tv * TILESIZE);
            quad[1].texCoords = sf::Vector2f((tu + 1) * TILESIZE, tv * TILESIZE);
            quad[2].texCoords = sf::Vector2f((tu + 1) * TILESIZE, (tv + 1) * TILESIZE);
            quad[3].texCoords = sf::Vector2f(tu * TILESIZE, (tv + 1) * TILESIZE);
        }
    }

    tile = layer->first_node("data");
    tile = tile->first_node("tile");

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            xml_attribute<> *pAttr = tile->first_attribute();
            int tilenumber = atoi(pAttr->value());
            tile = tile->next_sibling();
            if (tilenumber == 0) continue;
            tilenumber--;
            int x = i * TILESIZE;
            int y = j * TILESIZE;
            tiles.emplace_back(x, y);
        }
    }
    return true;
}

void Tilemap::draw(sf::RenderWindow &window)
{
    window.draw(vertices, states);
    //for (Tile t : tiles) {
    //    window.draw(t.getShape());
    //}

}

void Tilemap::update()
{
    return;
}

void Tilemap::clear()
{
    tiles.clear();
    vertices.clear();
}

std::vector<Tile> Tilemap::getTiles()
{
    return tiles;
}

sf::FloatRect Tilemap::getBounds()
{
    return vertices.getBounds();
}

sf::FloatRect Tilemap::getStart()
{
    return start;
}

sf::FloatRect Tilemap::getGoal()
{
    return goal;
}