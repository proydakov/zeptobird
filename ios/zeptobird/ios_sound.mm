#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

#include "ios_sound.h"

ios_sound::ios_sound() :
    m_musicAudioPlayer(nullptr),
    m_soundAudioPlayer(nullptr)
{
}

ios_sound::~ios_sound()
{
}

void ios_sound::play_music(const std::string& music)
{
    NSString *nsmusic = [NSString stringWithCString:music.c_str() encoding:[NSString defaultCStringEncoding]];
    NSString *soundFilePath = [[NSBundle mainBundle] pathForResource:nsmusic ofType: @"mp3"];
    NSURL *fileURL = [[NSURL alloc] initFileURLWithPath:soundFilePath];
    m_musicAudioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:fileURL error:nil];
    m_musicAudioPlayer.numberOfLoops = -1; //infinite loop
    [m_musicAudioPlayer play];
}

void ios_sound::stop_music()
{
    if(m_musicAudioPlayer) {
        [m_musicAudioPlayer stop];
    }
}

void ios_sound::play_sound(const std::string& sound)
{
    NSString *nsmusic = [NSString stringWithCString:sound.c_str() encoding:[NSString defaultCStringEncoding]];
    NSString *soundFilePath = [[NSBundle mainBundle] pathForResource:nsmusic ofType: @"mp3"];
    NSURL *fileURL = [[NSURL alloc] initFileURLWithPath:soundFilePath];
    m_soundAudioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:fileURL error:nil];
    m_soundAudioPlayer.numberOfLoops = 0; //just once
    [m_soundAudioPlayer play];
}
