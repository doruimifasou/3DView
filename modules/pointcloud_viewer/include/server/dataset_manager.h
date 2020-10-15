//
// Created by orange on 2020/5/29.
//

#ifndef KPOINTCLOUD_VIEWER_DATASET_MANAGER_H
#define KPOINTCLOUD_VIEWER_DATASET_MANAGER_H
#include <map>
#include <string>
//
#include "utils/singleton.h"
/**
 *
 */
class DatasetManager : public Singleton<DatasetManager> {
  friend class Singleton<DatasetManager>;
 public:
  std::string AddPointCloudDataset(const std::string &point_cloud_path);
  std::string GetPointCloudPath(const std::string &key);
  size_t GetPointCloudNums();
 private:
  std::map<std::string, std::string> point_cloud_datasets_;
};

#endif  // KPOINTCLOUD_VIEWER_DATASET_MANAGER_H
