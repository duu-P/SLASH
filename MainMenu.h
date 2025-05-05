/*fndef MAINMENU_H
#define MAINMENU_H

#include <SDL.h>

// Trạng thái trò chơi
enum GameState {
    STATE_MENU,
    STATE_PLAY
};
void renderGame(SDL_Renderer* renderer);
// Kích thước và vị trí nút Play
const SDL_Rect playButtonRect = { 300, 200, 200, 60 }; // Điều chỉnh theo ảnh thật nếu cần

// Vẽ menu chính bằng ảnh nền và ảnh nút
void renderMenu(SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Texture* playButtonTexture);

// Xử lý click vào nút Play
void handleMenuEvent(SDL_Event& e, GameState& state);


#endif // MAINMENU_H */

