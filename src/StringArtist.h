#pragma once

#include <vector>
#include "StringArtImage.h"
#include "Point2D.h"

enum class StringArtStyle
{
    BLACK_ON_WHITE = 0,
    FULL_COLOR = 1,
};

class StringArtist
{
public:
    StringArtist(const StringArtStyle stringArtStyle, const Image& image, unsigned int numPins, float draftOpacity, float threshold, unsigned int skippedNeighbors, unsigned int scaleFactor);
    ~StringArtist(){};
    void windString();
    bool findNextPin(const size_t currentPinId, size_t& bestPinId) const;
    float lineScore(const size_t currentPinId, const size_t nextPinId, unsigned int& pixelChanged) const;
    void drawLine(StringArtImage& image, const size_t currentPinId, const size_t nextPinId, const float opacity=1.0f);
    void saveImage(std::FILE* outputFile);
private:
    const StringArtStyle m_stringArtStyle;
    const Image* m_imagePtr;
    StringArtImage m_canvas;
    StringArtImage m_draft;
    std::vector<std::vector<bool>> m_adjacency;
    size_t m_numPins;
    float m_draftOpacity;
    float m_threshold;
    unsigned int m_skippedNeighbors;
    unsigned int m_scaleFactor;
    unsigned int m_iteration;
};
