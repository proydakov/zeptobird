#pragma once

#include <platform/isound.h>

class android_app;

class android_sound final : public isound
{
public:
    android_sound(android_app* app);
    ~android_sound() override;

    void play_music(const std::string& music) override;
    void stop_music() override;

    void play_sound(const std::string& sound) override;

private:
    android_app* m_app;
};
