//
// Created by yunp on 12/2/20.
//

#ifndef DRAGRECT_RECTSHAPE_H
#define DRAGRECT_RECTSHAPE_H

#include <SDL2/SDL.h>

typedef struct RectShape {
    SDL_FRect dest;
    uint32_t color;
    SDL_FPoint _dragStartPoint;
    SDL_FPoint _dragStartMousePoint;
    int _dragEnabled;
    struct RectShape *pre;
    struct RectShape *next;
} RectShape;

RectShape *RectShape_Create(float x, float y, float w, float h, uint32_t color);

void RectShape_Draw(RectShape *self, SDL_Renderer *renderer);

SDL_bool RectShape_OnMouseEvent(RectShape *self, SDL_Event *event);

void RectShape_Destroy(RectShape *self);

#endif //DRAGRECT_RECTSHAPE_H
