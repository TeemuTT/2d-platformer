
#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(std::string filename, int images, int w, int h)
{
    texture.loadFromFile(filename); 

    for (int i = 0; i < images; ++i) {
        frames.push_back(sf::IntRect(i * w, 0, w, h));
    }
}

sf::Texture* Animation::getTexture()
{
    return &texture;
}

sf::IntRect Animation::getTextureRect(int index)
{
    return frames[index];
}