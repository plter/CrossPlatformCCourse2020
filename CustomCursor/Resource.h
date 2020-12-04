//
// Created by yunp on 12/1/20.
//

#ifndef DRAWBALLS_RESOURCE_H
#define DRAWBALLS_RESOURCE_H

#include <SDL2/SDL.h>

int Resource_Load(SDL_Renderer *renderer);

SDL_Surface *Resource_GetCursorSurface();

SDL_Cursor *Resource_GetCursor();

void Resource_Unload();

#endif //DRAWBALLS_RESOURCE_H
