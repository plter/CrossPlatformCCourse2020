#include <stdio.h>
#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#define WIDTH 400
#define HEIGHT 300
#define FRAMERATE 60

SDL_Renderer *renderer;
SDL_Window *window;

void draw() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect r = {0, 0, 100, 100};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &r);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    struct SDL_Rect r1 = {50, 50, 100, 100};
    SDL_RenderFillRect(renderer, &r1);
    SDL_RenderPresent(renderer);
}

void event_loop() {
    while (1) {
        uint32_t begin = SDL_GetTicks();
        draw();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
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


void em_loop() {
    draw();
}

int main(int argc, char *argv[]) {
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

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(em_loop,0,1);
#else // __EMSCRIPTEN__
    event_loop();
#endif
   
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
