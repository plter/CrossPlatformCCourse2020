//
// Created by yunp on 12/5/20.
//

#ifndef RENDERTEXT_TEXT_H
#define RENDERTEXT_TEXT_H

#include "DisplayObject.h"

DisplayObject *TextCreate(char *font, char *value, int ptsize, uint32_t color);

void TextSet(struct DisplayObject *textDisplayObject, char *value);

void TextDestroy(struct DisplayObject *self);

#endif //RENDERTEXT_TEXT_H
