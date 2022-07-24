#pragma once

#include "Image.h"
#include "Point2D.h"

class StringArtImage : public Image
{
public:
    StringArtImage() = default;
    StringArtImage(size_t imageSize, size_t numPins);
    const Point2D& getPin(size_t pinId) const;
private:
    unsigned int m_scale;
    int m_radius;
    int m_numPins;
    std::vector<Point2D> m_pins;
};