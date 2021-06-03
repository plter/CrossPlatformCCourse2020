//
// Created by yunp on 12/7/20.
//

#ifndef FRAMEDANIMATION_WALKANIMATION_H
#define FRAMEDANIMATION_WALKANIMATION_H

#include "DisplayObject.h"

DisplayObject *WalkAnimationCreate();

void WalkAnimationGotoAndPlay(struct DisplayObject *anim, int frameIndex);

void WalkAnimationGotoAndStop(DisplayObject *anim, int frameIndex);

SDL_bool WalkAnimationIsWalking(struct DisplayObject *anim);

void WalkAnimationWalkRight(struct DisplayObject *anim);

void WalkAnimationWalkLeft(struct DisplayObject *anim);

void WalAnimationStop(struct DisplayObject *anim);

void WalkAnimationDestroy(struct DisplayObject *self);

#endif //FRAMEDANIMATION_WALKANIMATION_H
