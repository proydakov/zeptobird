#!/usr/bin/env python3

import os
import sys
import shutil

if len(sys.argv) < 2:
    print("usage", sys.argv[0], "[install path]")
    sys.exit(1)

files = []

htmls  = ["html5/index.html"]
sounds = os.listdir("shared/resources/music")
bins   = ["build-html5/html5/zeptobird.data",
          "build-html5/html5/zeptobird.js",
          "build-html5/html5/zeptobird.js.mem"]

for sound in sounds:
    files.append( "shared/resources/music/" + sound )

files += htmls
files += bins

for file in files:
    src = file
    dst = sys.argv[1] + "/" + os.path.basename(file)
    print("copy:", src, " - ", dst)
    shutil.copyfile(src, dst)
