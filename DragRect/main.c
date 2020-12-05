#include <stdio.h>
#include <SDL2/SDL.h>
#include "RectShape.h"

#define WIDTH 400
#define HEIGHT 300
#define FRAMERATE 60

#define RECTSHAPE_COUNT 3

SDL_Renderer *renderer;
SDL_Window *window;
RectShape *first;
RectShape *last;

void draw() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    RectShape *item = first;
    while (item != NULL) {
        RectShape_Draw(item, renderer);
        item = item->next;
    }

    SDL_RenderPresent(renderer);
}

void addRectShape(struct RectShape *rectShape) {
    if (last != NULL) {
        last->next = rectShape;
        rectShape->pre = last;
        last = rectShape;
    } else {
        last = rectShape;
        first = rectShape;
    }
}

void event_loop() {
    RectShape *item;

    while (1) {
        uint32_t begin = SDL_GetTicks();
        draw();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    item = last;
                    while (item != NULL) {
                        if (RectShape_OnMouseEvent(item, &event)) {
                            if (item != last) {
                                if (item->pre != NULL) {
                                    item->pre->next = item->next;
                                } else {
                                    first = item->next;
                                }
                                item->next->pre = item->pre;
                                item->next = NULL;
                                addRectShape(item);
                            }
                            break;
                        }
                        item = item->pre;
                    }
                    break;
                case SDL_QUIT:
                    return;
            }
        }
        long current = SDL_GetTicks();
        long cost = current - begin;
        long frame = 1000 / FRAMERATE;
        long delay = frame - cost;

        if (delay > 0) {
            SDL_Delay(delay);
        }
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Can not init video, %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
            "Hello World",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT,
            SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        SDL_Log("Can not create window, %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("Can not create renderer, %s", SDL_GetError());
        return 1;
    }

    first = NULL;
    last = NULL;
    addRectShape(RectShape_Create(0, 0, 80, 60, 0xffff0000));
    addRectShape(RectShape_Create(100, 0, 80, 60, 0xffffff00));
    addRectShape(RectShape_Create(200, 0, 80, 60, 0xff0000ff));
    event_loop();

    RectShape *item = first;
    while (item != NULL) {
        RectShape *current = item;
        item = item->next;
        RectShape_Destroy(current);
    }
    first = NULL;
    last = NULL;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
