#include "pixelator.h"

#include <QImage>

QPixmap gw::Pixelator::doPixelate(const QPixmap& source, const int pixelSize) noexcept
{
    const QImage imageOriginal { source.toImage() };
    QImage imageResult { source.toImage() };

    const int width  = source.width();
    const int height = source.height();
    const int maxx = 1 + (width  / pixelSize);
    const int maxy = 1 + (height / pixelSize);

    for (int y = 0; y != maxy; ++y) {
        const int y1 = (y * pixelSize);
        if (y1 >= height) continue;
        const int y2 = std::min(y1 + pixelSize, height);

        for (int x = 0; x != maxx; ++x) {
            const int x1 = (x * pixelSize);
            if (x1 >= width) continue;
            const int x2 = std::min( x1 + pixelSize, width);
            const QRgb p { getPixel(imageOriginal, x1, y1, x2, y2) };
            setPixel(imageResult, x1, y1, x2, y2, p);
        }
    }
    QPixmap result { QPixmap::fromImage(imageResult) };
    return result;
}

QRgb gw::Pixelator::getPixel(const QImage& image, const int x1, const int x2, const int y) noexcept
{
    const int nPixels = x2 - x1;
    int sumRed   = 0;
    int sumGreen = 0;
    int sumBlue  = 0;

    for (int x = x1; x != x2; ++x) {
        const QRgb p { image.pixel(x,y) };
        sumRed   += qRed(p);
        sumGreen += qGreen(p);
        sumBlue  += qBlue(p);
    }
    const int averageRed   = sumRed   / nPixels;
    const int averageGreen = sumGreen / nPixels;
    const int averageBlue  = sumBlue  / nPixels;

    QRgb rgb { qRgb(averageRed,averageGreen,averageBlue) };
    return rgb;
}

QRgb gw::Pixelator::getPixel(const QImage& image, const int x1, const int y1, const int x2,  const int y2) noexcept
{
    const int nPixelsVertical = y2 - y1;
    int sumRed   = 0;
    int sumGreen = 0;
    int sumBlue  = 0;

    for (int y = y1; y != y2; ++y) {
        const QRgb p { getPixel(image,x1,x2,y) };
        sumRed   += qRed(p);
        sumGreen += qGreen(p);
        sumBlue  += qBlue(p);
    }
    const int averageRed   = sumRed   / nPixelsVertical;
    const int averageGreen = sumGreen / nPixelsVertical;
    const int averageBlue  = sumBlue  / nPixelsVertical;

    QRgb rgb { qRgb(averageRed, averageGreen, averageBlue) };
    return rgb;
}

void gw::Pixelator::setPixel(QImage& image, const int x1, const int x2, const int y, const QRgb color) noexcept
{
    for (int x = x1; x != x2; ++x) {
        image.setPixel(x, y, color);
    }
}

void gw::Pixelator::setPixel(QImage& image, const int x1, const int y1, const int x2, const int y2, const QRgb color) noexcept
{
    for (int y = y1; y != y2; ++y) {
        setPixel(image, x1, x2, y, color);
    }
}
