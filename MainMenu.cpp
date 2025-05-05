/*#include "mainmenu.h"
#include <SDL_image.h>
#include <string>

// Hàm tải texture
SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path.c_str());
}

void handleMainMenu(SDL_Renderer* renderer) {
    bool quit = false;
    SDL_Event e;

    // Tải texture cho background và nút play
    SDL_Texture* backgroundTexture = loadTexture(renderer, "C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/BACKGROUND.png");
    SDL_Texture* playButtonTexture = loadTexture(renderer, "C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/Play.png");

    GameState gameState = STATE_MENU;

    // Vòng lặp sự kiện
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (gameState == STATE_MENU) {
                handleMenuEvent(e, gameState);
            }
        }

        // Vẽ menu hoặc game
        SDL_RenderClear(renderer);
        if (gameState == STATE_MENU) {
            renderMenu(renderer, backgroundTexture, playButtonTexture);
        } else if (gameState == STATE_PLAY) {
            renderGame(renderer); // Gọi game chính của bạn
        }

        // Cập nhật màn hình
        SDL_RenderPresent(renderer);
    }

    // Khi thoát, giải phóng tài nguyên
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(playButtonTexture);
}

inline void renderMenu(SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Texture* playButtonTexture) {
    // Vẽ ảnh nền
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    // Vẽ ảnh nút Play
    SDL_RenderCopy(renderer, playButtonTexture, nullptr, &playButtonRect);
}

inline void handleMenuEvent(SDL_Event& e, GameState& state) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = e.button.x;
        int mouseY = e.button.y;

        if (mouseX >= playButtonRect.x && mouseX <= playButtonRect.x + playButtonRect.w &&
            mouseY >= playButtonRect.y && mouseY <= playButtonRect.y + playButtonRect.h) {
            state = STATE_PLAY;
        }
    }
} */



