//
// Created by orange on 2019/9/18.
//

#ifndef KPEARTH_SERVER_MIME_TYPE_FACTORY_H
#define KPEARTH_SERVER_MIME_TYPE_FACTORY_H

#include <string>
#include <map>

#include "utils/singleton.h"


using namespace std;

/**
 *
 */
class MimeTypeFactory : public Singleton<MimeTypeFactory> {
  friend class Singleton<MimeTypeFactory>;
 public:
  MimeTypeFactory();
 public:
   string GetMimeType(const string &filename);

 private:
  map<string,string> mime_map_;
};

#endif  // KPEARTH_SERVER_MIME_TYPE_FACTORY_H
