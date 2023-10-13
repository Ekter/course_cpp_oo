// header-start
////////////////////////////////////////////////////////////////////////////////
// \project   yuv-viewer
//
// \file      yuvimage.cpp
//
// \brief     read a yuv image from a file and convert into a QImage
//
// \legal     Copyright (c) 2023
// \author    Bernard Plessier  bernard.plessier@videncode.com
//
////////////////////////////////////////////////////////////////////////////////
// header-end

#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

#include <QString>
#include <QDebug>

#include "yuvimage.h"
#include "util.h"


static QRgb convert_yuv_to_rgb(uint8_t y, uint8_t u, uint8_t v)
{
auto yi = static_cast<double>(static_cast<uint>(y));
auto ui = static_cast<double>(static_cast<uint>(u));
auto vi = static_cast<double>(static_cast<uint>(v));

double pyi = 1.1643836 * yi;

double r = pyi + 1.8765140 * vi - 268.2065015;
double g = pyi - 0.2132486 * ui - 0.5578116 * vi + 82.8546329;
double b = pyi + 2.1124018 * ui - 289.0175656;

Util::Clamp<double> clamp_to_rgb(0, 255);

return qRgb(clamp_to_rgb(r), clamp_to_rgb(g), clamp_to_rgb(b));
}


void YuvImage::yuv_to_rgb()
{
  // student code here
  // ~25 lines of code
  //
  QPainter painter(this);
  for (int y = 0; y < height_; ++y)
  {
      for (int x = 0; x < width_; ++x)
      {
          int Y = y_raw_[y * width_ + x];
          int block = x / 2 + y * width_ / 4;
          int u = u_raw_[block];
          int v = v_raw_[block];
          painter.fillRect(x, y, 1, 1, QColor(convert_yuv_to_rgb(Y, u, v)));
      }
  }

  // remove these 5 lines
  // painter.fillRect(rect(), Qt::black);
  // painter.setPen(Qt::white);
  // QString text{"No student code yet\nWindow size is %1x%2"};
  // painter.drawText(rect(), Qt::AlignCenter, text.arg(width()).arg(height()));
}

// Assist function for YUV to RGB image creation
// allocate the memory buffers
// and read raw yuv from the ifstream into the buffers
//
void YuvImage::load_from_stream(std::ifstream &yuv_strm)
{
  qDebug() << "INFO: load_from_stream";
  y_raw_ = new uint8_t[width_ * height_];
  u_raw_ = new uint8_t[width_ * height_ / 4];
  v_raw_ = new uint8_t[width_ * height_ / 4];
  for (int i = 0; i < width_ * height_; i++)
  {
    y_raw_[i] = yuv_strm.get();
  }
  for (int i = 0; i < width_ * height_ / 4; i++)
  {
    u_raw_[i] = yuv_strm.get();
  }
  for (int i = 0; i < width_ * height_ / 4; i++)
  {
    v_raw_[i] = yuv_strm.get();
  }
}

// Constructor for the YuvImage
// Note that the default QImage
// will not be used except if a throw.
// We shall use QImage::swap at the end
//

YuvImage::YuvImage(ImageParameters const &params)
    : QImage(300, 100, QImage::Format_RGB32)
{
  qDebug() << "INFO: YuvImage constructor";
  //
  // we can guess the width and height of the file
  // based on the size of the file
  // and a few additional fact
  // 1) width is always greater then height
  // 2) width and height are always multiple of 8
  y_raw_ = nullptr;
  u_raw_ = nullptr;
  v_raw_ = nullptr;
  width_ = 300;
  height_ = 100;

  const std::string &file_name = params.yuv_file_name_;

  try
  {
    std::ifstream yuv_strm(file_name, std::ios::in | std::ios::binary);
    yuv_strm.exceptions(std::ifstream::eofbit |
                        std::ifstream::failbit |
                        std::ifstream::badbit);

    // position stream pointer at the end to read the file size...
    yuv_strm.seekg(0, std::ios::end);
    auto filesize = yuv_strm.tellg();

    // .. and don't forget to put it back to the beg so that we can read
    yuv_strm.seekg(0, std::ios::beg);

    auto ysize = (filesize * 2) / 3;
    if (((ysize * 3) / 2) != filesize)
    {
      throw wrong_size_();
    }

    // dummy algorithm for width and height
    switch (ysize)
    {
    case 3840 * 2160:
      width_ = 3840;
      height_ = 2160;
      break;
    case 1920 * 1080:
      width_ = 1920;
      height_ = 1080;
      break;
    case 1024 * 768:
      width_ = 1024;
      height_ = 768;
      break;
    case 832 * 480:
      width_ = 832;
      height_ = 480;
      break;
    case 352 * 288:
      width_ = 352;
      height_ = 288;
      break;
    default:
      throw wrong_size_();
    }

    qDebug() << "INFO: Image width  is " << width_;
    qDebug() << "INFO: Image height is " << height_;

    //
    // initialize raw memory from the input stream
    //
    load_from_stream(yuv_strm);

    // from now on, no more exception
    // we can allocate an image of the required size
    // ready to be used

    QImage main_image(width_, height_, QImage::Format_RGB32);
    swap(main_image);

    // and convert yuv raw data to rgb
    yuv_to_rgb();
  }

  catch (const std::ios_base::failure &error)
  {
    qDebug() << "INFO: catch i/o failure " << QString::fromStdString(error.what());
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, "Could not read from file");
  }

  catch (const std::bad_alloc &error)
  {
    qDebug() << "INFO: catch bad_alloc " << QString::fromStdString(error.what());
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, "Can't allocate memory");
  }

  catch (const std::exception &error)
  {
    qDebug() << "INFO: catch some error " << QString::fromStdString(error.what());
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, "Incorrect file size");
  }
}
