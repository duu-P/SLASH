#include "PLAYER.h"
#include<SDL_image.h>
#include"attack.h"
#include<iostream>
#include "Enemy.h"


Player::Player() {
    x = 380;
    y = 270;
    speed = 1;
    moveUp = moveDown = moveLeft = moveRight = false;

    idleTexture = nullptr;
    walkTexture = nullptr;

    frame = 0;
    frameTime = 0;
    state = IDLE;

    srcRect = { 0, 0, 32, 32 };
    dstRect = { x, y, 32, 32 };
}

Attack attack;

void Player::loadTextures(SDL_Renderer* renderer, const char* idlePath, const char* walkPath)
{
    SDL_Surface* idleSurface = IMG_Load(idlePath);
    SDL_Surface* walkSurface = IMG_Load(walkPath);

    idleTexture = SDL_CreateTextureFromSurface(renderer, idleSurface);
    walkTexture = SDL_CreateTextureFromSurface(renderer, walkSurface);

    SDL_FreeSurface(idleSurface);
    SDL_FreeSurface(walkSurface);

    attack.loadAttackTexture(renderer, "C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/Effect attack.png");
    attackPoseTexture = IMG_LoadTexture(renderer, "C:/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SLASH/Đồ họa game/Player-attack.png");
}



SDL_Texture* attackPoseTexture;
enum PlayerState { IDLE, WALKING, ATTACKING };
void Player::handleEvent(const SDL_Event& e) {

   if (state == ATTACKING) return;

    if (e.type == SDL_KEYDOWN && !e.key.repeat) {  // chỉ xử lý khi mới nhấn
        switch (e.key.keysym.sym) {
            case SDLK_w:
                moveUp = true;
                break;
            case SDLK_s:
                moveDown = true;
                break;
            case SDLK_a:
                moveLeft = true;
                currentDirection = LEFT;
                break;
            case SDLK_d:
                moveRight = true;
                currentDirection = RIGHT;
                break;
        }
    } else if (e.type == SDL_KEYUP && !e.key.repeat) {  // xử lý khi thả phím
        switch (e.key.keysym.sym) {
            case SDLK_w:
                moveUp = false;
                break;
            case SDLK_s:
                moveDown = false;
                break;
            case SDLK_a:
                moveLeft = false;
                break;
            case SDLK_d:
                moveRight = false;
                break;
        }
    }

    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && !attack.isAttackingNow()) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    int centerX = x + 32 / 2;
    int centerY = y + 32 / 2;
    attack.startAttack(x, y, mouseX, mouseY);

    // Khi tấn công thì không di chuyển
    moveUp = moveDown = moveLeft = moveRight = false; }
     /*if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        attack.startAttack(x, y, e.button.x, e.button.y);
        state = ATTACKING; // Khóa player
    } */
}


void Player::update(std::vector<Enemy*>& enemies) {

    if (state == ATTACKING) {
        attack.update(enemies);
        /*if (!attack.isAttackingNow()) {
            state = IDLE; // Mở khóa player
            frame = 0;

        } */
        return;
    }
    state = IDLE;
    //bool wasMoving = (state == WALKING);
    //bool isMoving = moveUp || moveDown || moveLeft || moveRight;


    //state = isMoving ? WALKING : IDLE;


        //if (moveUp) y -= speed; state = WALKING;
        //if (moveDown) y += speed; state = WALKING;
        //if (moveLeft) x -= speed; state = WALKING;
        //if (moveRight) x += speed; state = WALKING;
         if (moveUp) {
        y -= speed;
        state = WALKING;
    }
    if (moveDown) {
        y += speed;
        state = WALKING;
    }
    if (moveLeft) {
        x -= speed;
        state = WALKING;
    }
    if (moveRight) {
        x += speed;
        state = WALKING;
    }


    // animation
    frameTime++;
    if (frameTime >= FRAME_DELAY) {
        frame = (frame + 1) % 4; // có 4 frame
        frameTime = 0;
        //srcRect.x = frame * 32;
    }
       srcRect.x = frame * 32;

    attack.update(enemies);
}

void Player::render(SDL_Renderer* renderer) {
    dstRect.x = x;
    dstRect.y = y;

    SDL_Texture* current;
    if (attack.isAttackingNow()) {
        current = attackPoseTexture;
        srcRect.x = 0;
    }
    else {
        current = (state == WALKING) ? walkTexture : idleTexture;
        srcRect.x = frame * 32;
    }

    if (currentDirection == LEFT) {
        SDL_RenderCopyEx(renderer, current, &srcRect, &dstRect, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopy(renderer, current, &srcRect, &dstRect);
    }

    attack.render(renderer);
}

void Player::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;

    // In ra log hoặc cập nhật UI
    std::cout << "Player takes " << amount << " damage. Remaining HP: " << health << std::endl;
}

int Player::getHealth() const {
    return health;
}




