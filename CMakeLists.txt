cmake_minimum_required(VERSION 3.16)

project(work5_qq_cmake VERSION 0.1 LANGUAGES CXX)

# set(QT_PATH "F:/Qt/6.8.3/msvc2022_64")
# set(QT_PATH "F:/Qt/6.8.3/mingw_64")
# set(CMAKE_PREFIX_PATH ${QT_PATH})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找所有必需的 Qt 模块
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
    Sql
    Multimedia
    LinguistTools
    MultimediaWidgets
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
    Sql
    Multimedia
    LinguistTools
    MultimediaWidgets
)

set(TS_FILES work5_qq_cmake_zh_CN.ts)

# 主项目源文件
set(PROJECT_SOURCES
    abstractthread.cpp
    appupdater.cpp
    chatpreviewbutton.cpp
    groupdetail.cpp
    main.cpp
    mainwindow.cpp
    myhintpushbutton.cpp
    profile.cpp
    redpointbutton.cpp
    roundlabel.cpp
    setdialog.cpp
    sqlqueryfactory.cpp
    userdetail.cpp
    userpatcher.cpp
    userpatcherfactory.cpp
    filesenderthread.cpp
    videoencoder.cpp
    videodecoder.cpp

    abstractthread.h
    appupdater.h
    chatpreviewbutton.h
    groupdetail.h
    macro.h
    mainwindow.h
    myhintpushbutton.h
    profile.h
    redpointbutton.h
    roundlabel.h
    setdialog.h
    sqlqueryfactory.h
    userdetail.h
    userpatcher.h
    userpatcherfactory.h
    filesenderthread.h
    videoencoder.h
    videodecoder.h

    groupdetail.ui
    mainwindow.ui
    userdetail.ui

    res.qrc
)

# 添加子模块源文件
file(GLOB emotion_widget_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/emotion_widget/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/emotion_widget/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/emotion_widget/*.ui"
)
file(GLOB camera_widget_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/camera_widget/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/camera_widget/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/camera_widget/*.ui"
)
file(GLOB chat_widget_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/chat_widget/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/chat_widget/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/chat_widget/*.ui"
)
file(GLOB login_widget_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/login_widget/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/login_widget/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/login_widget/*.ui"
)

# 合并所有源文件
list(APPEND PROJECT_SOURCES
    ${emotion_widget_sources}
    ${camera_widget_sources}
    ${chat_widget_sources}
    ${login_widget_sources}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(work5_qq_cmake
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    # 添加包含目录
    target_include_directories(work5_qq_cmake PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/emotion_widget
        ${CMAKE_CURRENT_SOURCE_DIR}/camera_widget
        ${CMAKE_CURRENT_SOURCE_DIR}/chat_widget
        ${CMAKE_CURRENT_SOURCE_DIR}/login_widget
    )

    # 创建翻译文件
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(work5_qq_cmake SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(work5_qq_cmake
            ${PROJECT_SOURCES}
        )
    endif()

    # 添加包含目录
    target_include_directories(work5_qq_cmake PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/emotion_widget
        ${CMAKE_CURRENT_SOURCE_DIR}/camera_widget
        ${CMAKE_CURRENT_SOURCE_DIR}/chat_widget
        ${CMAKE_CURRENT_SOURCE_DIR}/login_widget
    )

    # 创建翻译文件
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# 链接所有必需的 Qt 模块
target_link_libraries(work5_qq_cmake PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.work5_qq_cmake)
endif()
set_target_properties(work5_qq_cmake PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 设置应用程序图标（Windows）
if(WIN32)
   # 添加图标文件到资源
   set(ICON_FILE ${CMAKE_CURRENT_SOURCE_DIR}/chat.ico)
   if(EXISTS ${ICON_FILE})
       set_source_files_properties(${ICON_FILE} PROPERTIES MACOSX_PICTURE_RESOURCE TRUE)
       target_sources(work5_qq_cmake PRIVATE ${ICON_FILE})
   endif()
endif()

include(GNUInstallDirs)
install(TARGETS work5_qq_cmake
   BUNDLE DESTINATION .
   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)



set(FFMPEG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/ffmpeg")

target_include_directories(work5_qq_cmake PRIVATE "${FFMPEG_DIR}/include")

find_library(AVCODEC_LIB NAMES avcodec PATHS "${FFMPEG_DIR}/lib" NO_DEFAULT_PATH)
find_library(AVUTIL_LIB NAMES avutil PATHS "${FFMPEG_DIR}/lib" NO_DEFAULT_PATH)
find_library(SWSCALE_LIB NAMES swscale PATHS "${FFMPEG_DIR}/lib" NO_DEFAULT_PATH)

target_link_libraries(work5_qq_cmake PRIVATE
    ${AVCODEC_LIB}
    ${AVUTIL_LIB}
    ${SWSCALE_LIB}
)

if(QT_VERSION_MAJOR EQUAL 6)
   qt_finalize_executable(work5_qq_cmake)
endif()
