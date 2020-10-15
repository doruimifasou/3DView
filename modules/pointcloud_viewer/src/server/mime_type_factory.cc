//
// Created by orange on 2019/9/18.
//

#include "server/mime_type_factory.h"

#include <Poco/Path.h>
#include <rapidjson/istreamwrapper.h>

#include <fstream>
//
#include <QDebug>
#include <QFile>
#include <QTextStream>
//
#include "rapidjson/document.h"

using namespace std;

string MimeTypeFactory::GetMimeType(const string& filename) {
  size_t pos = filename.rfind('.');
  string extension = filename.substr(pos, filename.size() - pos);
  //
  auto find_it = mime_map_.find(extension);
  //
  if (find_it != mime_map_.end()) {
    //
    const string& mime = find_it->second;
    return mime;
  }
  return "";
}
/**
 *
 */
MimeTypeFactory::MimeTypeFactory() {
  //
  QString mime_json_file = ":/assets/file-extension-to-mime-types.json";
  //
  QFile qfile(mime_json_file);
  if (!qfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << " Could not open the file[" << mime_json_file << "] for reading";
    return;
  }
  //
  QTextStream in(&qfile);
  QString myText = in.readAll();
  rapidjson::Document d;
  d.Parse(myText.toStdString().data());
  //
  if (!d.HasParseError()) {
    if (d.IsObject()) {
      for (auto& m : d.GetObject()) {
        //
        string name(m.name.GetString(), m.name.GetStringLength());
        string value(m.value.GetString(), m.value.GetStringLength());
        //
        mime_map_.insert({name, value});
      }
    }
  }
}