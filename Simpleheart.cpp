#include "SimpleHeart.h"
#include <iostream>
#include<SDL_image.h>
SimpleHeart::SimpleHeart(SDL_Renderer* renderer)
    : renderer(renderer), heartTexture(nullptr) {}

SimpleHeart::~SimpleHeart() {
    if (heartTexture) SDL_DestroyTexture(heartTexture);
}

bool SimpleHeart::loadTexture(const char* filePath) {
    heartTexture = IMG_LoadTexture(renderer, filePath);
    if (!heartTexture) {
        std::cerr << "Failed to load heart texture: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void SimpleHeart::render() {
    for (int i = 0; i < currentLives; ++i) {
        SDL_Rect dstRect = { 10 + i * (heartSize + 5), 10, heartSize, heartSize };
        SDL_RenderCopy(renderer, heartTexture, nullptr, &dstRect);
    }
}

void SimpleHeart::loseLife() {
    if (currentLives > 0) currentLives--;
}

void SimpleHeart::reset() {
    currentLives = maxLives;
}

int SimpleHeart::getLives() const {
    return currentLives;
}

