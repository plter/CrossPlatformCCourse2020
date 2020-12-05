//
// Created by yunp on 12/4/20.
//

#ifndef CUSTOMCURSOR_CURSOR_H
#define CUSTOMCURSOR_CURSOR_H

#include <SDL2/SDL.h>
#include "DisplayObject.h"

DisplayObject *EyeBallCreate(float x, float y);

void EyeballDestroy(struct DisplayObject *self);


#endif //CUSTOMCURSOR_CURSOR_H
