//
// Created by yunp on 12/1/20.
//

#include "Resource.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct SDL_Texture *walkTexture;

int Resource_Load(SDL_Renderer *renderer) {

    walkTexture = IMG_LoadTexture(renderer, "walk.png");
    if (walkTexture == NULL) {
        SDL_Log("Can not load texture, %s", IMG_GetError());
        return 1;
    }
    return 0;
}


struct SDL_Texture *Resource_GetWalkTexture() {
    return walkTexture;
}

void Resource_Unload() {
    SDL_DestroyTexture(walkTexture);
}
