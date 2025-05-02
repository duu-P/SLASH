#include "Map.h"
#include <SDL_image.h>

Map::Map() {
    // Gán toàn bộ map là sàn (tile loại 1)
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            map[y][x] = 1;
        }
    }

    // Tường xung quanh
    for (int x = 0; x < MAP_WIDTH; x++) {
        map[0][x] = 0;
        map[MAP_HEIGHT - 1][x] = 0;
    }
    for (int y = 0; y < MAP_HEIGHT; y++) {
        map[y][0] = 0;
        map[y][MAP_WIDTH - 1] = 0;
    }

    tileset = nullptr;
}

void Map::loadTileset(SDL_Renderer* renderer, const char* filename) {
    SDL_Surface* tempSurface = IMG_Load(filename);
    tileset = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

void Map::render(SDL_Renderer* renderer) {
    if (!tileset) return;

    SDL_Rect srcRect, destRect;
    srcRect.w = destRect.w = TILE_SIZE;
    srcRect.h = destRect.h = TILE_SIZE;

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            int tileType = map[y][x];
            srcRect.x = tileType * TILE_SIZE;
            srcRect.y = 0;
            destRect.x = x * TILE_SIZE;
            destRect.y = y * TILE_SIZE;
            SDL_RenderCopy(renderer, tileset, &srcRect, &destRect);
        }
    }

}

void Map::clean() {
    SDL_DestroyTexture(tileset);
}

