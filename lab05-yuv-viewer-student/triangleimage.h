#pragma once

#include <QPointF>
#include <QImage>
#include <QPainter>
#include "imageparams.h"

class TriangleImage : public QImage
{
public:
  TriangleImage(ImageParameters const &params);
private:
  QPointF red_;
  QPointF green_;
  QPointF blue_;

  double xmin_;
  double ymin_;
  double xmax_;
  double ymax_;
  int xmin_pixel_;
  int ymin_pixel_;
  int xmax_pixel_;
  int ymax_pixel_;

  int margin_;
  int x_offset_;
  int y_offset_;
  int square_size_;
  double square_size_d_;

  void compute_bbox();
  void draw_grid(QPainter &painter);
};
