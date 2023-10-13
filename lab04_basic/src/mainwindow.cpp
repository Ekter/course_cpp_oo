#include <iostream>
#include "imageparams.h"
#include "mainwindow.h"
#include "checkerimage.h"

QSize
MainWindow::sizeHint() const
{
  return QSize(600, 400);
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{

  image_widget_ = new QLabel;
  image_widget_->setBackgroundRole(QPalette::Base);
  image_widget_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  image_widget_->setScaledContents(true);
  image_widget_->setMinimumSize(600, 400);
  setCentralWidget(image_widget_);

  create_actions();
  create_menus();
  is_full_screen_ = false;
  image_kind_ = ImageKind::None;



}

void MainWindow::create_actions() {
  //
  action_checker_image_ = new QAction(tr("Open Checker Image"), this);
  connect(action_checker_image_, SIGNAL(triggered()), this, SLOT(slot_load_checker_image()));

  action_triangle_image_ = new QAction(tr("Open Triangle Image"), this);
  connect(action_triangle_image_, SIGNAL(triggered()), this, SLOT(slot_load_triangle_image()));

  action_exit_ = new QAction(tr("E&xit"), this);
  action_exit_->setShortcut(tr("Ctrl+Q"));
  connect(action_exit_, SIGNAL(triggered()), this, SLOT(slot_exit()));

  action_zoom_in_ = new QAction(tr("Zoom &In (25%)"), this);
  action_zoom_in_->setShortcut(tr("Ctrl++"));
  action_zoom_in_->setEnabled(false);
  connect(action_zoom_in_, SIGNAL(triggered()), this, SLOT(slot_zoom_in()));

  action_zoom_out_ = new QAction(tr("Zoom &Out (25%)"), this);
  action_zoom_out_->setShortcut(tr("Ctrl+-"));
  action_zoom_out_->setEnabled(false);
  connect(action_zoom_out_, SIGNAL(triggered()), this, SLOT(slot_zoom_out()));

  action_full_screen_ = new QAction(tr("&Full Screen"), this);
  action_full_screen_->setEnabled(false);
  action_full_screen_->setShortcut(tr("Ctrl+L"));
  connect(action_full_screen_, SIGNAL(triggered()), this, SLOT(slot_full_screen()));

  action_about_ = new QAction(tr("&About"), this);
  connect(action_about_, SIGNAL(triggered()), this, SLOT(slot_about()));

  spinbox_thread_ = new QSpinBox;
  spinbox_thread_->setRange(1, 20);
  spinbox_thread_->setSingleStep(1);
  spinbox_thread_->setValue(1);

  action_thread_ = new QWidgetAction(nullptr);
  action_thread_->setDefaultWidget(spinbox_thread_);
  connect(spinbox_thread_, &QSpinBox::valueChanged, this,
         [this]() { this->slot_thread_changed(); }
  );
}

void MainWindow::slot_exit() {
  close();
}

void MainWindow::slot_about() {
    QMessageBox::about(this, tr("About Combo Viewer"),
            tr("<p>A <b>triangle image</b> is displayed on the screen, the user can "
               "<p>In addition, the user can view a checker image</p>"));
}

void
MainWindow::slot_thread_changed() {
  int value = spinbox_thread_->value();
  image_params_.nb_threads_ = value;
  redraw_image();
}

void MainWindow::slot_zoom_in() {
  image_params_.zoom_in();
  redraw_image();
}

void MainWindow::slot_zoom_out() {
  image_params_.zoom_out();
  redraw_image();
}

void MainWindow::slot_full_screen() {
  if (is_full_screen_) {
    showNormal();
    menuBar()->show();
    is_full_screen_ = false;
  } else {
    is_full_screen_ = true;
    menuBar()->hide();
    showFullScreen();
  }
}

void MainWindow::create_menus() {
  menu_open_ = new QMenu(tr("&Open"), this);

  menu_open_->addAction(action_triangle_image_);
  menu_open_->addAction(action_checker_image_);
  menu_open_->addAction(action_triangle_image_);
  menu_open_->addAction(action_exit_);


  menu_view_ = new QMenu(tr("&View"), this);
  menu_view_->addAction(action_zoom_in_);
  menu_view_->addAction(action_zoom_out_);
  menu_view_->addSeparator();
  menu_view_->addAction(action_full_screen_);

  menu_thread_ = new QMenu(tr("&Thread"), this);
  menu_thread_->addAction(action_thread_);

  menu_help_ = new QMenu(tr("&Help"), this);
  menu_help_->addAction(action_about_);

  menuBar()->addMenu(menu_open_);
  menuBar()->addMenu(menu_view_);
  menuBar()->addMenu(menu_thread_);
  menuBar()->addMenu(menu_help_);
}


void
MainWindow::mouseReleaseEvent(QMouseEvent *event)  {
  qDebug() << "Mouse Release at " << event->pos().x() << "," << event->pos().y();
}

//! \brief This is a virtual function override
//         base class behavior only
//         When the window has change size, we call a redraw of the
//         triangle image
//
void MainWindow::resizeEvent(QResizeEvent *event) {
  image_params_.width_  = event->size().width();
  image_params_.height_ = event->size().height();

  redraw_image();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_Plus:
    image_params_.zoom_in();
    redraw_image();
    break;
  case Qt::Key_Minus:
    image_params_.zoom_out();
    redraw_image();
    break;
  case Qt::Key_Left:
    image_params_.pan_left();
    redraw_image();
    break;
  case Qt::Key_Right:
    image_params_.pan_right();
    redraw_image();
    break;
  case Qt::Key_Down:
    image_params_.pan_down();
    redraw_image();
    break;
  case Qt::Key_Up:
    image_params_.pan_up();
    redraw_image();
    break;
  case Qt::Key_T:
    image_params_.toggle_curve();
    redraw_image();
    break;
  case Qt::Key_Q:
    if (is_full_screen_) {
      showNormal();
      menuBar()->show();
      is_full_screen_ = false;
    }
    break;
  default:
    QWidget::keyPressEvent(event);
  }
}


void MainWindow::redraw_image() {
  if (image_kind_ == ImageKind::Checker) {
    slot_load_checker_image();
  } else if (image_kind_ == ImageKind::Triangle) {
    slot_load_triangle_image();
  }
}


//
// Checker
//
void MainWindow::slot_load_checker_image() {
  image_kind_ = ImageKind::Checker;

  // the Qimage is now drawn
  // we set the image_widget_ to hold the image
  // and adjust the widgets to fit the image

  CheckerImage checker_image(image_params_);
  image_widget_->setPixmap(QPixmap::fromImage(checker_image));
}


//
// Draw Triangle
//
void MainWindow::slot_load_triangle_image() {
  image_kind_ = ImageKind::Triangle;

  //Code for Lab04 here

}





