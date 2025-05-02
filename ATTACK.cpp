#include "attack.h"
#include <SDL_image.h>
#include <SDL_log.h>

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

    // Tính hướng tấn công
    int dx = mouseX - playerX;
    int dy = mouseY - playerY;

    if (abs(dx) > abs(dy)) {
        dx = (dx > 0) ? 1 : -1;
        dy = 0;
    } else {
        dx = 0;
        dy = (dy > 0) ? 1 : -1;
    }

    attackRect.x = playerX + dx * 32;
    attackRect.y = playerY + dy * 32;
    attackRect.w = 32;
    attackRect.h = 32;
}

void Attack::update() {
     if (isAttacking) {
        timer--;
        if (timer <= 0) {
            isAttacking = false;
        }
    }
}

void Attack::render(SDL_Renderer* renderer) {
    if (isAttacking && attackTexture) {
        SDL_RenderCopy(renderer, attackTexture, nullptr, &attackRect);
    }
}

bool Attack::isAttackingNow() const {
    return isAttacking;
}

SDL_Rect Attack::getAttackRect() const {
    return attackRect;
}



