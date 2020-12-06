//
// Created by yunp on 12/5/20.
//

#include "Text.h"
#include <SDL2/SDL_ttf.h>

typedef struct {
    TTF_Font *font;
    SDL_Surface *textSurface;
    char *fontFile;
    char *value;
    int ptsize;
    uint32_t color;
} TextData;

static void TextOnDraw(struct DisplayObject *displayObject, SDL_Renderer *renderer) {
    TextData *data = displayObject->subClassData;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, data->textSurface);

    SDL_RenderCopyF(renderer, texture, NULL, displayObject->dest);

    SDL_DestroyTexture(texture);
}

DisplayObject *TextCreate(char *fontFile, char *value, int ptsize, uint32_t color) {
    TTF_Font *font = TTF_OpenFont(fontFile, ptsize);
    if (font == NULL) {
        SDL_Log("Can not open font, %s", TTF_GetError());
        return NULL;
    }

    TextData *data = malloc(sizeof(TextData));
    data->font = font;
    data->textSurface = NULL;
    data->fontFile = fontFile;
    data->color = color;
    data->value = value;
    data->ptsize = ptsize;

    struct DisplayObject *obj = DisplayObjectCreate(
            0, 0, 0, 0,
            &TextOnDraw, NULL
    );

    obj->subClassData = data;

    TextSet(obj, value);
    return obj;
}

void TextSet(struct DisplayObject *textDisplayObject, char *value) {
    TextData *data = textDisplayObject->subClassData;
    data->value = value;

    SDL_Color textColor = {
            (data->color & 0x00ff0000) >> 16,
            (data->color & 0x0000ff00) >> 8,
            (data->color & 0x000000ff),
            (data->color & 0xff000000) >> 24
    };
    if (data->textSurface != NULL) {
        SDL_FreeSurface(data->textSurface);
    }
    data->textSurface = TTF_RenderUTF8_Blended(data->font, data->value, textColor);
    textDisplayObject->dest->w = (float) data->textSurface->w;
    textDisplayObject->dest->h = (float) data->textSurface->h;
}

void TextDestroy(struct DisplayObject *self) {
    TextData *data = self->subClassData;
    SDL_FreeSurface(data->textSurface);
    TTF_CloseFont(data->font);
    DisplayObjectDestroy(self);
}