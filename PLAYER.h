#ifndef PLAYER_H
#define PLAYER_H

#include<SDL.h>

class Player {
public:
    Player();
    void handleEvent(const SDL_Event& e);
    void update();
    void render(SDL_Renderer* renderer);
    void loadTextures(SDL_Renderer* renderer, const char* idlePath, const char* walkPath);

private:
    int x, y;       // Vị trí
    int speed;
    bool moveUp, moveDown, moveLeft, moveRight;

     SDL_Texture* idleTexture;
     SDL_Texture* walkTexture;
     SDL_Texture* attackPoseTexture;

    SDL_Rect srcRect;  // khung ảnh từ sprite sheet
    SDL_Rect dstRect;  // vị trí trên màn hình

    int frame;
    int frameTime;     // đếm thời gian chuyển frame
    const int FRAME_DELAY = 10;

    enum PlayerState { IDLE, WALKING };
    PlayerState state;

    enum Direction { RIGHT, LEFT };
    Direction currentDirection = RIGHT; // hướng nhìn của người chơi

};


#endif // PLAYER_H
