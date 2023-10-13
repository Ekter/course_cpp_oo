// header-start
////////////////////////////////////////////////////////////////////////////////
// \project   yuv-viewer
//
// \file      mainwindow.cpp
//
// \brief     based on user input display on the screen
//            - yuv 4:2:0 image from a selected file
//            - a BT709 colored triangle
//
// \legal     Copyright (c) 2023
//
////////////////////////////////////////////////////////////////////////////////
// header-end

#include "imageparams.h"
#include "mainwindow.h"
#include "checkerimage.h"
#include "triangleimage.h"
#include "yuvimage.h"

const int MainWindow::MAX_RECENT_FILES = 5;

QSize
MainWindow::sizeHint() const
{
  return QSize(600, 400);
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  //
  // construct image_widget and scroll area
  //
  image_widget_ = new QLabel;
  image_widget_->setBackgroundRole(QPalette::Base);
  image_widget_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  image_widget_->setScaledContents(true);
  image_widget_->setMinimumSize(600, 400);
  image_widget_->setFrameStyle(QFrame::NoFrame);

  scroll_area_ = new QScrollArea;
  scroll_area_->setBackgroundRole(QPalette::Dark);

  is_full_screen_ = false;

  create_actions();
  create_menus();

  update_recent_file_actions();

  setCentralWidget(image_widget_);
  //resize(QGuiApplication::primaryScreen()->availableSize() * 2 / 5);
}


void
MainWindow::create_actions()
{
  //
  action_checker_image_ = new QAction(tr("Open Checker Image"), this);
  connect(action_checker_image_, SIGNAL(triggered()), this, SLOT(slot_load_checker_image()));

  action_open_ = new QAction(tr("&Open..."), this);
  action_open_->setShortcut(tr("Ctrl+O"));
  connect(action_open_, SIGNAL(triggered()), this, SLOT(slot_open_file()));

  action_menu_open_recent_title_ = new QAction(tr("Recently Opened Files"), this);

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
  action_full_screen_->setEnabled(true);
  action_full_screen_->setShortcut(tr("Ctrl+L"));
  connect(action_full_screen_, SIGNAL(triggered()), this, SLOT(slot_full_screen()));

  action_normal_size_ = new QAction(tr("&Normal Size"), this);
  action_normal_size_->setShortcut(tr("Ctrl+S"));
  action_normal_size_->setEnabled(true);
  connect(action_normal_size_, SIGNAL(triggered()), this, SLOT(slot_normal_size()));

  action_fit_to_window_ = new QAction(tr("&Fit to Window"), this);
  action_fit_to_window_->setEnabled(false);
  action_fit_to_window_->setCheckable(true);
  action_fit_to_window_->setShortcut(tr("Ctrl+F"));
  connect(action_fit_to_window_, SIGNAL(triggered()), this, SLOT(slot_fit_to_window()));

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

void
MainWindow::slot_exit()
{
  close();
}

void
MainWindow::slot_about()
{
    QMessageBox::about(this, tr("About YUV Viewer"),
            tr("<p><b>yuv-viewer</b> display on the screen an YUV 4:2:0 image "
               "read from a given file.</p>"));
}

void
MainWindow::slot_thread_changed()
{
  int value = spinbox_thread_->value();
  image_params_.nb_threads_ = value;
  redraw_image();
}

void
MainWindow::slot_zoom_in()
{
  qDebug() << "INFO: slot_zoom_in() is not implemented yet!";
}

void
MainWindow::slot_zoom_out()
{
  qDebug() << "INFO: slot_zoom_out() is not implemented yet!";

}

void
MainWindow::slot_normal_size()
{
  qDebug() << "INFO: slot_normal_size() is not implemented yet!";

}

void
MainWindow::slot_fit_to_window() {
  qDebug() << "INFO: slot_fit_to_window() is not implemented yet!";

}
void
MainWindow::slot_full_screen()
{
  if (is_full_screen_) {
    qDebug() << "full screen is turned off";
    showNormal();
    menuBar()->show();
    is_full_screen_ = false;
  } else {
    qDebug() << "full screen is turned on";
    is_full_screen_ = true;
    menuBar()->hide();
    showFullScreen();
  }
}



void
MainWindow::create_menus()
{
  menu_file_ = new QMenu(tr("&File"), this);

  menu_open_recent_ = new QMenu(menu_file_);
  menu_open_recent_->setTitle(tr("Open Recent"));
  menu_open_recent_->addAction(action_menu_open_recent_title_);
  menu_open_recent_->addSeparator();

  menu_file_->addAction(action_open_);
  menu_file_->addAction(menu_open_recent_->menuAction());
  menu_file_->addAction(action_checker_image_);
  menu_file_->addAction(action_triangle_image_);
  menu_open_recent_->addSeparator();
  menu_file_->addAction(action_exit_);


  menu_view_ = new QMenu(tr("&View"), this);
  menu_view_->addAction(action_zoom_in_);
  menu_view_->addAction(action_zoom_out_);
  menu_view_->addAction(action_normal_size_);
  menu_view_->addSeparator();
  menu_view_->addAction(action_fit_to_window_);
  menu_view_->addAction(action_full_screen_);

  menu_thread_ = new QMenu(tr("&Thread"), this);
  menu_thread_->addAction(action_thread_);
  menu_help_ = new QMenu(tr("&Help"), this);
  menu_help_->addAction(action_about_);

  for (int i = 0; i < MAX_RECENT_FILES; ++i) {
    auto qaction = new QAction(this);
    action_open_recent_files_.push_back(qaction);

    qaction->setVisible(false);
    menu_open_recent_->addAction(qaction);

    connect(qaction, SIGNAL(triggered()), this, SLOT(slot_open_recent_file()));
  }

  menuBar()->addMenu(menu_file_);
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
  qDebug() << "resize Event  " << event->size().width() << "," << event->size().height();
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
  } else if (image_kind_ == ImageKind::YuvImage) {
    //slot_load_yuv_image();
  }
}

static  QString base_dir(QDir::homePath());

//
// Checker
//
void
MainWindow::slot_load_checker_image()
{
  image_kind_ = ImageKind::Checker;
  setCentralWidget(image_widget_);

  CheckerImage checker_image(image_params_);
  image_widget_->setPixmap(QPixmap::fromImage(checker_image));
  image_widget_->adjustSize();

}
//
// Draw Triangle
//

void
MainWindow::slot_load_triangle_image() {
  image_kind_ = ImageKind::Triangle;
  TriangleImage triangle_image(image_params_);
  setCentralWidget(image_widget_);

  image_widget_->setPixmap(QPixmap::fromImage(triangle_image));
  image_widget_->adjustSize();
}

void
MainWindow::slot_open_recent_file()
{
  QAction *action = qobject_cast<QAction *>(sender());
  if (action) {
    QString file_name = action->data().toString();

    image_params_.yuv_file_name_ = file_name.toStdString();
    slot_load_yuv_image();
  }
}


void MainWindow::slot_open_file()
{
  QString file_name =
      QFileDialog::getOpenFileName(this,
                                   tr("Open Raw File"),
                                   base_dir,
                                   tr("Images (*.yuv);;Any files (*)"));

  if (file_name.isEmpty()) {
    // may be the result of a "cancel" action in the fileDialog
    return;
  }
  // update the base_dir so that we open from the last location
  // next time
  base_dir = QFileInfo(file_name).canonicalPath();

  set_current_file(file_name);
  image_params_.yuv_file_name_ = file_name.toStdString();
  slot_load_yuv_image();
}


void
MainWindow::slot_load_yuv_image()
{
  image_kind_ = ImageKind::YuvImage;

  YuvImage image(image_params_);
  image_widget_->setPixmap(QPixmap::fromImage(image));
  image_widget_->adjustSize();
  scroll_area_->setWidget(image_widget_);
  setCentralWidget(scroll_area_);
  //if(not is_full_screen_) {
  //  setMaximumSize(800, 500);
  //}
}

void MainWindow::set_current_file(const QString &file_name)
{
  QString key("recentFileList");

  // query file list from key "recentFileList"
  // move fileName to top of the list
  // and remove other instance of fileName

  QSettings settings;
  QStringList files = settings.value(key).toStringList();
  files.removeAll(file_name);
  files.prepend(file_name);
  while (files.size() > MAX_RECENT_FILES) {
    files.removeLast();
  }
  settings.setValue(key, files);

  foreach (QWidget *widget, QApplication::topLevelWidgets()) {
    MainWindow *main_window = qobject_cast<MainWindow *>(widget);
    if (main_window) {
      main_window->update_recent_file_actions();
    }
  }
}

void
MainWindow::update_recent_file_actions()
{
  QSettings settings;
  QString key("recentFileList");

  QStringList files = settings.value(key).toStringList();

  int numRecentFiles = qMin(files.size(), MAX_RECENT_FILES);

  for (int i = 0; i < numRecentFiles; ++i) {
    QString text = tr("%1").arg(stripped_name(files[i]));
    action_open_recent_files_[i]->setText(text);
    action_open_recent_files_[i]->setData(files[i]);
    action_open_recent_files_[i]->setVisible(true);
  }
  for (int i = numRecentFiles; i < MAX_RECENT_FILES; ++i) {
    action_open_recent_files_[i]->setVisible(false);
  }
}

QString
MainWindow::stripped_name(const QString &full_file_name)
{
  // ensure that we keep at most 50 characters
  //
  QString file_name("/" + QFileInfo(full_file_name).fileName());
  QString path_name(QFileInfo(full_file_name).canonicalPath());

  if (path_name.length() > 6) {
    int  l_path_name = path_name.length();
    int  l_file_name = file_name.length();

    if (l_path_name + l_file_name > 50) {
      int l_left = 50 - (l_file_name + 3);
      l_left = (l_left < 3)  ? 3 : l_left;
      // remove from l_path_name
      path_name = path_name.left(l_left).append("...");
    }
  }
  return path_name + file_name;
}
