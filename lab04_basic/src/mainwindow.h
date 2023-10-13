#pragma once

#include "imageparams.h"
#include <QtWidgets>
#include <QMainWindow>

enum class ImageKind : int {
  None,
  Triangle,
  Checker,
  Undefined
};

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override = default;
  void resizeEvent(QResizeEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  QSize sizeHint() const override;

private slots:
  void slot_exit();
  void slot_about();
  void slot_load_triangle_image();
  void slot_load_checker_image();
  void slot_zoom_in();
  void slot_zoom_out();
  void slot_thread_changed();
  void slot_full_screen();

private:
  ImageKind image_kind_;
  QLabel *image_widget_;

  void redraw_image();
  void create_menus();
  void create_actions();

  ImageParameters image_params_;
  bool is_full_screen_;

  int delta_width_;
  int delta_height_;

  QAction *action_triangle_image_;
  QAction *action_checker_image_;
  QAction *action_exit_;
  QAction *action_zoom_in_;
  QAction *action_zoom_out_;
  QAction *action_full_screen_;
  QAction *action_about_;
  QWidgetAction *action_thread_;
  QSpinBox *spinbox_thread_;

  QMenu *menu_open_;
  QMenu *menu_view_;
  QMenu *menu_thread_;
  QMenu *menu_help_;
  bool accept_user_event_;
};
