// header-start
////////////////////////////////////////////////////////////////////////////////
// \project   yuv-viewer
//
// \file      main.cpp
//
// \brief     display a yuv 4:2:0 image on the screen
//
// \legal     Copyright (c) 2023
//
////////////////////////////////////////////////////////////////////////////////
// header-end

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  a.setOrganizationName("Polytech");
  a.setOrganizationDomain("polytech.unice.fr");
  a.setApplicationName("yuv-viewer");

  MainWindow w;
  w.show();

  return a.exec();
}
