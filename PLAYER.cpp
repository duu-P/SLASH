#include "PLAYER.h"
#include<SDL_image.h>


Player::Player() {
    x = 400;
    y = 288;
    speed = 1;
    moveUp = moveDown = moveLeft = moveRight = false;
    texture = nullptr;  // ban đầu chưa có ảnh
}

void Player::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && !e.key.repeat) {  // chỉ xử lý khi mới nhấn
        switch (e.key.keysym.sym) {
            case SDLK_w:
                moveUp = true;
                break;
            case SDLK_s:
                moveDown = true;
                break;
            case SDLK_a:
                moveLeft = true;
                break;
            case SDLK_d:
                moveRight = true;
                break;
        }
    } else if (e.type == SDL_KEYUP && !e.key.repeat) {  // xử lý khi thả phím
        switch (e.key.keysym.sym) {
            case SDLK_w:
                moveUp = false;
                break;
            case SDLK_s:
                moveDown = false;
                break;
            case SDLK_a:
                moveLeft = false;
                break;
            case SDLK_d:
                moveRight = false;
                break;
        }
    }
}

void Player::update() {
    if (moveUp) y -= speed;
    if (moveDown) y += speed;
    if (moveLeft) x -= speed;
    if (moveRight) x += speed;
}

void Player::render(SDL_Renderer* renderer) {
    SDL_Rect rect = {x, y, 32, 32};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Player::loadTexture(SDL_Renderer* renderer, const char* filePath) {
    SDL_Surface* surface = IMG_Load(filePath);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}


