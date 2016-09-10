#pragma once

#include <platform/isound.h>

#import <AVFoundation/AVFoundation.h>

class ios_sound : public isound
{
public:
    ios_sound();
    ~ios_sound() override;

    void play_music(const std::string& music) override;
    void stop_music() override;
    void play_sound(const std::string& sound) override;

private:
    AVAudioPlayer* m_musicAudioPlayer;
    AVAudioPlayer* m_soundAudioPlayer;
};
