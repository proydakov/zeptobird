#include "sdl2_sound.h"
#include "generated_resource.h"

#include <SDL2/SDL_mixer.h>

#include <iostream>

namespace {
    std::string build_path(const std::string& name)
    {
        const char music_folder[] = "/music/";
        const char mp3_ext[] = ".ogg";

        std::string sstream;
        sstream.reserve(std::size(ABS_RES_PATH) + std::size(music_folder) + name.size() + std::size(mp3_ext));
        sstream.append(ABS_RES_PATH);
        sstream.append(music_folder);
        sstream.append(name);
        sstream.append(mp3_ext);
        return sstream;
    }
    template<typename T>
    void play(T& sound, int channel, int loops)
    {
        if (sound)
        {
            Mix_VolumeChunk(sound.get(), 100);
            Mix_PlayChannel(channel, sound.get(), loops);
        }
        else
        {
            std::cerr << "Can't load sound. " << Mix_GetError() << std::endl;
        }
    }
}

sdl2_sound::sdl2_sound() : m_music(nullptr, Mix_FreeChunk), m_sound(nullptr, Mix_FreeChunk)
{
    int i, count = SDL_GetNumAudioDevices(0);

    for (i = 0; i < count; ++i)
    {
        std::cout << "Audio device " << i << ": " << SDL_GetAudioDeviceName(i, 0) << std::endl;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        std::cerr << "SDL2_mixer could not be initialized! SDL_Error: " << Mix_GetError() << std::endl;
    }
}

sdl2_sound::~sdl2_sound()
{
    Mix_CloseAudio();
}

void sdl2_sound::play_music(const std::string& music)
{
    auto path = build_path(music);
    m_music = sound_t(Mix_LoadWAV(path.c_str()), Mix_FreeChunk);
    play(m_music, 0, -1);
}

void sdl2_sound::stop_music()
{
    Mix_HaltChannel(0);
}

void sdl2_sound::play_sound(const std::string& sound)
{
    auto path = build_path(sound);
    m_sound = sound_t(Mix_LoadWAV(path.c_str()), Mix_FreeChunk);
    play(m_sound, 1, 0);
}
