#pragma once

#include <QImage>
#include "imageparams.h"

class CheckerImage : public QImage
{
public:
  CheckerImage(ImageParameters const &params);
};
