#include "Enemy.h"
#include <cmath>
#include <iostream>
#include <SDL_image.h>
#include <string>

Enemy::Enemy(int startX, int startY, int startHealth, SDL_Renderer* renderer) {
    ai.x = startX;
    ai.y = startY;
    ai.health = startHealth;
    this->renderer = renderer;



}

float Enemy::distanceManhattan(float x1, float y1, float x2, float y2) {
    return fabs(x1 - x2) + fabs(y1 - y2);
}

void Enemy::moveTowardsPlayer(const Entity& player) {
    const int speed = 1;

    float dx = player.x - ai.x;
    float dy = player.y - ai.y;

    float distance = sqrt(dx * dx + dy * dy);

    // Kiểm tra để tránh chia cho 0
    if (distance > speed) {
        ai.x += speed * (dx / distance);
        ai.y += speed * (dy / distance);
    }
}

void Enemy::attackPlayer(Entity& player) {
     float dx = abs(ai.x - player.x);
    float dy = abs(ai.y - player.y);

    // Nếu AI và player cách nhau < 32 pixel (nghĩa là gần nhau trong 1 ô tile 32x32)
    if (dx < 32 && dy < 32) {
        std::cout << "AI tấn công người chơi!" << std::endl;
        player.health -= 10;
    }
}

void Enemy::render() {
     /*if (enemyTexture != nullptr) {
        SDL_Rect renderQuad = { static_cast<int>(ai.x), static_cast<int>(ai.y), 32, 32 };
        SDL_RenderCopy(renderer, enemyTexture, nullptr, &renderQuad); }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &renderQuad); */
        SDL_Rect renderQuad = { static_cast<int>(ai.x), static_cast<int>(ai.y), 32, 32 };

    if (enemyTexture != nullptr) {
        SDL_RenderCopy(renderer, enemyTexture, nullptr, &renderQuad);
    } else {
        // Vẽ ô đỏ để kiểm tra nếu texture không có
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &renderQuad);
    }
}

int Enemy::getX() const {
    return ai.x;
}

int Enemy::getY() const {
    return ai.y;
}

int Enemy::getHealth() const {
    return ai.health;
}

bool Enemy::loadTexture(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cout << "Không thể load ảnh enemy: " << path << " - SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    enemyTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!enemyTexture) {
        std::cout << "Không thể tạo texture từ surface - SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}
