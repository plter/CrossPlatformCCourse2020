#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 600
#define HEIGHT 500
#define FRAMERATE 60


struct SDL_Surface *img;

void draw(SDL_Surface *screen, SDL_Window *win) {

    SDL_Rect src = {0, 0, img->w, img->h};
    SDL_BlitSurface(img, &src, screen, &src);

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

    img = SDL_LoadBMP("cat.bmp");
    struct SDL_Surface *screen = SDL_GetWindowSurface(win);

    event_loop(screen, win);
    SDL_FreeSurface(img);
    SDL_DestroyWindow(win);
    return 0;
}
