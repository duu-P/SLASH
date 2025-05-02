#ifndef PLAYER_H
#define PLAYER_H

#include<SDL.h>

class Player {
public:
    Player();
    void handleEvent(const SDL_Event& e);
    void update();
    void render(SDL_Renderer* renderer);
    void loadTexture(SDL_Renderer* renderer, const char* filePath);

private:
    int x, y;       // Vị trí
    int speed;
    bool moveUp, moveDown, moveLeft, moveRight;
    SDL_Texture* texture;

};


#endif // PLAYER_H
