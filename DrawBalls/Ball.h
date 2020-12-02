//
// Created by yunp on 12/1/20.
//

#ifndef DRAWBALLS_BALL_H
#define DRAWBALLS_BALL_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect dest;
    double angle;
    double rotateSpeed;
} Ball;

Ball *Ball_Create(int x, int y, double rotateSpeed);

void Ball_Draw(Ball *self, SDL_Renderer *renderer);

void Ball_Destroy(Ball *);

#endif //DRAWBALLS_BALL_H
