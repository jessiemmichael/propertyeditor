# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(RectProperty)

include_directories(BEFORE "${CMAKE_SOURCE_DIR}/lib" )

set(Rect_SRCS rect.cpp)
QT5_WRAP_CPP(Rect_SRCS rect.h)

add_library(RectProperty SHARED ${Rect_SRCS})
add_dependencies(RectProperty PropertyEditor)
link_directories( "${CMAKE_BINARY_DIR}/lib" )
target_link_libraries(RectProperty PropertyEditor ${Qt5Widgets_LIBRARIES}
        ${Qt5Core_LIBRARIES} )

install(TARGETS RectProperty ${INSTALL_PLUGINS_DEFAULT_ARGS})
