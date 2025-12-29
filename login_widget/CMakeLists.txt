# login_widget/CMakeLists.txt
add_library(login_widget STATIC
    loadwidget.cpp
    loginwidget.cpp
    loginwidget.ui
)

# 头文件（用于MOC）
set_property(TARGET login_widget PROPERTY AUTOMOC ON)
set_property(TARGET login_widget PROPERTY AUTOUIC ON)

# 包含目录
target_include_directories(login_widget PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 链接Qt库
if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(login_widget PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
    )
else()
    target_link_libraries(login_widget PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
    )
endif()