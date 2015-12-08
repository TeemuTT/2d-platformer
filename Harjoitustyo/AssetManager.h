#ifndef __ASSETMANAGER__
#define __ASSETMANAGER__

#include <map>
#include <string>

#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

class AssetManager
{
public:
    AssetManager();
    ~AssetManager();

    sf::Texture& getTexture(std::string name);
    sf::SoundBuffer& getSound(std::string name);
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::SoundBuffer> sounds;
};

#endif