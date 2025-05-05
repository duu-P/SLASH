/*#include "SimpleHeart.h"
#include <iostream>
#include <SDL_image.h>

SimpleHeart::SimpleHeart() :
    heartTexture(nullptr),
    lives(3),
    heartWidth(32),
    heartHeight(32) {}

SimpleHealth::~SimpleHealth() {
    if (heartTexture) {
        SDL_DestroyTexture(heartTexture);
        heartTexture = nullptr;
    }
}

bool SimpleHealth::init(SDL_Renderer* renderer, const char* heartImagePath) {
    // Load texture trái tim
    heartTexture = IMG_LoadTexture(renderer, heartImagePath);
    if (!heartTexture) {
        std::cerr << "Không thể load texture trái tim: " << IMG_GetError() << std::endl;
        return false;
    }

    // Lấy kích thước thực của texture
    SDL_QueryTexture(heartTexture, NULL, NULL, &heartWidth, &heartHeight);
    reset();
    return true;
}

void SimpleHealth::loseLife() {
    if (lives > 0) lives--;
}

void SimpleHealth::render(SDL_Renderer* renderer) {
    if (!heartTexture) return;

    // Vẽ từng trái tim còn lại
    for (int i = 0; i < lives; i++) {
        SDL_Rect destRect = {
            10 + i * (heartWidth + 5),  // Cách nhau 5 pixel
            10,
            heartWidth,
            heartHeight
        };
        SDL_RenderCopy(renderer, heartTexture, NULL, &destRect);
    }
}

bool SimpleHealth::isAlive() const {
    return lives > 0;
}

void SimpleHealth::reset() {
    lives = 3;
} */
