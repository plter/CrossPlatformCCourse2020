//
// Created by yunp on 12/1/20.
//

#include "Resource.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture *eyeTexture;

int Resource_Load(SDL_Renderer *renderer) {
    eyeTexture = IMG_LoadTexture(renderer, "eye.png");
    if (eyeTexture == NULL) {
        SDL_Log("Can not load texture, %s", IMG_GetError());
        return 1;
    }
    return 0;
}

struct SDL_Texture *Resource_GetEyeTexture() {
    return eyeTexture;
}

void Resource_Unload() {
    SDL_DestroyTexture(eyeTexture);
}
