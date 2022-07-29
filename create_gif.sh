#! /bin/sh

filename=${1}
numPins=256
maxSkippedNeighbors=128

# 1. Convert to pmg
"./../../../../../../Program Files/ImageMagick-7.1.0-Q16-HDRI/magick.exe" convert -resize 512x512 -caption '' ${filename} img.pgm

# 2. Collect string art images
for i in $(seq -w 1 ${maxSkippedNeighbors}); do \
    ../bin/string-art.exe img.pgm ${numPins} ${i} $img_${i}.pgm
done

# 2. Convert to png
for i in $(seq -w 1 ${maxSkippedNeighbors}); do \
    "./../../../../../../Program Files/ImageMagick-7.1.0-Q16-HDRI/magick.exe" convert img_${i}.pgm img_${i}.png
done

# ... and compose them into a gif with magick
"./../../../../../../Program Files/ImageMagick-7.1.0-Q16-HDRI/magick.exe" convert -loop 0 \
$(for i in $(seq -w ${maxSkippedNeighbors} -1 1); do echo img_${i}.png; done) \
animated.gif
