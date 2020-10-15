# 点云QT编辑器工程

## 概述

## 对Potree的封装
    为了简化对Potree资源的hrc资源自动同步列表，实现了一个python脚本tools/update_qrc.py,每次变更Potree资源，则需要运行此脚本进行同步。
## 打包
### Mac OS X
    使用自带的macdeployqt命令打包，发现网络上说的其他方案都不靠谱。