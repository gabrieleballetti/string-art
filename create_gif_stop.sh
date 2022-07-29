#! /bin/sh

numPins=256

# 2. Collect string art images
#for s in $(seq -w 101 200); do \
#    ../bin/string-art.exe ../ada.pgm ${numPins} 0.15 255 32 a${s}.pgm ${s}
#    "../../../../../../Program Files/ImageMagick-7.1.0-Q16-HDRI/magick.exe" convert -resize 512x512 a${s}.pgm a${s}.png
#done

# ... and compose them into a gif with magick
"./../../../../../../Program Files/ImageMagick-7.1.0-Q16-HDRI/magick.exe" convert -loop 0 \
a001.png $(for s in $(seq -w 50 50 200); do echo a${s}.png; done) $(for s in $(seq -w 250 50 6600); do echo a0${s}.png; done) \
animated4.gif
