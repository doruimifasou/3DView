//
// Created by orange on 2020/5/28.
//

#ifndef KPOINTCLOUD_VIEWER_SIMPLE_POINTCLOUD_VIEWER_H
#define KPOINTCLOUD_VIEWER_SIMPLE_POINTCLOUD_VIEWER_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QtGui>

#include "ui/pointcloud_viewer.h"
/**
 *
 */
class SimplePointCloudMainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit SimplePointCloudMainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags())
      : QMainWindow(parent, flags) {
    action_inspector_ = new QAction(QObject::tr("调试工具"), this);
    connect(action_inspector_, &QAction::triggered, this, &SimplePointCloudMainWindow::ShowInspector);
    //
    action_quit_ = new QAction(QObject::tr("退出"), this);
    connect(action_quit_, &QAction::triggered, this, &SimplePointCloudMainWindow::close);
    //
    action_open_task_ = new QAction(QObject::tr("添加点云"), this);
    connect(action_open_task_, &QAction::triggered, this, &SimplePointCloudMainWindow::ShowOpenTask);
    //
    auto *file_menu = menuBar()->addMenu(QObject::tr("文件"));
    file_menu->addAction(action_open_task_);
    file_menu->addSeparator();
    file_menu->addAction(action_quit_);
    //
    auto *tools_menu = menuBar()->addMenu(QObject::tr("工具"));
    tools_menu->addAction(action_inspector_);
    //
    view_ = new PointCloudViewer(9999, this);
    this->setCentralWidget(view_);
    //

    //
    this->setWindowTitle("点云性能演示");
  }
 protected slots:
  void ShowOpenTask() {
    QString dir_path = QFileDialog::getExistingDirectory(this, tr("指定任务目录"), "",
                                                         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    std::string task_path = dir_path.toStdString();
    if(!task_path.empty()){
      view_->AddPointCloudDataset(task_path);
    }
  };
  void ShowInspector() {
    //
    inspector_ = new QWebEngineView(nullptr);
    inspector_->load(QUrl("http://localhost:9998"));
    // inspector_->load(QUrl("chrome://gpu"));
    inspector_->setWindowTitle(tr("开发者工具"));
    view_->page()->setDevToolsPage(inspector_->page());
    //
    inspector_->show();
  }

 private:
  QAction *action_inspector_;
  QAction *action_open_task_;
  QAction *action_quit_;
  QWebEngineView *inspector_;
  PointCloudViewer *view_;
};
#endif  // KPOINTCLOUD_VIEWER_SIMPLE_POINTCLOUD_VIEWER_H
