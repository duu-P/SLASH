#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "PLAYER.h"
#include "Map.h"
#include "ATTACK.h"
#include "Enemy.h"
#include<vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Score.h"
#include "GameMenu.h"
#include "SimpleHeart.h"


using namespace std;

const int SCREEN_WIDTH = 768; // 768= 16 * 48
const int SCREEN_HEIGHT = 544; // 544= 16 * 34
const char* WINDOW_TITLE = "SLASH";

int spawnCount = 3;       // U1 = 3 quái ban đầu
int spawnCountIncrement = 5; // d = 1 , sản sinh theo cấp số cộng
float spawnInterval = 5000; // ban đầu 5 giây
float intervalIncrement = 1000; //  (1000ms)
const float MAX_INTERVAL = 10000; // 10s

Uint32 lastSpawnTime = 0;
int currentWave = 0;

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

void spawnEnemyWave(vector<Enemy*>& enemies, SDL_Texture* enemyTexture, int screenWidth, int screenHeight) {
    // Tính số quái theo công thức: Uₙ = 3 + (n-1)*1
    int enemiesToSpawn = 3 + currentWave;

    // Tính thời gian giữa các wave: 5s -> 10s
    float spawnInterval = min(5000.0f + (currentWave * 1000.0f), 10000.0f);

    // Tăng tốc dộ
     Uint32 baseCooldown = 200;
    Uint32 speedIncrease = (currentWave / 10) * 5; // Cứ mỗi 10 wave tăng tốc +5ms
    Uint32 newCooldown = (baseCooldown > speedIncrease) ? baseCooldown - speedIncrease : 50;

    for (int i = 0; i < enemiesToSpawn; i++) {
        Enemy* newEnemy = new Enemy(0, 0, enemyTexture);
        newEnemy->spawnRandom(screenWidth, screenHeight);
        newEnemy->setMoveCooldown(newCooldown);
        enemies.push_back(newEnemy);
    }

    currentWave++;
    lastSpawnTime = SDL_GetTicks();

    //
    cout << "Spawned wave " << currentWave
              << " (" << enemiesToSpawn << " enemies)"
              << " | Next wave in " << (spawnInterval/1000) << "s\n";
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
    if (!texture) {
        cerr << "IMG_LoadTexture error: " << IMG_GetError() << endl;
    }
    return texture;
}






int main(int argc, char* argv[])
{
    //Khởi tạo môi trường đồ họa
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);

    SDL_Texture* gameOverTexture = IMG_LoadTexture(renderer, "C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/Game Over.png");
    bool isGameOver = false;

    GameMenu menu(renderer);
if (!menu.loadMedia("C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/BACKGROUND.png", "C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/PLAY-game.png")) {
    cerr << "Không thể tải ảnh menu!\n";
    quitSDL(window, renderer);
    return 1;
}

bool quit = false;
bool startGame = false;
SDL_Event menuEvent;

while (!quit && !startGame) {
    while (SDL_PollEvent(&menuEvent)) {
        if (menuEvent.type == SDL_QUIT) quit = true;
        menu.handleEvent(&menuEvent, startGame);
    }

    SDL_RenderClear(renderer);
    menu.render();
    SDL_RenderPresent(renderer);
}

if (quit) {
    quitSDL(window, renderer);
    return 0;
}


    // Tạo map
    Map gameMap;
    gameMap.loadTileset(renderer, "C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/Block.png");

    // Khai báo người chơi
    Player player;
    player.loadTextures(renderer,"C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/Player-Stand.png","C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/Player-Runn.png" );

    SimpleHeart hearts(renderer);
    hearts.loadTexture( "C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/Heart.png");

    SDL_Texture* enemyTexture = IMG_LoadTexture(renderer, "C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/Knight-enemy.png");

    vector<Enemy*> enemies;
    enemies.push_back(new Enemy(-1, -1, enemyTexture));


    Attack attack;
    attack.loadCrosshair(renderer, "C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/aim target.png");



    bool running = true;
    SDL_Event event;

    Attack playerAttack;





    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) running = false;

            player.handleEvent(event);
        }

        if (!isGameOver) {
        // Spawn theo wave
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastSpawnTime > std::min(5000 + (currentWave * 1000), 10000)) {
            spawnEnemyWave(enemies, enemyTexture, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        player.update(enemies);

        int targetLives = player.getHealth();
    while (hearts.getLives() > targetLives) {
        hearts.loseLife();
    }


        for (auto it = enemies.begin(); it != enemies.end(); ) {
            if ((*it)->isDead()) {
                delete *it;
                it = enemies.erase(it);
            } else {
                (*it)->update(player, hearts);
                ++it;
            }
        }
        attack.update(enemies);

        // Hết máu thì hiện màn hình Game Over
        if (player.getHealth() <= 0) {
                isGameOver = true;
        }
}

        SDL_RenderClear(renderer);

         if (!isGameOver) {
        gameMap.render(renderer);

        for (auto enemy : enemies) {
    if (!enemy->isDead()) {
        enemy->render(renderer);
    }
}
        player.render(renderer);


        attack.renderCrosshair(renderer);

        hearts.render(); }
        else {
            SDL_ShowCursor(SDL_ENABLE);
            SDL_RenderCopy(renderer, gameOverTexture, NULL, NULL);
        }

        SDL_RenderPresent(renderer);
    }
    for (auto enemy : enemies) {
        delete enemy; }
        enemies.clear();
    IMG_Quit();
    if (gameOverTexture) {
        SDL_DestroyTexture(gameOverTexture);
    }


    gameMap.clean();
    quitSDL(window, renderer);
    return 0;
}














