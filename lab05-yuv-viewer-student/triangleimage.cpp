#include <algorithm>

#include "util.h"
#include "imageparams.h"
#include "triangleimage.h"

using namespace Util;

void
TriangleImage::compute_bbox()
{
  xmin_ = std::min({red_.x(), green_.x(), blue_.x()});
  xmax_ = std::max({red_.x(), green_.x(), blue_.x()});
  ymin_ = std::min({red_.y(), green_.y(), blue_.y()});
  ymax_ = std::max({red_.y(), green_.y(), blue_.y()});

  // create world to pixel interpolator
  QPointF x_w2p0{0.0, 0.0};
  QPointF x_w2p1{1.0, square_size_d_};
  QPointF y_w2p0{0.0, square_size_d_};
  QPointF y_w2p1{1.0, 0.0};

  LinearInterpolator x_w2p(x_w2p0, x_w2p1);
  LinearInterpolator y_w2p(y_w2p0, y_w2p1);

  xmin_pixel_ = static_cast<int>(std::floor(x_w2p(xmin_)));
  xmax_pixel_ = static_cast<int>(std::ceil(x_w2p(xmax_)));

  // the y axis on the pixel world is inverted vs. the
  // real world, so min on the world is a max on the pixel
  ymax_pixel_ = static_cast<int>(std::ceil(y_w2p(ymin_)));
  ymin_pixel_ = static_cast<int>(std::floor(y_w2p(ymax_)));
}

void
TriangleImage::draw_grid(QPainter& painter)
{
  //QPainter painter(this);

  // green-ish color
  const QColor gridColor(51, 204, 102);
  QPen gridPen(gridColor);
  painter.setPen(gridPen);

  // given the margin and the square size
  QRect my_rect(x_offset_, y_offset_, square_size_, square_size_);

  // draw border
  painter.drawLine(my_rect.topLeft(), my_rect.topRight());
  painter.drawLine(my_rect.topRight(), my_rect.bottomRight());
  painter.drawLine(my_rect.bottomRight(), my_rect.bottomLeft());
  painter.drawLine(my_rect.bottomLeft(), my_rect.topLeft());

  // modify the pen for dashes
  QVector<qreal> dashes;
  dashes << 2 << 2;
  gridPen.setDashPattern(dashes);
  painter.setPen(gridPen);

  // draw horizontal/vertical/ lines between bars
  // assume width is normalized to 1.0
  // we draw lines at 0.1, 0.2, ... 0.9
  // i.e 9 vertical or horizontal lines
  // how many vertical
  {
    const int num_of_lines = 9;
    QLine vline(my_rect.topLeft(), my_rect.bottomLeft());
    QLine hline(my_rect.topLeft(), my_rect.topRight());
    for (int i=1; i<= num_of_lines; ++i) {
      vline.translate(my_rect.width()/(num_of_lines + 1), 0);
      painter.drawLine(vline);

      hline.translate(0, my_rect.height()/(num_of_lines + 1));
      painter.drawLine(hline);
    }
  }
}

TriangleImage::TriangleImage(ImageParameters const &params)
  : QImage(params.width_, params.height_, QImage::Format_RGB32)
  , red_{0.64, 0.33}
  , green_{0.3, 0.6}
  , blue_{0.15,0.06}
{


  qDebug() << "Draw triangle " << width() << " by " << height();

  margin_ = 60;
  square_size_  = std::min(width(), height()) - margin_;

  // triangle

  x_offset_ = (width() - square_size_) / 2;
  y_offset_ = (height() - square_size_) /2;
  square_size_d_ = static_cast<double>(square_size_);
  compute_bbox();


  // create pixel to world interpolator
  // aka p2w

  QPointF x_p2w0{0.0, 0.0};
  QPointF x_p2w1{square_size_d_ , 1.0};
  QPointF y_p2w0{square_size_d_ , 0.0};
  QPointF y_p2w1{0.0, 1.0};

  LinearInterpolator x_p2w(x_p2w0, x_p2w1);
  LinearInterpolator y_p2w(y_p2w0, y_p2w1);


  QPainter painter(this);
  painter.fillRect(rect(), Qt::black);
  draw_grid(painter);


  // using the results of the bbox
  // to limit the scope of y's and x's
  for (int y = ymin_pixel_; y <= ymax_pixel_ ; ++y) {
    //double y_world = y_p2w(y);

    for (int x = xmin_pixel_; x < xmax_pixel_; ++x) {
      //double x_world = x_p2w(x);
      //code to be added here
      //check if point(x_world, y_world) is inside or outside the triangle
      //if inside, compute the color and set the pixel

      setPixel(x + x_offset_, y + y_offset_, qRgb(0, 100, 100));
    }
  }

}
