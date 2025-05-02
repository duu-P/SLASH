#ifndef MAP_H
#define MAP_H

#include <SDL.h>

const int TILE_SIZE = 16;
const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 36;

class Map {
public:
    Map();
    void loadTileset(SDL_Renderer* renderer, const char* filename);
    void render(SDL_Renderer* renderer);
    void clean();

private:
    int map[MAP_HEIGHT][MAP_WIDTH];
    SDL_Texture* tileset;
};

#endif

