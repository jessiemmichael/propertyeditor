# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(RectfProperty)

include_directories(BEFORE "${CMAKE_SOURCE_DIR}/lib" )

set(Rectf_SRCS rectf.cpp)
QT5_WRAP_CPP(Rectf_SRCS rectf.h)

add_library(RectfProperty SHARED ${Rectf_SRCS})
add_dependencies(RectfProperty PropertyEditor)
link_directories( "${CMAKE_BINARY_DIR}/lib" )
target_link_libraries(RectfProperty PropertyEditor ${Qt5Widgets_LIBRARIES}
        ${Qt5Core_LIBRARIES} )

install(TARGETS RectfProperty ${INSTALL_PLUGINS_DEFAULT_ARGS})
