#include <string>
#include "Image.h"
#include "StringArtist.h"

int main(int argc, char *argv[])
{
    // parse arguments
    if (argc != 5)
    {
        std::fprintf(stderr, "Usage: string_art input.pgm num_pins skipped_neighbors output.pgm\n");
        return 0;
    }
    std::FILE* imageFile = std::fopen(argv[1], "rb");
    int imageSize, height, depth;
    if (std::fscanf(imageFile, "P5 %d%d%d%*c", &imageSize, &height, &depth) != 3 || imageSize != height || depth != 255)
    {
        std::fprintf(stderr, "Error while parsing image, should be square binary PGM image (without comments).\n");
        return 1;
    }
    Image image = Image(imageFile, imageSize);
    int numPins = std::strtol(argv[2], nullptr, 10);
    int skippedNeighbors = std::strtol(argv[3], nullptr, 10);
    std::FILE* outputFile = std::fopen(argv[4], "wb");

    // actual art being done
    StringArtist stringArtist = StringArtist(image, numPins, skippedNeighbors);
    stringArtist.windString();

    // save final result
    stringArtist.saveImage(outputFile);
}
