#include "Image.h"

Image::Image(size_t imageSize) :
    m_imageSize(imageSize)
{
    m_data.resize(m_imageSize * m_imageSize, 255);
}

Image::Image(std::FILE* imageFile, size_t imageSize) :
    m_imageSize(imageSize)
{
    m_data.resize(m_imageSize * m_imageSize);
    std::fread(&m_data[0], 1, m_imageSize * m_imageSize, imageFile);
    std::fclose(imageFile);
}

size_t Image::size() const
{
    return m_imageSize;
}

void Image::setPixelValue(const Point2D& pixel, unsigned char value)
{
    m_data[pixel[1] * m_imageSize + pixel[0]] = value;
}

unsigned char Image::getPixelValue(const Point2D& pixel) const
{
    return m_data[pixel[1] * m_imageSize + pixel[0]];
}

unsigned char* Image::getFirstPixelPointer()
{
    return &m_data[0];
}
