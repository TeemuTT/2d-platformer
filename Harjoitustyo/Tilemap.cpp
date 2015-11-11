
#include "Tilemap.h"

Tilemap::Tilemap()
{
    states.texture = &tileset;
}

bool Tilemap::load(const std::string &filename, sf::Vector2u tileSize, int width, int height)
{
    if (!tileset.loadFromFile(filename)) return false;

    using namespace rapidxml;

    xml_document<> doc;
    file<> xmlFile("../Debug/map.tmx");
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

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            tilenumber--;
            int tu = tilenumber % (tileset.getSize().x / tileSize.x);
            int tv = tilenumber / (tileset.getSize().x / tileSize.x);
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
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
            int x = i * tileSize.x;
            int y = j * tileSize.y;
            tiles.emplace_back(x, y);
        }
    }
}

void Tilemap::draw(sf::RenderWindow &window)
{    
    window.draw(vertices, states);
}

void Tilemap::update()
{

}