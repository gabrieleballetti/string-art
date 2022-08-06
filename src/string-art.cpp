#include <string>
#include "Image.h"
#include "StringArtist.h"

int main(int argc, char *argv[])
{
    if (argc != 8)
    {
        std::fprintf(stderr, "Usage: string_art input.pgm num_pins opacity threshold skipped_neighbors scale_factor output.pgm\n");
        return 0;
    }
    
    char buffer[1024];
    std::FILE* imageFile = std::fopen(argv[1], "rb");
    int magicNumber, imageSize, height, depth;

    // get type
    if (std::fgets(buffer, sizeof(buffer), imageFile))
    {
        std::fprintf(stderr, buffer);
        if (std::sscanf(buffer, "P%d", &magicNumber) != 1)
        {
            std::fprintf(stderr, "Error while parsing image type.\n");
            return 1;
        }
    }
    if (magicNumber != 5 && magicNumber != 6)
    {
        std::fprintf(stderr, "The image is not a portable graymap format (.pgm) nor a portable pixmap format (.ppm).\n");
        return 1;
    }

    // skip comment
    while (std::fgets(buffer, sizeof(buffer), imageFile))
    {
        std::fprintf(stderr, buffer);
        if (*buffer != '#')
            break;
    }

    // get size (no need to fgets)
    if (std::sscanf(buffer, "%d%d%d", &imageSize, &height) != 2)
    {
        std::fprintf(stderr, "Error while parsing image size.\n");
        return 1;
    }
    if (imageSize != height)
    {
        std::fprintf(stderr, "The image is not square.\n");
        return 1;
    }

    // get depth
    if (std::fgets(buffer, sizeof(buffer), imageFile))
    {
        std::fprintf(stderr, buffer);
        if (std::sscanf(buffer, "%d", &depth) != 1)
        {
            std::fprintf(stderr, "Error while parsing image depth.\n");
            return 1;
        }
    }
    if (depth != 255)
    {
        std::fprintf(stderr, "The image has not 255 colors.\n");
        return 1;
    }

    // parse arguments
    Image image = Image(imageFile, imageSize);
    int numPins = std::strtol(argv[2], nullptr, 10);
    float draftOpacity = std::strtof(argv[3], nullptr);
    float threshold = std::strtof(argv[4], nullptr);
    int skippedNeighbors = std::strtol(argv[5], nullptr, 10);
    int scaleFactor = std::strtol(argv[6], nullptr, 10);
    std::FILE* outputFile = std::fopen(argv[7], "wb");
    StringArtStyle style = magicNumber == 6 ? StringArtStyle::FULL_COLOR : StringArtStyle::BLACK_ON_WHITE; 

    // actual art being done
    StringArtist stringArtist = StringArtist(style, image, numPins, draftOpacity, threshold, skippedNeighbors, scaleFactor);
    stringArtist.windString();

    // save final result
    stringArtist.saveImage(outputFile);
}
