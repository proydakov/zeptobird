# ZeptoBird Game

<span style="display: inline-block;">

[![Travis CI Status](https://travis-ci.org/proydakov/zeptobird.svg?branch=master)](https://travis-ci.org/proydakov/zeptobird)
[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/proydakov/zeptobird/blob/master/LICENSE)
</span>

ZeptoBird is yet another flappy bird clone.

Platforms
---------

ZeptoBird is written on **C++11** and **OPENGLES 2.0**. Release for *IOS* and *Android*.

iOS
---

Open **platforms/ios/zeptobird.xcodeproj** in XCode

Android
-------

Open **platforms/android/settings.gradle** in Android Studio. (note RC2.2 support C++ debug)

Qt5 (linux, windows, macosx)
----------------------------

    mkdir build
    cd build
    cmake ..
    make -j

HTML5
-----

Install **emscripten sdk**. https://kripken.github.io/emscripten-site/docs/getting_started/downloads.html

    mkdir build-html5
    cd build-html5
    cmake -DCMAKE_TOOLCHAIN_FILE=path/to/emsdk_portable/emscripten/master/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=Release ..
    make -j

**Live Demo**: https://proydakov.github.io

Game Play
---------

![welcome](screenshot/welcome.jpg)
![about](screenshot/about.jpg)
![play](screenshot/play.jpg)
![game_over](screenshot/game_over.jpg)
![record](screenshot/record.jpg)

License
-------

Copyright (c) 2016 Evgeny Proydakov

[LICENSE](LICENSE)

[0]: https://github.com/proydakov/zeptobird
