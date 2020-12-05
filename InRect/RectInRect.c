//
// Created by yunp on 12/4/20.
//

#include "RectInRect.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_FRect *innerRect;
} SliderData;

static void drawCallback(struct DisplayObject *displayObject, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRectF(renderer, displayObject->dest);

    SliderData *data = (SliderData *) displayObject->subClassData;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawRectF(renderer, data->innerRect);
}

static void mouseMoveCallback(struct DisplayObject *displayObject, SDL_Event *event) {
    SliderData *data = displayObject->subClassData;
    data->innerRect->x = event->motion.x;
    if (data->innerRect->x < displayObject->dest->x) {
        data->innerRect->x = displayObject->dest->x;
    }
    if (data->innerRect->x > displayObject->dest->x + displayObject->dest->w - data->innerRect->w) {
        data->innerRect->x = displayObject->dest->x + displayObject->dest->w - data->innerRect->w;
    }
    data->innerRect->y = event->motion.y;
    if (data->innerRect->y < displayObject->dest->y) {
        data->innerRect->y = displayObject->dest->y;
    }
    if (data->innerRect->y > displayObject->dest->y + displayObject->dest->h - data->innerRect->h) {
        data->innerRect->y = displayObject->dest->y + displayObject->dest->h - data->innerRect->h;
    }
}

DisplayObject *RectInRectCreate(float x, float y) {
    struct DisplayObject *obj = DisplayObjectCreate(x, y, 200, 100, &drawCallback, &mouseMoveCallback);

    SliderData *data = malloc(sizeof(SliderData));
    obj->subClassData = data;
    data->innerRect = malloc(sizeof(struct SDL_FRect));
    data->innerRect->x = x;
    data->innerRect->y = y;
    data->innerRect->w = 30;
    data->innerRect->h = 30;
    return obj;
}

void RectInRectDestroy(struct DisplayObject *self) {
    free(((SliderData *) (self->subClassData))->innerRect);
    free(self->subClassData);
    DisplayObjectDestroy(self);
}