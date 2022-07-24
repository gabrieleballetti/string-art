#include "StringArtist.h"

#include <iostream>
#include "BresenhamLineIterator.h"

StringArtist::StringArtist(const Image& image, int numPins) :
    m_imagePtr(&image),
    m_numPins(numPins)
{
    m_canvas = StringArtImage(m_imagePtr->size() * 2, m_numPins);
    m_draft = StringArtImage(m_imagePtr->size(), m_numPins);
}

void StringArtist::windString()
{
    // Wind thread around pins until image can't be improved.
    size_t currentPinId = 0;
    std::cout << "start winding" << std::endl;
    int a = 0;
    while (true)
    {
        size_t nextPinId;
        if (!findNextPin(currentPinId, nextPinId))
            break;

        drawLine(m_draft, currentPinId, nextPinId);
        drawLine(m_canvas, currentPinId, nextPinId);
        currentPinId = nextPinId;
    }
}

bool StringArtist::findNextPin(const size_t currentPinId, size_t& bestPinId) const
{
    float bestScore = 0;

    for (size_t nextPinId = 0; nextPinId < m_numPins; ++nextPinId)
    {
        int diff = static_cast<int>(nextPinId) - static_cast<int>(currentPinId);
        int dist = std::min(diff % m_numPins, -diff % m_numPins);
        if (dist < 10)
            continue;

        unsigned int pixelChanged;
        float score = lineScore(currentPinId, nextPinId, pixelChanged);
        
        if (pixelChanged > 0 && score > bestScore)
        {
            bestScore = score;
            bestPinId = nextPinId;
        }
    }
    std::cout << bestScore << std::endl;
    return bestScore > 128;
}

float StringArtist::lineScore(const size_t currentPinId, const size_t nextPinId, unsigned int& pixelChanged) const
{
    pixelChanged = 0;
    float score = 0.f;
    Point2D currentPin = m_draft.getPin(currentPinId);
    Point2D nextPin = m_draft.getPin(nextPinId);
    //Point2D diff = nextPin - currentPin;
    //int distance = std::max(std::abs(diff[0]), std::abs(diff[1]));

    for (const Point2D& pixel : BresenhamLineIterator(currentPin, nextPin))
    {
        if (m_draft.getPixelValue(pixel) == 255)
        {
            score += std::abs(255 - m_imagePtr->getPixelValue(pixel)) * 1.0f;
            ++pixelChanged;
        }
    }
    return score;
}

void StringArtist::drawLine(StringArtImage& image, const size_t currentPinId, const size_t nextPinId)
{
    for (const Point2D& pixel : BresenhamLineIterator(image.getPin(currentPinId), image.getPin(nextPinId)))
    {
        image.setPixelValue(pixel, 0);
    }
}

void StringArtist::saveImage(std::FILE* outputFile)
{
    std::fprintf(outputFile, "P5\n%ld %ld\n255\n", m_canvas.size(), m_canvas.size());
    std::fwrite(m_canvas.getFirstPixelPointer(), m_canvas.size(), m_canvas.size(), outputFile);
    std::fclose(outputFile);
}