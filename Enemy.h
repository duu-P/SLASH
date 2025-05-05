#ifndef ENEMY_H
#define ENEMY_H
#include<SDL.h>
#include "player.h"
class Player;
class Enemy {
public:
    Enemy(int x, int y, SDL_Texture* texture);

    void update(Player& player); // AI hành vi chính
    void render(SDL_Renderer* renderer); // Vẽ enemy
    void takeDamage(int damage);
    void kill();
    bool isDead() const;
    bool isInAttackRange(const Player& player, int attackRange);

    int getX() const;
    int getY() const;
    SDL_Rect getRect() const;

    // Spawn Quái
    void spawnRandom(int screenWidth, int screenHeight);
    bool isActive() const { return active; }
    void setActive(bool a) { active = a; }

    void setMoveCooldown(Uint32 cooldown) { moveCooldown = cooldown; }


    Uint32 lastAttackTime = 0;
    const Uint32 attackCooldown = 600; // 0.5 giây

private:
    int x, y;
    int health;
    SDL_Texture* texture;
    bool active = false;

    bool isAdjacentTo(const Player& player);
    void moveTowards(const Player& player);
    void attack(Player& player);
     SDL_Rect rect;

    Uint32 lastMoveTime = 0;           // Lưu thời điểm lần cuối di chuyển
    Uint32 moveCooldown = 200;
};

#endif // ENEMY_H


