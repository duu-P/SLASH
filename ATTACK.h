#ifndef ATTACK_H
#define ATTACK_H

#include <SDL.h>
#include<vector>
#include "Enemy.h"

using namespace std;
class Enemy;
class Attack {
public:
    Attack();
    ~Attack();

    // Xử lí hình ảnh hiển thị con chuột
    void loadCrosshair(SDL_Renderer* renderer, const char* imagePath);
    void renderCrosshair(SDL_Renderer* renderer);

    // Thực hiện đòn đánh
    void loadAttackTexture(SDL_Renderer* renderer, const char* path);
    void startAttack(int playerX, int playerY, int mouseX, int mouseY);
    void update(vector<Enemy*>& enemies);
    void render(SDL_Renderer* renderer);

     bool checkEnemyHit(Enemy* enemy);
     void setDamage(int damage) { this->damage = damage; }
     int getDamage() const { return damage; }

    bool isAttackingNow() const;
    SDL_Rect getAttackRect() const;


private:
    SDL_Texture* crosshairTexture;
    int width, height;

    bool isAttacking;
    int attackDuration;
    int attackTimer;
    int damage = 100;

    SDL_Texture* attackTexture;
    SDL_Rect attackRect;

    float angle = 0.0f; // Góc tấn công (radian)ư

    int timer;
    const int duration = 30; // khoảng 1 giây nếu 60 FPS

};

#endif
