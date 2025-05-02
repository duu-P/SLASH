#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "PLAYER.h"
#include "Map.h"
#include "ATTACK.h"

using namespace std;

const int SCREEN_WIDTH = 768; // 768= 16 * 48
const int SCREEN_HEIGHT = 544; // 544= 16 * 34
const char* WINDOW_TITLE = "SLASH";

void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //full screen
    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}






int main(int argc, char* argv[])
{
    //Khởi tạo môi trường đồ họa
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);
    IMG_Init(IMG_INIT_PNG);
    //SDL_RenderSetLogicalSize(renderer, 553, 384); //tăng kích thước khung hình

    // Tạo map
    Map gameMap;
    gameMap.loadTileset(renderer, "C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/Block.png");

    // Khai báo người chơi
    Player player;
    player.loadTextures(renderer,"C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/Player-Stand.png","C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/Player-Runn.png" );

    Attack attack;
    attack.loadCrosshair(renderer, "C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/aim target.png");

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) running = false;

            player.handleEvent(event);
        }
        player.update();


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);

        gameMap.render(renderer);
        player.render(renderer);
        attack.renderCrosshair(renderer);


        SDL_RenderPresent(renderer);
    }
    IMG_Quit();


    gameMap.clean();
    quitSDL(window, renderer);
    return 0;
}














