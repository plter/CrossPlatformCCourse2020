//
// Created by yunp on 12/4/20.
//

#include "Slider.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_FPoint *sliderBarPoint;
} SliderData;

static void drawCallback(struct DisplayObject *displayObject, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRectF(renderer, displayObject->dest);

    SliderData *data = (SliderData *) displayObject->subClassData;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    struct SDL_FRect d = {data->sliderBarPoint->x, data->sliderBarPoint->y, 20, 20};
    SDL_RenderDrawRectF(renderer, &d);
}

static void mouseMoveCallback(struct DisplayObject *displayObject, SDL_Event *event) {
    SliderData *data = displayObject->subClassData;
    data->sliderBarPoint->x = event->motion.x;
    if (data->sliderBarPoint->x < displayObject->dest->x) {
        data->sliderBarPoint->x = displayObject->dest->x;
    }
    if (data->sliderBarPoint->x > displayObject->dest->x + displayObject->dest->w - 20) {
        data->sliderBarPoint->x = displayObject->dest->x + displayObject->dest->w - 20;
    }
}

DisplayObject *SliderCreate(float x, float y) {
    struct DisplayObject *obj = DisplayObjectCreate(x, y, 200, 10, &drawCallback, &mouseMoveCallback);

    SliderData *data = malloc(sizeof(SliderData));
    obj->subClassData = data;
    data->sliderBarPoint = malloc(sizeof(struct SDL_FPoint));
    data->sliderBarPoint->x = x;
    data->sliderBarPoint->y = y - 5;
    return obj;
}

void SliderDestroy(struct DisplayObject *self) {
    free(((SliderData *) (self->subClassData))->sliderBarPoint);
    free(self->subClassData);
    DisplayObjectDestroy(self);
}