#!/bin/bash

#echo $*

#echo "Display: $DISPLAY" > ~/env
#echo "XScreenSaver window: $XSCREENSAVER_WINDOW" >> ~/env

#cd "$HOME/screensaver"
cd $(dirname "${BASH_SOURCE[0]}" )

while true; do
    text=$(shuf -n 1 sayings.txt)
    javaprogram=$(java RandomProgram <<< $text)
    #echo "$javaprogram" >> test
    ./printprogram <<< "$javaprogram" >> ~/scrsvr.log
    wait
done
