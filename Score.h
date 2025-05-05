/*#ifndef SCORE_H
#define SCORE_H

#include <SDL.h>
#include <SDL_ttf.h>

class Score {
public:
    Score();
    ~Score();

    void updateScore(int points);
    void render(SDL_Renderer* renderer, TTF_Font* font);

private:
    int currentScore;
    SDL_Texture* scoreTexture;
    SDL_Rect scoreRect;
    void updateScoreTexture(SDL_Renderer* renderer, TTF_Font* font);
};

#endif */

