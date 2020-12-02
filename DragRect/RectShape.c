//
// Created by yunp on 12/2/20.
//

#include "RectShape.h"

RectShape *RectShape_Create(float x, float y, float w, float h, uint32_t color) {
    RectShape *self = malloc(sizeof(RectShape));
    self->color = color;
    self->dest.x = x;
    self->dest.y = y;
    self->dest.w = w;
    self->dest.h = h;
    self->_dragEnabled = 0;
    self->pre = NULL;
    self->next = NULL;
    return self;
}

void RectShape_Draw(RectShape *self, SDL_Renderer *renderer) {
    // 0xffff0000 ARGB
    SDL_SetRenderDrawColor(
            renderer,
            (self->color & 0x00ff0000) >> 16,
            (self->color & 0x0000ff00) >> 8,
            self->color & 0x000000ff,
            (self->color & 0xff000000) >> 24
    );
    SDL_RenderFillRectF(renderer, &(self->dest));
}

SDL_bool RectShape_OnMouseEvent(RectShape *self, SDL_Event *event) {
    SDL_Point currentMousePoint = {event->button.x, event->button.y};
    SDL_Rect destRect = {(int) self->dest.x, (int) self->dest.y, (int) self->dest.w, (int) self->dest.h};

    switch (event->type) {
        case SDL_MOUSEMOTION:
            if (self->_dragEnabled) {
                self->dest.x = self->_dragStartPoint.x + event->motion.x - self->_dragStartMousePoint.x;
                self->dest.y = self->_dragStartPoint.y + event->motion.y - self->_dragStartMousePoint.y;
                return SDL_TRUE;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (SDL_PointInRect(&currentMousePoint, &destRect)) {
                self->_dragStartPoint.x = self->dest.x;
                self->_dragStartPoint.y = self->dest.y;
                self->_dragStartMousePoint.x = event->button.x;
                self->_dragStartMousePoint.y = event->button.y;
                self->_dragEnabled = 1;
                return SDL_TRUE;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (SDL_PointInRect(&currentMousePoint, &destRect)) {
                self->_dragEnabled = 0;
                return SDL_TRUE;
            }
            break;
    }

    return SDL_FALSE;
}

void RectShape_Destroy(RectShape *self) {
    free(self);
}