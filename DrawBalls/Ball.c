//
// Created by yunp on 12/1/20.
//

#include "Ball.h"
#include "Resource.h"

Ball *Ball_Create(int x, int y, double rotateSpeed) {
    Ball *b = malloc(sizeof(Ball));
    b->dest.x = x;
    b->dest.y = y;
    b->dest.w = 30;
    b->dest.h = 30;
    b->angle = 0;
    b->rotateSpeed = rotateSpeed;
    return b;
}

void Ball_Draw(Ball *self, SDL_Renderer *renderer) {
    self->angle += self->rotateSpeed;

    SDL_RenderCopyEx(
            renderer,
            Resource_GetBallTexture(),
            NULL,
            &(self->dest),
            self->angle,
            NULL, SDL_FLIP_NONE
    );
}

void Ball_Destroy(Ball *ball) {
    free(ball);
}