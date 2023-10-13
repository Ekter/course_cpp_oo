#pragma once

#include <QtWidgets>
#include <vector>



struct ImageParameters {
  double zoom_in_factor_;
  double zoom_out_factor_;
  double pan_percent_;

  double xc_;
  double yc_;
  double zoom_;


  int width_;
  int height_;
  int nb_threads_;

  ImageParameters() {
    //
    // prepare the color indexes based on pdf data
    //

    // default size for the image
    width_ = 600;
    height_ = 400;


    zoom_in_factor_ = 0.8;
    zoom_out_factor_ = 1. / zoom_in_factor_;
    pan_percent_ = .10;
    nb_threads_ = 1;
  }

  ~ImageParameters() = default;

  void zoom_in() {
    zoom_ *= zoom_in_factor_;
  }

  void zoom_out() {
    zoom_ *= zoom_out_factor_;
  }
  void pan_left() {
    pan(-pan_percent_, 0.);
  }
  void pan_right() {
    pan(pan_percent_, 0.);
  }
  void pan_up() {
    pan(0., pan_percent_);
  }

  void pan_down() {
    pan(0., -pan_percent_);
  }

  void toggle_curve() {
    qDebug() << "Not implemented";
  }

  void pan(const double h_percent, const double v_percent) {
    qDebug() << "Not implemented";
  }

};
