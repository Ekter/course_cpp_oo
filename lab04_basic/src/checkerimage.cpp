#include "imageparams.h"
#include "checkerimage.h"


CheckerImage::CheckerImage(ImageParameters const &params)
  : QImage(params.width_, params.height_, QImage::Format_RGB32)
{
  QPainter painter(this);
  painter.fillRect(rect(), Qt::black);
  for (int y = 0; y < height(); ++y) {
    for (int x = 0; x < width(); ++x) {
      if ((x ^ y) & 0x20) {
        setPixel(x, y, qRgb(255, 255, 255));
      }
    }
  }
}
