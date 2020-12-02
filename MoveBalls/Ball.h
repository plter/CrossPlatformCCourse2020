//
// Created by yunp on 12/1/20.
//

#ifndef DRAWBALLS_BALL_H
#define DRAWBALLS_BALL_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_FRect dest;
    double angle;
    double rotateSpeed;
    float speedX, speedY;
} Ball;

Ball *Ball_Create(float x, float y, double rotateSpeed, float speedX, float speedY);

void Ball_Draw(Ball *self, SDL_Renderer *renderer);

void Ball_Destroy(Ball *);

#endif //DRAWBALLS_BALL_H
