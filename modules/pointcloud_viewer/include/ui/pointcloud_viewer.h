//
// Created by orange on 2020/5/28.
//

#ifndef KPOINTCLOUD_VIEWER_POINTCLOUD_VIEWER_H
#define KPOINTCLOUD_VIEWER_POINTCLOUD_VIEWER_H
#include <QWebEngineView>
#include <map>
#include <memory>
#include <string>
//
class GuiServer;
/**
 *
 */
class PointCloudViewer : public QWebEngineView {
  Q_OBJECT
 public:
  explicit PointCloudViewer(int port, QWidget *parent = nullptr);
 signals:
  void OnPageReady();
 public slots:
  void OnPageLoaded();
  void Debug(const QString &message) { qDebug() << message << endl; }

 public:
  virtual QWebEnginePage *page() { return page_; }
  /**
   * 添加点云数据集路径
   *
   * @param point_cloud_path
   * @return
   */
  std::string AddPointCloudDataset(const std::string &point_cloud_path);
  void CallJavascript(const QString &script);

 protected:
  QWebEnginePage *page_;

 private:
  int port_;
  std::shared_ptr<GuiServer> gui_server_ = nullptr;
};

#endif  // KPOINTCLOUD_VIEWER_POINTCLOUD_VIEWER_H
