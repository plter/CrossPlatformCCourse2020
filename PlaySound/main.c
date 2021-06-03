#include <stdio.h>
#include <SDL2/SDL.h>

typedef struct {
    Uint8 *sound;
    Uint32 soundLen;
    Uint32 soundPos;
    int completed;
} SoundInfo;


void SDLCALL audioCallback(void *userdata, Uint8 *stream, int len) {
    SoundInfo *si = userdata;

    Uint32 remaining = si->soundLen - si->soundPos;
    if (remaining > len) {
        SDL_memcpy(stream, si->sound + si->soundPos, len);
        si->soundPos += len;
    } else {
        SDL_memcpy(stream, si->sound + si->soundPos, remaining);
        si->soundPos = 0;
        si->completed = SDL_TRUE;
    }
}


int main() {
    if (SDL_Init(SDL_INIT_AUDIO)) {
        SDL_Log("%s", SDL_GetError());
        return 1;
    }

    SDL_AudioSpec spec;
    Uint8 *sound;
    Uint32 soundLen;
    if (SDL_LoadWAV("sound.wav", &spec, &sound, &soundLen) == NULL) {
        SDL_Log("%s", SDL_GetError());
        return 1;
    }

    spec.callback = audioCallback;

    SoundInfo si;
    si.sound = sound;
    si.soundLen = soundLen;
    si.soundPos = 0;
    si.completed = SDL_FALSE;
    spec.userdata = &si;

    SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, SDL_FALSE, &spec, NULL, 0);
    if (!device) {
        SDL_Log("%s", SDL_GetError());
        SDL_FreeWAV(sound);
        return 1;
    }

    SDL_PauseAudioDevice(device, SDL_FALSE);

    while (1) {
        if (si.completed) {
            break;
        }
        SDL_Delay(100);
    }
    SDL_CloseAudioDevice(device);
    SDL_FreeWAV(sound);
    return 0;
}