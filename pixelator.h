#ifndef PIXELATOR_H
#define PIXELATOR_H

#include <vector>
#include <QPixmap>

struct QImage;

namespace gw {

class Pixelator {
public:
    static QPixmap doPixelate(const QPixmap& source, const int pixelSize) noexcept;

private:
    //Get a line of pixel's average greyness
    //From x1 to (not including) x2
    //From http://www.richelbilderbeek.nl
    static QRgb getPixel(const QImage& image, const int x1, const int x2, const int y) noexcept;

    //Get a square of pixels' average greyness
    //From http://www.richelbilderbeek.nl
    static QRgb getPixel(const QImage& image, const int x1, const int y1, const int x2, const int y2) noexcept;

    //Set a square of pixels' color
    //From http://www.richelbilderbeek.nl
    static void setPixel(QImage& image, const int x1, const int y1, const int x2, const int y2, const QRgb color) noexcept;

    //Set a line of pixel's color
    //From http://www.richelbilderbeek.nl/CppSetPixel.htm
    static void setPixel(QImage& image, const int x1, const int x2, const int y, const QRgb color) noexcept;
};

} //~namespace gw


#endif
