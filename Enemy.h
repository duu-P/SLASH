#ifndef ENEMY_H
#define ENEMY_H
#include<SDL.h>
#include "player.h"
#include "SimpleHeart.h"
class Player;
class Enemy {
public:
    Enemy(int x, int y, SDL_Texture* texture);

    void update(Player& player,SimpleHeart& hearts); // AI hành vi
    void render(SDL_Renderer* renderer);
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
    const Uint32 attackCooldown = 600; // 0.6 giây

private:
    int x, y;
    int health;
    SDL_Texture* texture;
    bool active = false;
    bool facingRight;

    bool isAdjacentTo(const Player& player);
    void moveTowards(const Player& player);
    void attack(Player& player, SimpleHeart& hearts);
     SDL_Rect rect;

    Uint32 lastMoveTime = 0;           // Lưu thời điểm lần cuối di chuyển
    Uint32 moveCooldown = 200;
};

#endif // ENEMY_H


