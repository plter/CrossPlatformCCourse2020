//
// Created by yunp on 12/4/20.
//

#include "Cursor.h"
#include "Resource.h"

static void CursorOnDraw(DisplayObject *displayObject, SDL_Renderer *renderer) {
    SDL_RenderCopyF(renderer, Resource_GetCursorTexture(), NULL, displayObject->dest);
}

static void CursorOnMouseMove(struct DisplayObject *displayObject, SDL_Event *event) {
    displayObject->dest->x = event->motion.x;
    displayObject->dest->y = event->motion.y;
}


DisplayObject *CursorCreate(float x, float y, float w, float h) {
    return DisplayObjectCreate(
            x, y, w, h,
            &CursorOnDraw,
            &CursorOnMouseMove
    );
}

void CursorDestroy(struct DisplayObject *self) {
    DisplayObjectDestroy(self);
}