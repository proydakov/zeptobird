#pragma once

#include <platform/isound.h>

class fake_sound final : public isound
{
public:
    fake_sound();
    ~fake_sound() override;

    void play_music(const std::string& music) override;
    void stop_music() override;

    void play_sound(const std::string& sound) override;
};
