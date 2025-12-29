# camera_widget/CMakeLists.txt
add_library(camera_widget STATIC
    camerawidget.cpp
    clocklabel.cpp
    pictureview.cpp
    camerawidget.ui
)

# 头文件（用于MOC）
set_property(TARGET camera_widget PROPERTY AUTOMOC ON)
set_property(TARGET camera_widget PROPERTY AUTOUIC ON)

# 包含目录
target_include_directories(camera_widget PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 链接Qt库
if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(camera_widget PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Multimedia
    )
else()
    target_link_libraries(camera_widget PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Multimedia
    )
endif()