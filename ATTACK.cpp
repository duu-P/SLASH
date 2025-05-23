#include "attack.h"
#include <SDL_image.h>
#include <SDL_log.h>
#include <cmath>
#include<vector>
#include "Enemy.h"

using namespace std;
const int TILE_SIZE = 16;
const int SPRITE_SIZE = 32;

Attack::Attack() {
    crosshairTexture = nullptr;
    width = height = 0;

    // Ẩn con trỏ chuột hệ thống
    SDL_ShowCursor(SDL_DISABLE);

    isAttacking = false;
    attackDuration = 10;
    //attackTimer = 0;
    attackTexture = nullptr;
    timer = 0;
    attackRect = {0, 0, 32, 32}; // vùng đánh mặc định
}

Attack::~Attack() {
    if (crosshairTexture) {
        SDL_DestroyTexture(crosshairTexture);
    }

    if (attackTexture) {
        SDL_DestroyTexture(attackTexture);
    }
}

void Attack::loadCrosshair(SDL_Renderer* renderer, const char* imagePath) {
    SDL_Surface* surface = IMG_Load(imagePath);

    crosshairTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!crosshairTexture) {
        SDL_Log("Không thể tạo texture crosshair: %s", SDL_GetError());
    } else {
        width = surface->w;
        height = surface->h;
    }

    SDL_FreeSurface(surface);
}

class Enemy;

void Attack::loadAttackTexture(SDL_Renderer* renderer, const char* path)
{
    SDL_Surface* surface = IMG_Load(path);
    attackTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void Attack::renderCrosshair(SDL_Renderer* renderer) {
    if (!crosshairTexture) return;

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_Rect dstRect;
    dstRect.x = mouseX - width / 2;  // Căn giữa
    dstRect.y = mouseY - height / 2;
    dstRect.w = width;
    dstRect.h = height;

    SDL_RenderCopy(renderer, crosshairTexture, nullptr, &dstRect);
}

void Attack::startAttack(int playerX, int playerY, int mouseX, int mouseY) {
    if (isAttacking) return; // đang tấn công thì không cho tấn công tiếp

    isAttacking = true;
    timer = duration;

    // Tính góc từ người chơi đến chuột
    int centerX = playerX + 32 / 2;
    int centerY = playerY + 32 / 2;

    angle = atan2(mouseY - centerY, mouseX - centerX);

    int distance = 32;
    int offsetX = static_cast<int>(cos(angle) * distance);
    int offsetY = static_cast<int>(sin(angle) * distance);



    attackRect.w = 32;
    attackRect.h = 32;
    attackRect.x = centerX + offsetX - attackRect.w / 2;
    attackRect.y = centerY + offsetY - attackRect.h / 2;

}

bool Attack::checkEnemyHit(Enemy* enemy) {
    // Kiểm tra enemy hợp lệ và còn sống
    if (!enemy || enemy->isDead()) {
        return false;
    }

    // Lấy hitbox của enemy
    SDL_Rect enemyRect = enemy->getRect();

    // Kiểm tra va chạm
    if (SDL_HasIntersection(&attackRect, &enemyRect)) {
        // Gây damage cho enemy
        enemy->takeDamage(damage);
        return true;
    }
    return false;
}

void Attack::update(vector<Enemy*>& enemies) {
     if (isAttacking) {
        timer--;


    for (auto enemy : enemies) {
            if (enemy && !enemy->isDead()) {
                SDL_Rect enemyRect = enemy->getRect(); // Lưu vào biến cục bộ trước
                if (SDL_HasIntersection(&attackRect, &enemyRect)) {
                    enemy->takeDamage(damage);
                }
            }
        }

        if (timer <= 0) {
            isAttacking = false;
        }
     }
}

void Attack::render(SDL_Renderer* renderer) {
    /*if (isAttacking && attackTexture) {
        SDL_RenderCopy(renderer, attackTexture, nullptr, &attackRect);
    } */
    if (!isAttacking || attackTexture == nullptr) return;

    double angleDegrees = angle * (180.0 / M_PI);
    SDL_Point center = { attackRect.w / 2, attackRect.h / 2 };

    SDL_RenderCopyEx(renderer, attackTexture, nullptr, &attackRect, angleDegrees, &center, SDL_FLIP_NONE);
}


bool Attack::isAttackingNow() const {
    return isAttacking;
}

SDL_Rect Attack::getAttackRect() const {
    return attackRect;
}



