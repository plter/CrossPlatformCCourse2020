//
// Created by yunp on 12/1/20.
//

#include "Resource.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define BALL_FILE_NAME "ball.png"

SDL_Texture *ballTexture;

int Resource_Load(SDL_Renderer *renderer) {
    ballTexture = IMG_LoadTexture(renderer, BALL_FILE_NAME);
    if (ballTexture == NULL) {
        SDL_Log("Can not load texture, %s", IMG_GetError());
        return 1;
    }
    return 0;
}

SDL_Texture *Resource_GetBallTexture() {
    return ballTexture;
}

void Resource_Unload() {
    SDL_DestroyTexture(ballTexture);
}
