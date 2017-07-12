#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "linux_sound.h"
#include "generated_resource.h"

#include <sstream>
#include <iostream>

namespace {
    std::string build_path(const std::string& name)
    {
        std::stringstream sstream;
        sstream << ABS_RES_PATH << "/music/" << name << ".mp3";
        std::string filepath(sstream.str());
        return filepath;
    }
}

struct linux_sound::d
{
    d() :
        music(nullptr, Mix_FreeMusic),
        sound(nullptr, Mix_FreeMusic)
    {
    }

    std::unique_ptr<Mix_Music, void (*)(Mix_Music*)> music;
    std::unique_ptr<Mix_Music, void (*)(Mix_Music*)> sound;
};

linux_sound::linux_sound() :
    m_d(new d())
{
    int result = 0;
    int flags = MIX_INIT_MP3;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        throw std::runtime_error("Failed to init SDL");
    }

    if (flags != (result = Mix_Init(flags))) {
        std::stringstream sstream;
        sstream << "Could not initialize mixer (result: " << result
                << " ). Mix_Init: " << Mix_GetError() << std::endl;
        throw std::runtime_error(sstream.str());
    }

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
}

linux_sound::~linux_sound()
{
    m_d.reset();

    SDL_Quit();
}

void linux_sound::play_music(const std::string& music)
{
    const std::string filepath = build_path(music);
    m_d->music.reset(Mix_LoadMUS(filepath.c_str()));
    Mix_PlayMusic(m_d->music.get(), -1);
}

void linux_sound::stop_music()
{
    Mix_HaltMusic();
}

void linux_sound::play_sound(const std::string& sound)
{
    // temp hack
    if("game-over" == sound) {
        const std::string filepath = build_path(sound);
        m_d->music.reset(Mix_LoadMUS(filepath.c_str()));
        Mix_PlayMusic(m_d->music.get(), 1);
    }
}
