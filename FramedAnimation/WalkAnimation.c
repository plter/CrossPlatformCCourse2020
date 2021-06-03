//
// Created by yunp on 12/7/20.
//

#include "WalkAnimation.h"
#include "Resource.h"

typedef struct {
    int currentFrameIndex;
    uint32_t globalFramesCount;
    SDL_Rect frames[7];
    SDL_bool _walking;
    float speed;
    SDL_RendererFlip frameFlip;
} WalkAnimationData;


static void WalkAnimationOnDraw(struct DisplayObject *displayObject, SDL_Renderer *renderer) {
    WalkAnimationData *data = displayObject->subClassData;

    SDL_RenderCopyExF(
            renderer, Resource_GetWalkTexture(),
            &data->frames[data->currentFrameIndex],
            displayObject->dest,
            0, NULL, data->frameFlip
    );

    data->globalFramesCount++;
    if (data->_walking) {
        if (data->globalFramesCount % 10 == 0) {
            displayObject->dest->x += data->speed;
            data->currentFrameIndex++;

            if (data->currentFrameIndex == 5) {
                data->currentFrameIndex = 0;
            }
        }
    }
}


DisplayObject *WalkAnimationCreate() {
    WalkAnimationData *data = malloc(sizeof(WalkAnimationData));
    data->currentFrameIndex = 6;
    data->globalFramesCount = 0;
    data->_walking = SDL_FALSE;
    data->speed = 30;
    data->frameFlip = SDL_FLIP_NONE;
    for (int i = 0; i < 7; ++i) {
        data->frames[i].y = 0;
        data->frames[i].x = i * 162;
        data->frames[i].w = 162;
        data->frames[i].h = 265;
    }

    struct DisplayObject *obj = DisplayObjectCreate(0, 0, 162, 265, &WalkAnimationOnDraw, NULL);
    obj->subClassData = data;
    return obj;
}

void WalkAnimationGotoAndPlay(struct DisplayObject *anim, int frameIndex) {
    WalkAnimationData *data = anim->subClassData;
    data->currentFrameIndex = frameIndex;
    data->_walking = SDL_TRUE;
}

SDL_bool WalkAnimationIsWalking(struct DisplayObject *anim) {
    WalkAnimationData *data = anim->subClassData;
    return data->_walking;
}

void WalkAnimationGotoAndStop(DisplayObject *anim, int frameIndex) {
    WalkAnimationData *data = anim->subClassData;
    data->_walking = SDL_FALSE;
    data->currentFrameIndex = frameIndex;
}

void WalkAnimationWalkRight(struct DisplayObject *anim) {
    if (!WalkAnimationIsWalking(anim)) {
        WalkAnimationData *data = anim->subClassData;
        if (data->speed < 0) {
            data->speed *= -1;
        }
        data->frameFlip = SDL_FLIP_NONE;
        WalkAnimationGotoAndPlay(anim, 0);
    }
}

void WalkAnimationWalkLeft(struct DisplayObject *anim) {
    if (!WalkAnimationIsWalking(anim)) {
        WalkAnimationData *data = anim->subClassData;
        if (data->speed > 0) {
            data->speed *= -1;
        }
        data->frameFlip = SDL_FLIP_HORIZONTAL;
        WalkAnimationGotoAndPlay(anim, 0);
    }
}

void WalAnimationStop(struct DisplayObject *anim) {
    WalkAnimationGotoAndStop(anim, 6);
}


void WalkAnimationDestroy(struct DisplayObject *self) {
    WalkAnimationData *data = self->subClassData;
    free(data);
    DisplayObjectDestroy(self);
}