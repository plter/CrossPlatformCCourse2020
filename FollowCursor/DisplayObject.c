//
// Created by yunp on 12/4/20.
//

#include "DisplayObject.h"


DisplayObject *DisplayObjectCreate(
        float x, float y, float w, float h,
        DisplayObjectOnDrawCallback onDrawCallback,
        DisplayOnMouseMoveCallback onMouseMoveCallback
) {
    struct DisplayObject *obj = malloc(sizeof(struct DisplayObject));
    obj->dest = malloc(sizeof(struct SDL_FRect));
    obj->dest->x = x;
    obj->dest->y = y;
    obj->dest->w = w;
    obj->dest->h = h;
    obj->onDraw = onDrawCallback;
    obj->onMouseMove = onMouseMoveCallback;
}

void DisplayObjectDraw(DisplayObject *self, SDL_Renderer *renderer) {
    if (self->onDraw != NULL) {
        self->onDraw(self, renderer);
    }
}

void DisplayObjectOnMouseMove(struct DisplayObject *self, SDL_Event *event) {
    if (self->onMouseMove != NULL) {
        self->onMouseMove(self, event);
    }
}

void DisplayObjectDestroy(DisplayObject *self) {
    free(self->dest);
    free(self);
}