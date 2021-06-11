//
// Created by yunp on 12/4/20.
//

#include "Eyeball.h"
#include "Resource.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect *eyeballSrcRect;
    SDL_FPoint *eyeCenter;
    float eyeR;
    SDL_FRect *eyeDestRect;
    struct SDL_Rect *eyeSrcRect;
} EyeballData;


static void CursorOnDraw(DisplayObject *displayObject, SDL_Renderer *renderer) {
    EyeballData *data = displayObject->subClassData;

    SDL_RenderCopyF(renderer, Resource_GetEyeTexture(), data->eyeSrcRect, data->eyeDestRect);
    SDL_RenderCopyF(renderer, Resource_GetEyeTexture(), data->eyeballSrcRect, displayObject->dest);
}

static void CursorOnMouseMove(struct DisplayObject *displayObject, SDL_Event *event) {
    float halfW = displayObject->dest->w / 2;
    float halfH = displayObject->dest->h / 2;
    displayObject->dest->x = event->motion.x - halfW;
    displayObject->dest->y = event->motion.y - halfH;

    EyeballData *data = displayObject->subClassData;
    float mouseDistanceX = event->motion.x - data->eyeCenter->x;
    float mouseDistanceY = event->motion.y - data->eyeCenter->y;
    float mouseDistance = SDL_sqrtf(mouseDistanceX * mouseDistanceX + mouseDistanceY * mouseDistanceY);
    if (mouseDistance > data->eyeR) {
        displayObject->dest->x = data->eyeCenter->x + mouseDistanceX / mouseDistance * data->eyeR - halfW;
        displayObject->dest->y = data->eyeCenter->y + mouseDistanceY / mouseDistance * data->eyeR - halfH;
    }
}


DisplayObject *EyeBallCreate(float x, float y) {
    EyeballData *data = malloc(sizeof(EyeballData));
    data->eyeballSrcRect = malloc(sizeof(struct SDL_Rect));
    data->eyeballSrcRect->x = 0;
    data->eyeballSrcRect->y = 0;
    data->eyeballSrcRect->w = 10;
    data->eyeballSrcRect->h = 10;
    data->eyeCenter = malloc(sizeof(struct SDL_FPoint));
    data->eyeCenter->y = y;
    data->eyeCenter->x = x;
    data->eyeR = 15;
    data->eyeDestRect = malloc(sizeof(struct SDL_FRect));
    data->eyeDestRect->x = data->eyeCenter->x - 20;
    data->eyeDestRect->y = data->eyeCenter->y - 20;
    data->eyeDestRect->w = 40;
    data->eyeDestRect->h = 40;
    data->eyeSrcRect = malloc(sizeof(struct SDL_Rect));
    data->eyeSrcRect->x = 10;
    data->eyeSrcRect->y = 0;
    data->eyeSrcRect->w = 40;
    data->eyeSrcRect->h = 40;


    struct DisplayObject *obj = DisplayObjectCreate(
            x, y, (float) data->eyeballSrcRect->w, (float) data->eyeballSrcRect->h,
            &CursorOnDraw,
            &CursorOnMouseMove
    );

    obj->subClassData = data;
    return obj;
}

void EyeballDestroy(struct DisplayObject *self) {
    free(((EyeballData *) self->subClassData)->eyeballSrcRect);
    free(((EyeballData *) self->subClassData)->eyeSrcRect);
    free(((EyeballData *) self->subClassData)->eyeCenter);
    free(((EyeballData *) self->subClassData)->eyeDestRect);
    free(self->subClassData);
    DisplayObjectDestroy(self);
}