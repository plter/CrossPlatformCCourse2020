#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 600
#define HEIGHT 500
#define FRAMERATE 60
#define FONT_SIZE 32

TTF_Font *font;


void draw(SDL_Surface *screen, SDL_Window *win) {
    SDL_Color color = {255, 255, 255, 255};
    struct SDL_Surface *text = TTF_RenderUTF8_Blended(
            font, "https://yunp.top", color
    );
    SDL_Rect src = {0, 0, text->w, text->h};
    SDL_BlitSurface(text, &src, screen, &src);
    SDL_FreeSurface(text);
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
    if (TTF_Init()) {
        SDL_Log("Can not init ttf, %s", TTF_GetError());
        return 1;
    }

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

    font = TTF_OpenFont("padmaa.ttf", FONT_SIZE);
    if (font == NULL) {
        SDL_Log("Can not open font");
        return 1;
    }
    struct SDL_Surface *screen = SDL_GetWindowSurface(win);

    event_loop(screen, win);
    TTF_CloseFont(font);
    SDL_DestroyWindow(win);
    return 0;
}
