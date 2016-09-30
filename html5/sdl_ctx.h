#pragma once

#include <string>
#include <iostream>
#include <SDL/SDL.h>

class sdl_ctx
{
public:
    sdl_ctx(int width, int height, int frameRate, int flags);
    ~sdl_ctx();

    void setCaption (std::string title);
    void setEventListener  (void (*listener) (SDL_Event&));
    void setRenderCallback (void (*callback) (SDL_Surface*));
    void setUpdateCallback (void (*callback) (int));
    void step();

private:
    void (*eventListener) (SDL_Event&);
    void (*renderCallback) (SDL_Surface*);
    void (*updateCallback) (int);

    void handleEvent(SDL_Event &event);
    void render();
    void update(int deltaTime);

    SDL_Surface* screen;

    bool active;
    bool paused;
    int ticksPerFrame;
    int previousTime;
};
