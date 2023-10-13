// header-start
////////////////////////////////////////////////////////////////////////////////
// \project   yuv-image
//
// \file      yuvimage.h
//
// \brief     include file for YuvImage class
//
// \legal     Copyright (c) 2023
//
// \author    Bernard Plessier
//
////////////////////////////////////////////////////////////////////////////////
// header-end

#pragma once

#include <QtWidgets>
#include <cstring>
#include <string>
#include <exception>
#include "imageparams.h"

QT_BEGIN_NAMESPACE
class QImage;
QT_END_NAMESPACE


class YuvImage : public QImage {
public:
  explicit YuvImage(const ImageParameters& params);
  YuvImage(const YuvImage &image);
  void load_from_stream(std::ifstream &yuv_strm);
  void yuv_to_rgb();

  ~YuvImage() {
    delete [] y_raw_;
    delete [] u_raw_;
    delete [] v_raw_;
  }

  // A nested class extending the exception class
  // we shall thow an exception if the size of the
  // file does not match some expected values
  // the usage is:  throw wrong_size();
  // which calls the constructor for this class
  // As you can see, no constructor exists so
  // wrong_size() calls the default constructor
  // which call the base class constructor std::exception();
  // which trigger the throw
  // the virtual function what() return a pointer to a const char *
  // the qualifers after the what() are
  // const   => this function does not change the class member value
  // throw() => this function does not throw
  // override => this function is virtual and override the base class function

  class wrong_size_ : public std::exception {
  public:
    const char *what() const throw() override {
      return "File has wrong size";
    }
  };

private:
  int width_;
  int height_;

  uint8_t *y_raw_;
  uint8_t *u_raw_;
  uint8_t *v_raw_;
};
