//
// Created by orange on 2020/5/28.
//
#include <QAction>
#include <QApplication>

#include <iostream>
#include <string>
//
#include "simple_pointcloud_viewer.h"

using namespace std;


/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
  //
  // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  //
#ifdef __APPLE__
  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setVersion(4, 1);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);
#endif
  //
  QApplication app(argc, argv);
  //
  QFont font;
  font.setPointSize(12);
  font.setFamily("SimSun");
  QApplication::setFont(font);
  //
  //
  SimplePointCloudMainWindow main_window;
  main_window.showMaximized();
  main_window.show();
  //
  //
  int status = QApplication::exec();
  return status;
}