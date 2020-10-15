//
// Created by orange on 2020/5/28.
//

#include "ui/pointcloud_viewer.h"

#include <QWebChannel>
#include <QWebEngineSettings>
//
//
#include "server/dataset_manager.h"
#include "server/gui_server.h"
/**
 *
 * @param port
 * @param parent
 */
PointCloudViewer::PointCloudViewer(int port, QWidget *parent) : port_(port), QWebEngineView(parent) {
  //
  gui_server_ = std::make_shared<GuiServer>(port_);
  gui_server_->Start();
  //
  page_ = new QWebEnginePage(this);
  //使用widget来与QT通讯，相当于QWebEngineView是浏览器宿主
  auto *webChannel = new QWebChannel(this);
  webChannel->registerObject("widget", this);
  //
  page_->setWebChannel(webChannel);
  //
  page_->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
  page_->settings()->setAttribute(QWebEngineSettings::WebGLEnabled, true);
  page_->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
  //设置页面对象
  this->setPage(page_);
  // QUrl url=QUrl("https://threejs.org/examples/#webgl_animation_keyframes")
  QUrl url = QUrl("qrc:/assets/html/point_cloud_viewer.html");
  this->setUrl(url);
  // this->page()->set
}
/**
 *
 */
void PointCloudViewer::OnPageLoaded() { emit this->OnPageReady(); }
/**
 *
 * @param point_cloud_path
 * @return 数据集的key
 */
string PointCloudViewer::AddPointCloudDataset(const string &point_cloud_path) {
  //
  DatasetManager &dm = DatasetManager::getInstance();
  //
  int pc_nums = dm.GetPointCloudNums();
  string pc_key = dm.AddPointCloudDataset(point_cloud_path);
  if (!pc_key.empty()) {
    //
    QString script = QString::asprintf("addPointCloud('http://127.0.0.1:%d/pointclouds/%s/cloud.js','test_%d');", port_,
                                       pc_key.data(), (pc_nums));
    //
    this->CallJavascript(script);
    //
    return pc_key;
  }
  //
  return "";
}

void PointCloudViewer::CallJavascript(const QString &script) {
  //
  this->page()->runJavaScript(script);
}
