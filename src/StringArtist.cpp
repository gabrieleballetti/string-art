#include "StringArtist.h"

#include <iostream>
#include "BresenhamLineIterator.h"

namespace {
    float CANVAS_LINE_OPACITY = 1.0f;
    float DRAFT_LINE_OPACITY = 0.2f;
    float MAX_ALLOWED_SCORE = 0.0f;
    unsigned int CANVAS_SCALE = 8;
}

StringArtist::StringArtist(const Image& image, unsigned int numPins, unsigned int skipped_neighbors) :
    m_imagePtr(&image),
    m_numPins(numPins),
    m_skipped_neighbors(skipped_neighbors),
    m_iteration(0)
{
    m_canvas = StringArtImage(m_imagePtr->size() * CANVAS_SCALE, m_numPins);
    m_draft = StringArtImage(m_imagePtr->size(), m_numPins);
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

        drawLine(m_draft, currentPinId, nextPinId, DRAFT_LINE_OPACITY);
        drawLine(m_canvas, currentPinId, nextPinId, CANVAS_LINE_OPACITY);
        currentPinId = nextPinId;
    }
}

bool StringArtist::findNextPin(const size_t currentPinId, size_t& bestPinId)
{
    float bestScore = 0;

    for (size_t nextPinId = 0; nextPinId < m_numPins; ++nextPinId)
    {
        int diff = static_cast<int>(nextPinId) - static_cast<int>(currentPinId);
        int dist = std::min(diff % m_numPins, -diff % m_numPins);
        if (dist < m_skipped_neighbors)
            continue;

        unsigned int pixelChanged;
        float score = lineScore(currentPinId, nextPinId, pixelChanged);
        
        if (pixelChanged > 0 && score > bestScore)
        {
            bestScore = score;
            bestPinId = nextPinId;
        }
    }
    std::cout << m_iteration++ << " - " << bestScore << std::endl;
    return bestScore > MAX_ALLOWED_SCORE;
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
        //if (m_draft.getPixelValue(pixel) == 255)
        {
            score += std::max(-4, m_draft.getPixelValue(pixel) - m_imagePtr->getPixelValue(pixel));
            ++pixelChanged;
        }
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