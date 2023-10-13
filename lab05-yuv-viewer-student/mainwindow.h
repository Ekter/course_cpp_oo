// header-start
////////////////////////////////////////////////////////////////////////////////
// \project   yuv-viwer
//
// \file      mainwindow.h
//
// \brief     based on user input display on the screen
//            - yuv 4:2:0 image from a selected file
//            - a BT709 colored triangle
//
// \legal     Copyright (c) 2023
//
// \author    Bernard Plessier
//
////////////////////////////////////////////////////////////////////////////////
// header-end

#pragma once

#include "imageparams.h"
#include <QtWidgets>
#include <QMainWindow>
#include <vector>

enum class ImageKind : int {
  None,
  Triangle,
  Checker,
  YuvImage,
  Undefined
};

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  static const int MAX_RECENT_FILES;
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override = default;

  void resizeEvent(QResizeEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  QSize sizeHint() const override;

  QLabel *image_widget_;
  QScrollArea *scroll_area_;

private slots:
  void slot_exit();
  void slot_about();
  void slot_open_file();
  void slot_open_recent_file();
  void slot_load_yuv_image();
  void slot_load_checker_image();
  void slot_load_triangle_image();
  void slot_zoom_in();
  void slot_zoom_out();
  void slot_thread_changed();
  void slot_full_screen();
  void slot_normal_size();
  void slot_fit_to_window();

private:
  ImageKind image_kind_;
  void redraw_image();
  void create_menus();
  void create_actions();
  ImageParameters image_params_;
  bool is_full_screen_;

  int delta_width_;
  int delta_height_;

  void update_recent_file_actions();

  void set_current_file(const QString &);
  QString stripped_name(const QString &);


  std::vector<QAction *> action_open_recent_files_;
  QAction *action_open_;
  QAction *action_triangle_image_;
  QAction *action_checker_image_;
  QAction *action_exit_;
  QAction *action_zoom_in_;
  QAction *action_zoom_out_;
  QAction *action_full_screen_;
  QAction *action_normal_size_;
  QAction *action_fit_to_window_;
  QAction *action_about_;
  QWidgetAction *action_thread_;
  QSpinBox *spinbox_thread_;

  QAction *action_menu_open_recent_title_;
  QMenu *menu_open_;
  QMenu *menu_file_;
  QMenu *menu_open_recent_;
  QMenu *menu_view_;
  QMenu *menu_thread_;
  QMenu *menu_help_;
  bool accept_user_event_;
};
