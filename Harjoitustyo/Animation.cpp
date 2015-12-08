
#include "Animation.h"

Animation::Animation()
{

}

Animation::~Animation()
{

}

Animation::Animation(sf::Texture texture, int images, int w, int h, bool looping)
{
    this->texture = texture;

    for (int i = 0; i < images; ++i) {
        frames.push_back(sf::IntRect(i * w, 0, w, h));
    }

    this->looping = looping;
}

sf::Texture* Animation::getTexture()
{
    return &texture;
}

sf::IntRect Animation::getTextureRect(float delta, bool flip)
{
    timer += delta;
    if (timer >= frames.size()) {
        if (looping) timer = 0;
        else timer = frames.size() - 1;
    }
    if (flip) {
        sf::IntRect rect = frames[(int)timer];
        rect.left = rect.width * ((int)timer + 1);
        rect.width = -rect.width;
        return rect;
    }
    return frames[(int)timer];
}

void Animation::reset()
{
    timer = 0;
}