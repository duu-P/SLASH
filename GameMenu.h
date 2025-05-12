#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include<string>

using namespace std;

class GameMenu {
public:
    GameMenu(SDL_Renderer* renderer);
    ~GameMenu();

    bool loadMedia(const std::string& backgroundPath, const std::string& playButtonPath);
    void handleEvent(SDL_Event* e, bool& startGame);
    void render();

private:
    SDL_Renderer* renderer;

    SDL_Texture* backgroundTexture;
    SDL_Texture* playButtonTexture;

    SDL_Rect playButtonRect;

    SDL_Texture* loadTexture(const std::string& path);
};

#endif // GAME_MENU_H


