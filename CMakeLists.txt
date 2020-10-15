cmake_minimum_required(VERSION 3.5)
project(kpointcloud-viewer C CXX)

set(CMAKE_CXX_STANDARD 14)

if (NOT CMAKE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX d)
endif ()


message("project[${PROJECT_NAME}] build type=${CMAKE_BUILD_TYPE}")

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist" CACHE PATH "default install path" FORCE)
endif ()

message("project[${PROJECT_NAME}] install path=${CMAKE_INSTALL_PREFIX}")

#ignore the shape lib warning
if (CMAKE_HOST_APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-tautological-compare")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-tautological-compare")
endif (CMAKE_HOST_APPLE)
if (CMAKE_HOST_UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-declarations")
endif ()

if (CMAKE_HOST_UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif ()

if (USE_SANITIZER)
    if (CMAKE_HOST_UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -O1 -fno-omit-frame-pointer -g")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -O1 -fno-omit-frame-pointer -g")
    endif ()
endif ()
#set msvc /utf-8
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8")
endif (MSVC)
#
include_directories(thirdparty/include)
if (CMAKE_HOST_WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/thirdparty/platform/win64/poco/include)
elseif (CMAKE_HOST_APPLE)
    include_directories(${CMAKE_SOURCE_DIR}/thirdparty/platform/darwin/poco/1.9.2/include)
elseif (CMAKE_HOST_UNIX)
    include_directories(${CMAKE_SOURCE_DIR}/thirdparty/platform/linux/poco/include)
endif ()

if (CMAKE_HOST_WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/thirdparty/platform/win64/poco/lib)
elseif (CMAKE_HOST_APPLE)
    link_directories(${CMAKE_SOURCE_DIR}/thirdparty/platform/darwin/poco/1.9.2/lib)
elseif (CMAKE_HOST_UNIX)
    link_directories(${CMAKE_SOURCE_DIR}/thirdparty/platform/linux/poco/lib)
endif ()
#
add_subdirectory(thirdparty/SQLiteCpp-3.0.0)
#
#
find_package(OpenGL)
find_package(Qt5Widgets)
find_package(Qt5Charts)
find_package(Qt5OpenGL)
find_package(Qt5WebEngine)
find_package(Qt5WebEngineWidgets)
find_package(Qt5Concurrent)
##
if (Qt5Widgets_FOUND)
    ##
    #set(CMAKE_AUTOMOC ON)
    #set(CMAKE_AUTORCC ON)
    #set(CMAKE_AUTOUIC ON)
    message(${Qt5Widgets_INCLUDE_DIRS})
    message("Found Qt Version=${Qt5Widgets_VERSION}")
endif ()
##
add_subdirectory(modules)