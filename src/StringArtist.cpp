#include "StringArtist.h"

#include <iostream>
#include "BresenhamLineIterator.h"

namespace {
    float CANVAS_LINE_OPACITY = 1.0f;
}

StringArtist::StringArtist(const StringArtStyle stringArtStyle, const Image& image, unsigned int numPins, float draftOpacity, float threshold, unsigned int skipped_neighbors, unsigned int scaleFactor) :
    m_stringArtStyle(stringArtStyle),
    m_imagePtr(&image),
    m_numPins(numPins),
    m_draftOpacity(draftOpacity),
    m_threshold(threshold),
    m_skippedNeighbors(skipped_neighbors),
    m_scaleFactor(scaleFactor),
    m_iteration(0)
{
    m_canvas = StringArtImage(m_imagePtr->size() * m_scaleFactor, m_numPins);
    m_draft = StringArtImage(m_imagePtr->size(), m_numPins);
    m_adjacency.resize(m_imagePtr->size(), std::vector<bool>(m_imagePtr->size(), false));
}

void StringArtist::windString()
{
    // Wind thread around pins until image can't be improved.
    size_t currentPinId = 0;
    std::cout << "start winding" << std::endl;
    while (true)
    {
        size_t nextPinId;
        if (!findNextPin(currentPinId, nextPinId))
            break;

        m_iteration++;
        //std::cout << m_iteration << std::endl;
        drawLine(m_draft, currentPinId, nextPinId, m_draftOpacity);
        drawLine(m_canvas, currentPinId, nextPinId, CANVAS_LINE_OPACITY);

        m_adjacency[currentPinId][nextPinId] = true;
        m_adjacency[nextPinId][currentPinId] = true;
        currentPinId = nextPinId;
    }
    std::cout << "Done after "<< m_iteration << " iterations" << std::endl;
}

bool StringArtist::findNextPin(const size_t currentPinId, size_t& bestPinId) const
{
    float bestScore = std::numeric_limits<float>::infinity();

    for (size_t nextPinId = 0; nextPinId < m_numPins; ++nextPinId)
    {
        int diff = static_cast<int>(nextPinId) - static_cast<int>(currentPinId); 
        int dist = std::min(diff % m_numPins, -diff % m_numPins);
        if (dist < m_skippedNeighbors || m_adjacency[currentPinId][nextPinId])
            continue;

        unsigned int pixelChanged;
        float score = lineScore(currentPinId, nextPinId, pixelChanged);
        
        if (pixelChanged > 0 && score < bestScore)
        {
            bestScore = score;
            bestPinId = nextPinId;
        }
    }
    return bestScore < m_threshold;
}

float StringArtist::lineScore(const size_t currentPinId, const size_t nextPinId, unsigned int& pixelChanged) const
{
    pixelChanged = 0;
    float score = 0.f;
    Point2D currentPin = m_draft.getPin(currentPinId);
    Point2D nextPin = m_draft.getPin(nextPinId);
    Point2D diff = nextPin - currentPin;
    int distance = std::max(std::abs(diff[0]), std::abs(diff[1]));

    for (const Point2D& pixel : BresenhamLineIterator(currentPin, nextPin))
    {
        score += m_imagePtr->getPixelValue(pixel) + (255 - m_draft.getPixelValue(pixel));
        ++pixelChanged;
    }
    return score / distance;
}

void StringArtist::drawLine(StringArtImage& image, const size_t currentPinId, const size_t nextPinId, const float opacity)
{
    for (const Point2D& pixel : BresenhamLineIterator(image.getPin(currentPinId), image.getPin(nextPinId)))
    {
        int value = 0;
        if (opacity < 1.0f)
        {
            value = image.getPixelValue(pixel) * (1 - opacity);
        }
        image.setPixelValue(pixel, value);
    }
}

void StringArtist::saveImage(std::FILE* outputFile)
{
    std::fprintf(outputFile, "P5\n%ld %ld\n255\n", m_canvas.size(), m_canvas.size());
    std::fwrite(m_canvas.getFirstPixelPointer(), m_canvas.size(), m_canvas.size(), outputFile);
    std::fclose(outputFile);
}