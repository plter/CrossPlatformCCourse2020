//
// Created by yunp on 12/1/20.
//

#include "Ball.h"
#include "Resource.h"
#include "Config.h"

Ball *Ball_Create(float x, float y, double rotateSpeed, float speedX, float speedY) {
    Ball *b = malloc(sizeof(Ball));
    b->dest.x = x;
    b->dest.y = y;
    b->dest.w = 30;
    b->dest.h = 30;
    b->angle = 0;
    b->rotateSpeed = rotateSpeed;
    b->speedX = speedX;
    b->speedY = speedY;
    return b;
}

void Ball_Draw(Ball *self, SDL_Renderer *renderer) {
    self->angle += self->rotateSpeed;
    self->dest.x += self->speedX;
    self->dest.y += self->speedY;

    if ((self->dest.x > WINDOW_WIDTH - self->dest.w && self->speedX > 0) ||
        (self->dest.x < 0 && self->speedX < 0)) {
        self->speedX *= -1;
    }
    if ((self->dest.y > WINDOW_HEIGHT - self->dest.h && self->speedY > 0) ||
        (self->dest.y < 0 && self->speedY < 0)) {
        self->speedY *= -1;
    }

    SDL_RenderCopyExF(
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