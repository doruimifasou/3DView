#include and src file
file(GLOB_RECURSE viewer_header include/*.hpp include/*.h)
file(GLOB_RECURSE viewer_src src/*.cpp src/*.c src/*.cc include/glmap/font/*.cc)
file(GLOB_RECURSE viewer_exclude_src test/*.cpp)
list(REMOVE_ITEM viewer_src "${viewer_exclude_src}")
#
if (CMAKE_HOST_WIN32)
elseif (CMAKE_HOST_APPLE)
elseif (CMAKE_HOST_UNIX)
endif ()

if (Qt5Widgets_FOUND)
qt5_add_resources(QT_CORE_RESOURCES src/ui_resources.qrc)
endif()
add_library(pointcloud_viewer SHARED ${viewer_src} ${viewer_header} ${QT_CORE_RESOURCES})
#exe
set_property(TARGET pointcloud_viewer PROPERTY AUTOMOC ON)
set_property(TARGET pointcloud_viewer PROPERTY AUTORCC ON)
set_property(TARGET pointcloud_viewer PROPERTY AUTOUIC ON)
#
#include self include
target_include_directories(pointcloud_viewer PUBLIC include)
#link lib
target_link_libraries(pointcloud_viewer Qt5::Widgets Qt5::WebEngine Qt5::WebEngineWidgets Qt5::Concurrent Qt5::Charts)
#
if (CMAKE_HOST_WIN32)
    #poco
    target_link_libraries(pointcloud_viewer general PocoFoundation.lib PocoJSON.lib PocoNet.lib PocoUtil.lib PocoXML.lib)
elseif (CMAKE_HOST_APPLE)
    #Poco
    target_link_libraries(pointcloud_viewer general PocoFoundation PocoJSON PocoNet PocoUtil PocoXML)
elseif (CMAKE_HOST_UNIX)
    #poco
    target_link_libraries(pointcloud_viewer general PocoNet PocoUtil PocoXML PocoFoundation PocoJSON pthread)
endif ()
#
#thirdparty lib
if (APPLE)
    #find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    #find_library(IOKIT_LIBRARY IOKit)
    #find_library(COREVIDEO_LIBRARY CoreVideo)
    SET(EXTRA_LIBS ${OpenGL_LIBRARY})
    target_link_libraries(pointcloud_viewer ${EXTRA_LIBS})
endif (APPLE)
#
#add_subdirectory(test)
#
INSTALL(TARGETS pointcloud_viewer DESTINATION ./lib)
INSTALL(DIRECTORY include/ui DESTINATION ./include/ FILES_MATCHING PATTERN "ui/*.h")

add_custom_target(install_pointcloud_viewer
        "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target install
        DEPENDS pointcloud_viewer
        COMMENT "Installing pointcloud_viewer")