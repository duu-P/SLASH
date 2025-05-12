#include<SDL.h>
#include "GameMenu.h"
#include<SDL_image.h>
using namespace std;

GameMenu::GameMenu(SDL_Renderer* renderer)
    : renderer(renderer), backgroundTexture(nullptr), playButtonTexture(nullptr) {
    playButtonRect = { 0, 0, 64, 64 }; // Kích thước nút Play
}

GameMenu::~GameMenu() {
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (playButtonTexture) SDL_DestroyTexture(playButtonTexture);
}

bool GameMenu::loadMedia(const std::string& backgroundPath, const std::string& playButtonPath) {
    backgroundTexture = loadTexture(backgroundPath);
    playButtonTexture = loadTexture(playButtonPath);

    if (!backgroundTexture || !playButtonTexture) {
        return false;
    }


    playButtonRect.x = 768 / 2 - playButtonRect.w / 2;
    playButtonRect.y = 544 / 2 - playButtonRect.h / 2;

    return true;
}

SDL_Texture* GameMenu::loadTexture(const std::string& path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    return texture;
}

void GameMenu::handleEvent(SDL_Event* e, bool& startGame) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x >= playButtonRect.x && x <= playButtonRect.x + playButtonRect.w &&
            y >= playButtonRect.y && y <= playButtonRect.y + playButtonRect.h) {
            startGame = true;
        }
    }
}

void GameMenu::render() {
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    SDL_RenderCopy(renderer, playButtonTexture, NULL, &playButtonRect);
}




