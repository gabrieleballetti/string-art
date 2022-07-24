#pragma once

#include <vector>
#include "StringArtImage.h"
#include "Point2D.h"

class StringArtist
{
public:
    StringArtist(const Image& image, int numPins);
    ~StringArtist(){};
    void windString();
    bool findNextPin(const size_t currentPinId, size_t& bestPinId) const;
    float lineScore(const size_t currentPinId, const size_t nextPinId, unsigned int& pixelChanged) const;
    void drawLine(StringArtImage& image, const size_t currentPinId, const size_t nextPinId);
    void saveImage(std::FILE* outputFile);
private:
    const Image* m_imagePtr;
    StringArtImage m_canvas;
    StringArtImage m_draft;
    size_t m_numPins;
};
