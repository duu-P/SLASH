#ifndef SIMPLE_HEART_H
#define SIMPLE_HEART_H

#include <SDL.h>
#include <vector>

class SimpleHeart {
public:
    SimpleHeart(SDL_Renderer* renderer);
    ~SimpleHeart();

    bool loadTexture(const char* filePath);
    void render();
    void loseLife();
    void reset();
    int getLives() const;


private:
    SDL_Renderer* renderer;
    SDL_Texture* heartTexture;
    int maxLives = 3;
    int currentLives = 3;
    int heartSize = 32;
};

#endif

