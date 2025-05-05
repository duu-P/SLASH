/*#ifndef SIMPLE_HEART_H
#define SIMPLE_HEART_H

#include <SDL.h>
#include <SDL_image.h>

class SimpleHeart {
public:
    SimpleHeart();
    ~SimpleHeart();

    // Khởi tạo hệ thống máu
    bool init(SDL_Renderer* renderer, const char* heartImagePath);

    // Mất 1 mạng
    void loseLife();

    // Vẽ máu lên màn hình
    void render(SDL_Renderer* renderer);

    // Kiểm tra còn sống
    bool isAlive() const;

    // Reset về 3 mạng
    void reset();

private:
    SDL_Texture* heartTexture;
    int lives;
    int heartWidth;
    int heartHeight;
};

#endif */
