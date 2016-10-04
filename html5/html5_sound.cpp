#include <emscripten.h>

#include "html5_sound.h"

html5_sound::~html5_sound()
{
}

void html5_sound::play_music(const std::string& music)
{
    stop_music();
    EM_ASM_({
        var music_name = Pointer_stringify($0) + ".mp3";
        window.zmusic = new Audio( music_name );
        window.zmusic.loop = true;
        window.zmusic.play();
    }, music.c_str());
}

void html5_sound::stop_music()
{
    EM_ASM(
        if(window.zmusic) {
            console.log("stop music");
            window.zmusic.pause();
            window.zmusic = null;
        }
    );
}

void html5_sound::play_sound(const std::string& sound)
{
    EM_ASM_({
        var sound_name = Pointer_stringify($0) + ".mp3";
        var sound = new Audio( sound_name );
        sound.loop = false;
        sound.play();
    }, sound.c_str());
}
