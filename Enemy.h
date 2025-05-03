#ifndef ENEMY_H
#define ENEMY_H
#include<SDL.h>
#include<string>


struct Entity {
    float x, y; // Vị trí
    int health; // Sức khỏe
};

class Enemy {
public:
    Enemy(int startX, int startY, int startHealth, SDL_Renderer* renderer); // Constructor

    void moveTowardsPlayer(const Entity& player); // Di chuyển về phía người chơi
    void attackPlayer(Entity& player); // Tấn công người chơi
    float distanceManhattan(float x1, float y1, float x2, float y2); // Tính khoảng cách Manhattan
    void render();

    // Getters và Setters
    int getX() const;
    int getY() const;
    int getHealth() const;
    bool loadTexture(const std::string& path);

private:
    Entity ai; // Thông tin của AI
    SDL_Texture* enemyTexture;
    SDL_Renderer* renderer;
};

#endif // ENEMY_H

