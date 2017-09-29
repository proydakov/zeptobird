#include "qt5_sound.h"
#include "generated_resource.h"

#include <sstream>
#include <iostream>

#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace {
    std::string build_path(const std::string& name)
    {
        std::stringstream sstream;
        sstream << ABS_RES_PATH << "/music/" << name << ".mp3";
        std::string filepath(sstream.str());
        return filepath;
    }
}

struct qt5_sound::d
{
    d()
    {
        music_player.reset(new QMediaPlayer);
        sound_player.reset(new QMediaPlayer);
        music_player->setVolume(100);
        sound_player->setVolume(100);
    }

    std::unique_ptr<QMediaPlayer> music_player;
    std::unique_ptr<QMediaPlayer> sound_player;
};

qt5_sound::qt5_sound() :
    m_d(new d())
{
}

qt5_sound::~qt5_sound()
{
}

void qt5_sound::play_music(const std::string& music)
{
    QString path(QString::fromStdString(build_path(music)));

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile(path));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    m_d->music_player->setPlaylist(playlist);
    m_d->music_player->play();
}

void qt5_sound::stop_music()
{
    m_d->music_player->stop();
}

void qt5_sound::play_sound(const std::string& sound)
{
    QString path(QString::fromStdString(build_path(sound)));
    m_d->sound_player->setMedia(QUrl::fromLocalFile(path));
    m_d->sound_player->play();
}
