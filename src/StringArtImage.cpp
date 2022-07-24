#include "StringArtImage.h"

#include <cmath>

namespace {
    const double PI = 3.141592653589793;
}

StringArtImage::StringArtImage(size_t imageSize, size_t numPins) :
    Image(imageSize),
    m_radius((imageSize - 1) / 2),
    m_numPins(numPins)
{
    m_pins.resize(m_numPins);
    for (size_t pinId = 0; pinId < m_numPins; ++pinId)
    {
        double angle = 2 * PI / m_numPins * pinId;
        m_pins[pinId][0] = static_cast<int>(m_radius * (1 + std::cos(angle)) + 0.5f);
        m_pins[pinId][1] = static_cast<int>(m_radius * (1 - std::sin(angle)) + 0.5f);
    }
}

const Point2D& StringArtImage::getPin(size_t pinId) const
{
    return m_pins[pinId];
}
