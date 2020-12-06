#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Text.h"

#define WIDTH 400
#define HEIGHT 300
#define FRAMERATE 60


SDL_Renderer *renderer;
SDL_Window *window;
DisplayObject *text;
int clickCount = 0;

void draw() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    DisplayObjectDraw(text, renderer);

    SDL_RenderPresent(renderer);
}

void createComponents() {
    text = TextCreate("padmaa.ttf", "Hello World", 32, 0xFF000000);
}

void freeComponents() {
    TextDestroy(text);
}

void event_loop() {
    while (1) {
        uint32_t begin = SDL_GetTicks();
        draw();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONUP:
                    clickCount++;
                    char buf[16];
                    sprintf(buf, "Count: %d", clickCount);
                    TextSet(text, buf);
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
    if (TTF_Init()) {
        SDL_Log("Can not init font, %s", TTF_GetError());
        return 1;
    }

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

    createComponents();
    event_loop();
    freeComponents();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
