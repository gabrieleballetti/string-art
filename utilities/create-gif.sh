#! /bin/sh

# Example of a bash script to create a gif from multiple output of the main string-art script

# 1. Convert to pgm
magick convert input.png -resize 512x512 image.pgm

# 2. Create and convert string art images, then delete it
for numPins in $(seq -w 1 4 256); do \
    bin/string-art image.pgm ${numPins} 0.15 255 32 8 temp.pgm
    magick convert -resize 512x512 temp.pgm out_${s}.png
    rm temp/pgm
done

# 3. Compose output pngs into a gif with magick
magick convert -loop 0 \
$(for numPins in $(seq -w 50 50 200); do echo out_${s}.png; done) \
output.gif
