
#include "GameState.h"

GameState::~GameState()
{

}

bool GameState::isDestroyed()
{
    return destroyed;
}

void GameState::add_entity(Entity* entity)
{
    queue.push_back(entity);
}

std::vector<Entity*> GameState::getEntities()
{
    return entities;
}

std::vector<Tile> GameState::getTiles()
{
    return level.getTiles();
}

sf::View GameState::getView()
{
    return view;
}

void GameState::transition()
{

}