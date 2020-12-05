//
// Created by yunp on 12/4/20.
//

#ifndef CUSTOMCURSOR_CURSOR_H
#define CUSTOMCURSOR_CURSOR_H

#include <SDL2/SDL.h>
#include "DisplayObject.h"

DisplayObject *CursorCreate(float x, float y, float w, float h);

void CursorDestroy(struct DisplayObject *self);


#endif //CUSTOMCURSOR_CURSOR_H
