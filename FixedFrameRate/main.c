#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 400
#define HEIGHT 300
#define FRAMERATE 60

int x = 0;

void draw(SDL_Surface *screen, SDL_Window *win) {
    x++;
    SDL_Rect r = {0, 0, WIDTH, HEIGHT};
    SDL_FillRect(screen, &r, 0xffffffff);// ARGB
    struct SDL_Rect redRect = {x, 0, 100, 100};
    SDL_FillRect(screen, &redRect, 0xffff0000);
    SDL_UpdateWindowSurface(win);
}

void event_loop(SDL_Surface *screen, SDL_Window *win) {
    while (1) {
        uint32_t begin = SDL_GetTicks();
        draw(screen, win);

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

int main() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Can not init video, %s", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow(
            "Hello World",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT,
            SDL_WINDOW_SHOWN
    );
    if (win == NULL) {
        SDL_Log("Can not create window, %s", SDL_GetError());
        return 1;
    }

    struct SDL_Surface *screen = SDL_GetWindowSurface(win);

    event_loop(screen, win);
    SDL_DestroyWindow(win);
    return 0;
}
