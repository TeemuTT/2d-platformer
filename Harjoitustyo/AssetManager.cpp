
#include "AssetManager.h"


AssetManager::AssetManager()
{
    sf::Texture texture;
    texture.loadFromFile("textures/run.png");
    textures["player_run"] = texture;
    texture.loadFromFile("textures/jump.png");
    textures["player_jump"] = texture;
    texture.loadFromFile("textures/slide.png");
    textures["player_sprint"] = texture;
    texture.loadFromFile("textures/dead.png");
    textures["player_dead"] = texture;
    texture.loadFromFile("textures/idle.png");
    textures["player_idle"] = texture;
    texture.loadFromFile("textures/explosion.png");
    textures["explosion"] = texture;
    texture.loadFromFile("textures/zappy.png");
    textures["zappy"] = texture;
    texture.loadFromFile("textures/bullet.png");
    textures["bullet"] = texture;

    sf::SoundBuffer buffer;
    buffer.loadFromFile("sounds/shoot.wav");
    sounds["player_shoot"] = buffer;
    buffer.loadFromFile("sounds/hit.wav");
    sounds["enemy_hit"] = buffer;
    buffer.loadFromFile("sounds/slide.wav");
    sounds["player_sprint"] = buffer;
    buffer.loadFromFile("sounds/playerhit.wav");
    sounds["player_hit"] = buffer;
    buffer.loadFromFile("sounds/explosion.wav");
    sounds["explosion"] = buffer;
}

AssetManager::~AssetManager()
{

}

sf::Texture& AssetManager::getTexture(std::string name)
{
    return textures[name];
}

sf::SoundBuffer& AssetManager::getSound(std::string name)
{
    return sounds[name];
}