//
// Created by orange on 2020/5/29.
//

#include "server/dataset_manager.h"
//

#include <Poco/File.h>
#include <Poco/Path.h>
//
#include "utils/md5.h"

using Hash = Chocobo1::MD5;
//
/**
 *
 * @param point_cloud_path
 * @return
 */
std::string DatasetManager::AddPointCloudDataset(const std::string &point_cloud_path) {
  //
  Poco::File pc_file(point_cloud_path);
  Poco::Path pc_path(point_cloud_path);
  //
  std::string data_set_dir;
  if (pc_file.isFile()) {
    if (pc_path.getFileName() == "cloud.js") {
      //
      data_set_dir = pc_path.parent().absolute().toString();
    }
  } else if (pc_file.isDirectory()) {
    Poco::File pc_cloud_file(point_cloud_path + "/cloud.js");
    if (pc_cloud_file.exists()) {
      data_set_dir = pc_path.absolute().toString();
    }
  }
  //
  if (!data_set_dir.empty()) {
    const std::string &hash_key = Hash().addData(data_set_dir.data(), data_set_dir.size()).finalize().toString();
    point_cloud_datasets_.insert({hash_key, data_set_dir});
    //
    return hash_key;
  }
  return "";
}
/**
 *
 * @param key
 * @return
 */
std::string DatasetManager::GetPointCloudPath(const std::string &key) {
  auto find_it = point_cloud_datasets_.find(key);
  //
  if (find_it != point_cloud_datasets_.end()) {
    //
    return find_it->second;
  }
  //
  return "";
}

size_t DatasetManager::GetPointCloudNums() { return point_cloud_datasets_.size(); }