#include "enemy.h"
#include <cmath>
#include <iostream>
#include "Player.h"
#include <cstdlib>
#include <ctime>
#include "SimpleHeart.h"

using namespace std;
const int TILE_SIZE = 16;
const int SPRITE_SIZE = 32;

Enemy::Enemy(int x, int y, SDL_Texture* texture)
    : x(x), y(y), texture(texture), health(100) {
    rect = {x * TILE_SIZE, y * TILE_SIZE, SPRITE_SIZE, SPRITE_SIZE};}

int Enemy::getX() const { return x; }
int Enemy::getY() const { return y; }

void Enemy::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        kill();
    }
}

bool Enemy::isDead() const {
    return health <= 0;
}

void Enemy::update(Player& player, SimpleHeart& hearts) {
    Uint32 now = SDL_GetTicks();
    if (now - lastMoveTime < moveCooldown) return; // Đợi đến khi đủ thời gian

    lastMoveTime = now;

    if (isAdjacentTo(player)) {
        attack(player, hearts);
    } else {
        moveTowards(player);
    }
}

bool Enemy::isAdjacentTo(const Player& player) {
    int playerTileX = player.getX() / TILE_SIZE;
    int playerTileY = player.getY() / TILE_SIZE;

    int dx = abs(x - playerTileX);
    int dy = abs(y - playerTileY);
    return (dx + dy == 1); }

void Enemy::moveTowards(const Player& player) {
    int targetX = player.getX() / TILE_SIZE;
    int targetY = player.getY() / TILE_SIZE;

    int dx = targetX - x;
    int dy = targetY - y;

    if (dx > 0) {
        facingRight = true; // Sang phải
    }
    else if (dx < 0) {
        facingRight = false; // Sang trái
    }

    if (abs(dx) > abs(dy)) {
        x += (dx > 0) ? 1 : -1;
    } else if (dy != 0) {
        y += (dy > 0) ? 1 : -1;
    }
}

void Enemy::attack(Player& player, SimpleHeart& hearts) {
    Uint32 now = SDL_GetTicks();
    if (now - lastAttackTime < attackCooldown) return;

    lastAttackTime = now;
    cout << "Enemy attacks!" << endl;
    player.takeDamage(1);
    hearts.loseLife();
}

void Enemy::render(SDL_Renderer* renderer) {
    if (isDead()) return;
    SDL_Rect srcRect = {0, 0, SPRITE_SIZE, SPRITE_SIZE}; //  dùng frame đầu tiên
    SDL_Rect dstRect;

    dstRect.x = x * TILE_SIZE + (TILE_SIZE / 2); // Căn giữa tile 16px
    dstRect.y = y * TILE_SIZE + (TILE_SIZE / 2);
    dstRect.w = SPRITE_SIZE;
    dstRect.h = SPRITE_SIZE;

    rect = dstRect;


    SDL_RendererFlip flip = facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0, NULL, flip);
}

SDL_Rect Enemy::getRect() const {
    return rect;  // vị trí và kích thước của enemy
}

void Enemy::kill() {
    health = 0;
    std::cout << "Enemy instantly killed!" << std::endl;
}

void Enemy::spawnRandom(int screenWidth, int screenHeight) {
   const int tileSize = 16;  // Kích thước mỗi ô tile
    int spawnTileX, spawnTileY;

    // Chọn hướng spawn: 0 là trái, 1 là phải, 2 là dưới
    int direction = std::rand() % 3;

    switch (direction) {
        case 0: // Trái
            spawnTileX = -1;  // Tọa độ X ở ngoài rìa trái
            spawnTileY = std::rand() % (screenHeight / tileSize);
            break;

        case 1: // Phải (
            spawnTileX = screenWidth / tileSize;
            spawnTileY = std::rand() % (screenHeight / tileSize);
            break;

        case 2: // Dưới (
            spawnTileX = std::rand() % (screenWidth / tileSize);  // Tạo tọa độ X trong khoảng từ 0 đến chiều rộng màn hình
            spawnTileY = screenHeight / tileSize;  // Tọa độ Y ở ngoài rìa dưới
            break;
    }

    x = spawnTileX;
    y = spawnTileY;

    active = true;
    health=100;
     rect = {x, y, 32, 32};
}




