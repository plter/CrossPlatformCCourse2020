#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 400
#define HEIGHT 300

void event_loop() {
    while (1) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
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

    SDL_Surface *screen = SDL_GetWindowSurface(win);

    SDL_Rect r = {0, 0, WIDTH, HEIGHT};
    SDL_FillRect(screen, &r, 0xffffffff);// ARGB
    struct SDL_Rect redRect = {0, 0, 100, 100};
    SDL_FillRect(screen, &redRect, 0xffff0000);
    SDL_UpdateWindowSurface(win);

    event_loop();
    SDL_DestroyWindow(win);
    return 0;
}
