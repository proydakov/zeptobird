#pragma once

#include <memory>
#include <platform/isound.h>

class qt5_sound final : public isound
{
public:
    qt5_sound();
    ~qt5_sound() override;

    void play_music(const std::string& music) override;
    void stop_music() override;

    void play_sound(const std::string& sound) override;

private:
    struct d;
    std::unique_ptr<d> m_d;
};
