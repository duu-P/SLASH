/*#include "score.h"
#include <SDL_ttf.h>
#include <string>
using namespace std;

Score::Score() : currentScore(0), scoreTexture(nullptr) {
    scoreRect.x = 10; // Vị trí trên góc phải
    scoreRect.y = 10;
    scoreRect.w = 100; // Kích thước width cho score
    scoreRect.h = 30;  // Kích thước height cho score
}

Score::~Score() {
    if (scoreTexture) {
        SDL_DestroyTexture(scoreTexture);
        scoreTexture = nullptr;
    }
}

void Score::updateScore(int points) {
    currentScore += points;
}

void Score::updateScoreTexture(SDL_Renderer* renderer, TTF_Font* font) {
    if (scoreTexture) {
        SDL_DestroyTexture(scoreTexture);
        scoreTexture = nullptr;
    }
    string scoreText = "Score: " + to_string(currentScore);
    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), {255, 255, 255}); // Màu trắng
    if (surface) {
        scoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

}

void Score::render(SDL_Renderer* renderer, TTF_Font* font) {
    updateScoreTexture(renderer, font); // Cập nhật texture mỗi khi render
    if (scoreTexture) {
        SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
    }
}*/


