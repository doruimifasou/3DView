#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(prefix "simple_pointcloud_viewer.app/Contents")
set(INSTALL_RUNTIME_DIR "${prefix}/MacOS")
set(INSTALL_CMAKE_DIR "${prefix}/Resources")
set_source_files_properties(${CMAKE_SOURCE_DIR}/railway.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
#
set(myApp_ICON ${CMAKE_SOURCE_DIR}/railway.icns)
add_executable(simple_pointcloud_viewer MACOSX_BUNDLE simple_pointcloud_viewer.cc ${myApp_ICON})
target_link_libraries(simple_pointcloud_viewer pointcloud_viewer)
#
set_property(TARGET simple_pointcloud_viewer PROPERTY AUTOMOC ON)
set_property(TARGET simple_pointcloud_viewer PROPERTY AUTORCC ON)
set_property(TARGET simple_pointcloud_viewer PROPERTY AUTOUIC ON)
#
set_target_properties(simple_pointcloud_viewer PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/MacOS/MacOSXBundleInfo.plist.in"
        MACOSX_BUNDLE_ICON_FILE railway.icns
        MACOSX_BUNDLE_BUNDLE_NAME "点云演示")
##
INSTALL(TARGETS simple_pointcloud_viewer DESTINATION ./bin)
##
# Retrieve the absolute path to qmake and then use that path to find
# the binaries
get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
if (CMAKE_HOST_WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
elseif (CMAKE_HOST_APPLE)
    find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")
    add_custom_command(TARGET simple_pointcloud_viewer POST_BUILD
            COMMAND "${MACDEPLOYQT_EXECUTABLE}"
            "$<TARGET_FILE_DIR:simple_pointcloud_viewer>/../.."
            -always-overwrite
            COMMENT "Running macdeployqt..."
            )
endif ()
