#ifndef PLAYER_H
#define PLAYER_H

#include<SDL.h>
#include "Enemy.h"
#include<vector>

class Enemy;

class Player {
public:
    Player();
    void handleEvent(const SDL_Event& e);
    void update(std::vector<Enemy*>& enemies);
    void render(SDL_Renderer* renderer);
    void loadTextures(SDL_Renderer* renderer, const char* idlePath, const char* walkPath);
    void resetAnimation();

    int getX() const { return x; }
    int getY() const { return y; }

    void takeDamage(int amount);
    int getHealth() const;

private:
    int x, y;       // Vị trí
    int speed;
    bool moveUp, moveDown, moveLeft, moveRight;

    int health = 10;

     SDL_Texture* idleTexture;
     SDL_Texture* walkTexture;
     SDL_Texture* attackPoseTexture;

    SDL_Rect srcRect;  // khung ảnh từ sprite sheet
    SDL_Rect dstRect;  // vị trí trên màn hình

    int frame;
    int frameTime;     // đếm thời gian chuyển frame
    const int FRAME_DELAY = 10;

    enum PlayerState { IDLE, WALKING, ATTACKING };
    PlayerState state = IDLE;

    enum Direction { RIGHT, LEFT };
    Direction currentDirection = RIGHT; // hướng nhìn của người chơi

};


#endif // PLAYER_H
