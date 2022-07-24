
#include "Image.h"
#include "StringArtist.h"

int main(int argc, char *argv[])
{
    // parse output
    if (argc != 5)
    {
        std::fprintf(stderr, "Usage: string_art input.pgm block_size num_pins output.pgm\n");
        return 0;
    }
    std::FILE* imageFile = std::fopen(argv[1], "rb");
    int imageSize, height, depth;
    if (std::fscanf(imageFile, "P5 %d%d%d%*c", &imageSize, &height, &depth) != 3 || imageSize != height || depth != 255)
    {
        std::fprintf(stderr, "Error while parsing image, should be square binary PGM image (without comments).\n");
        return 1;
    }
    //int blockSize = std::strtol(argv[2], nullptr, 10);
    int numPins = std::strtol(argv[3], nullptr, 10);
    std::FILE* outputFile = std::fopen(argv[4], "wb");

    // actual art being done
    Image image = Image(imageFile, imageSize);
    StringArtist stringArtist = StringArtist(image, numPins);
    stringArtist.windString();
    stringArtist.saveImage(outputFile);
}
