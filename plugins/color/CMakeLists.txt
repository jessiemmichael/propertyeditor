# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(ColorProperty)

include_directories(BEFORE "${CMAKE_SOURCE_DIR}/lib" )

set(Color_SRCS changecolor.cpp  color.cpp)
QT5_WRAP_CPP(Color_SRCS changecolor.h  color.h)


add_library(ColorProperty SHARED ${Color_SRCS})
add_dependencies(ColorProperty PropertyEditor)
link_directories( "${CMAKE_BINARY_DIR}/lib" )
target_link_libraries(ColorProperty PropertyEditor ${Qt5Widgets_LIBRARIES}
        ${Qt5Core_LIBRARIES} )

install(TARGETS ColorProperty ${INSTALL_PLUGINS_DEFAULT_ARGS})
