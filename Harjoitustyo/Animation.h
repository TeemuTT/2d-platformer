#ifndef __ANIMATION__
#define __ANIMATION__

#include <string>
#include <vector>

#include "SFML\Graphics.hpp"

class Animation
{
public:
    Animation();
    Animation(std::string filename, int images, int w, int h);

    sf::Texture* getTexture();
    sf::IntRect getTextureRect(int index);

private:
    sf::Texture texture;
    std::vector<sf::IntRect> frames;
};

#endif