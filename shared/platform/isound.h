#pragma once

#include <string>

class isound
{
public:
    virtual ~isound();
    
    virtual void play_music(const std::string& music) = 0;
    virtual void stop_music() = 0;

    virtual void play_sound(const std::string& music) = 0;
};
