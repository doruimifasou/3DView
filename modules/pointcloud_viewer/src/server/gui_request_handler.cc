//
// Created by joseph on 2018/1/18.
//

#include "server/gui_request_handler.h"

#include <QDebug>
#include <QFile>
#include <QString>
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//
#include <Poco/Net/HTTPServer.h>
#include <Poco/StreamCopier.h>
//
#include "server/dataset_manager.h"
#include "server/mime_type_factory.h"
//
using namespace std;
/**
 *
 * @param request
 * @param response
 */
void GuiRequestHandler::DoResource(HTTPServerRequest &request, HTTPServerResponse &response) {
  //
  const string &uri = request.getURI();
  //
  // response.add("Access-Control-Allow-Origin", "*");
  QFile qfile(QString::fromStdString(":" + uri));
  if (!qfile.open(QFile::ReadOnly)) {
    qDebug() << QString::fromStdString("could not open file for read=" + uri);
    //

    response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND, "Not found the file!");
    return;
  } else {
    //
    MimeTypeFactory &mime_factory = MimeTypeFactory::getInstance();
    const string &mime_type = mime_factory.GetMimeType(uri);
    if (!mime_type.empty()) {
      response.setContentType(mime_type);
    }
    //
    QByteArray iContents = qfile.readAll();
    //
    response.setContentLength64(iContents.length());
    response.sendBuffer(iContents.data(), iContents.length());
  }
}
/**
 *
 * @param request
 * @param response
 */
void GuiRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) {
  //
  response.add("Access-Control-Allow-Origin", "*");
  //
  string strack("/pointclouds/");
  string smedia("/assets/");
  string uri = request.getURI();
  if (uri.compare(0, strack.size(), strack) == 0) {
    DoPointClouds(request, response);
  } else if (uri.compare(0, smedia.size(), smedia) == 0) {
    //
    DoResource(request, response);
  }
}
/**
 *
 * @param request
 * @param response
 */
void GuiRequestHandler::DoPointClouds(HTTPServerRequest &request, HTTPServerResponse &response) {
  const string &uri = request.getURI();
  //获取数据集
  response.setChunkedTransferEncoding(true);
  //
  size_t pc_path_len = string("/pointclouds/").size();
  string uri_part = uri.substr(pc_path_len, uri.size() - pc_path_len);
  std::size_t find_pos = uri_part.find_first_of('/');
  if (find_pos != string::npos) {
    string data_name = uri_part.substr(0, find_pos);
    string res_name = uri_part.substr(find_pos + 1, uri_part.length() - find_pos - 1);
    //
    DatasetManager &dm = DatasetManager::getInstance();
    //
    const string &pc_path = dm.GetPointCloudPath(data_name);
    if (!pc_path.empty()) {
      //
      string full_path=pc_path+"/"+res_name;
      std::fstream fs;
      fs.open(full_path, fstream::in);
      if (fs.is_open()) {
        //
        auto& os = response.send();
        Poco::StreamCopier::copyStream(fs, os);
        //
        fs.close();
      }
      return;
    }
  }
  response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND, "Not found the file!");
}
