//
// Created by yunp on 12/4/20.
//

#ifndef CUSTOMCURSOR_DISPLAYOBJECT_H
#define CUSTOMCURSOR_DISPLAYOBJECT_H

#include <SDL2/SDL.h>

typedef struct DisplayObject {
    SDL_FRect *dest;

    void (*onDraw)(struct DisplayObject *displayObject, SDL_Renderer *renderer);

    void (*onMouseMove)(struct DisplayObject *displayObject, SDL_Event *event);
} DisplayObject;

typedef void (*DisplayOnMouseMoveCallback)(struct DisplayObject *displayObject, SDL_Event *event);

typedef void(*DisplayObjectOnDrawCallback)(struct DisplayObject *displayObject, SDL_Renderer *renderer);

DisplayObject *DisplayObjectCreate(
        float x, float y, float w, float h,
        DisplayObjectOnDrawCallback onDrawCallback,
        DisplayOnMouseMoveCallback onMouseMoveCallback
);

void DisplayObjectDraw(DisplayObject *self, SDL_Renderer *renderer);

void DisplayObjectOnMouseMove(struct DisplayObject *self, SDL_Event *event);

void DisplayObjectDestroy(DisplayObject *self);

#endif //CUSTOMCURSOR_DISPLAYOBJECT_H
