//
// Created by yunp on 12/1/20.
//

#include "Resource.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface *cursorSurface;
SDL_Cursor *cursor;
SDL_Texture *cursorTexture;

int Resource_Load(SDL_Renderer *renderer) {
    cursorSurface = IMG_Load("cursor.png");
    if (cursorSurface == NULL) {
        SDL_Log("Can not load cursor, %s", IMG_GetError());
        return 1;
    }
    cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
    cursorTexture = SDL_CreateTextureFromSurface(renderer, cursorSurface);
    return 0;
}

struct SDL_Texture *Resource_GetCursorTexture() {
    return cursorTexture;
}

SDL_Surface *Resource_GetCursorSurface() {
    return cursorSurface;
}

SDL_Cursor *Resource_GetCursor() {
    return cursor;
}

void Resource_Unload() {
    SDL_DestroyTexture(cursorTexture);
    SDL_FreeCursor(cursor);
    SDL_FreeSurface(cursorSurface);
}
