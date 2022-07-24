#pragma once

#include <cstdio>
#include <vector>

#include "Point2D.h"

class Image
{
public:
    Image() = default;
    Image(size_t imageSize);
    Image(std::FILE* imageFile, size_t imageSize);
    size_t size() const;
    void setPixelValue(const Point2D& pixel, unsigned char value);
    unsigned char getPixelValue(const Point2D& pixel) const;
    unsigned char* getFirstPixelPointer();
private:
    std::vector<unsigned char> m_data;
    size_t m_imageSize;
};