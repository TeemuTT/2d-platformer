#ifndef __ANIMATION__
#define __ANIMATION__

#include <string>
#include <vector>

#include "SFML\Graphics.hpp"

class Animation
{
public:
    Animation();
    Animation(sf::Texture texture, int images, int w, int h, bool looping);
    ~Animation();

    sf::Texture* getTexture();
    sf::IntRect getTextureRect(float delta, bool flip);

    void reset();
private:
    float timer;
    bool looping{ false };
    sf::Texture texture;
    std::vector<sf::IntRect> frames;
};

#endif