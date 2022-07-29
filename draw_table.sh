#! /bin/sh

numPins=256

# 2. Collect string art images

for op in $(seq 0.3 -0.05 0.1); do \
    for t in $(seq -w 245 5 265); do \
        ../bin/string-art.exe ../cat.pgm ${numPins} ${op} ${t} 32 ${op}_${t}.pgm
        "../../../../../../Program Files/ImageMagick-7.1.0-Q16-HDRI/magick.exe" convert -resize 256x256 ${op}_${t}.pgm ${op}_${t}.png
    done
done

"../../../../../../Program Files/ImageMagick-7.1.0-Q16-HDRI/magick.exe" montage \
    -label "o=0.30 t=245"  0.30_245.png \
    -label "o=0.30 t=250"  0.30_250.png \
    -label "o=0.30 t=255"  0.30_255.png \
    -label "o=0.30 t=260"  0.30_260.png \
    -label "o=0.30 t=265"  0.30_265.png \
    -label "o=0.25 t=245"  0.25_245.png \
    -label "o=0.25 t=250"  0.25_250.png \
    -label "o=0.25 t=255"  0.25_255.png \
    -label "o=0.25 t=260"  0.25_260.png \
    -label "o=0.25 t=265"  0.25_265.png \
    -label "o=0.20 t=245"  0.20_245.png \
    -label "o=0.20 t=250"  0.20_250.png \
    -label "o=0.20 t=255"  0.20_255.png \
    -label "o=0.20 t=260"  0.20_260.png \
    -label "o=0.20 t=265"  0.20_265.png \
    -label "o=0.15 t=245"  0.15_245.png \
    -label "o=0.15 t=250"  0.15_250.png \
    -label "o=0.15 t=255"  0.15_255.png \
    -label "o=0.15 t=260"  0.15_260.png \
    -label "o=0.15 t=265"  0.15_265.png \
    -label "o=0.10 t=245"  0.10_245.png \
    -label "o=0.10 t=250"  0.10_250.png \
    -label "o=0.10 t=255"  0.10_255.png \
    -label "o=0.10 t=260"  0.10_260.png \
    -label "o=0.10 t=265"  0.10_265.png \
    -tile 5x5 -geometry 128x128+4+4 montage4.png
