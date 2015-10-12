# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(PenProperty)

include_directories(BEFORE "${CMAKE_SOURCE_DIR}/lib" )

set(Pen_SRCS pen.cpp)
QT5_WRAP_CPP(Pen_SRCS pen.h)

add_library(PenProperty SHARED ${Pen_SRCS})
add_dependencies(PenProperty PropertyEditor)
link_directories( "${CMAKE_BINARY_DIR}/lib" )
target_link_libraries(PenProperty PropertyEditor ${Qt5Widgets_LIBRARIES}
        ${Qt5Core_LIBRARIES} )

install(TARGETS PenProperty ${INSTALL_PLUGINS_DEFAULT_ARGS})
