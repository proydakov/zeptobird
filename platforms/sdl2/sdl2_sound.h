#pragma once

#include <memory>
#include <platform/isound.h>

struct Mix_Chunk;

class sdl2_sound final : public isound
{
public:
    sdl2_sound();
    ~sdl2_sound() override;

    void play_music(const std::string& music) override;
    void stop_music() override;

    void play_sound(const std::string& sound) override;

private:
    using sound_t = std::unique_ptr<Mix_Chunk, void(*)(Mix_Chunk*)>;
    sound_t m_music;
    sound_t m_sound;
};
