
#include "GameState.h"

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
    return map.getTiles();
}