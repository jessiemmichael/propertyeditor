# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(SizeProperty)

include_directories(BEFORE "${CMAKE_SOURCE_DIR}/lib" )

set(Size_SRCS size.cpp)
QT5_WRAP_CPP(Size_SRCS size.h)

add_library(SizeProperty SHARED ${Size_SRCS})
add_dependencies(SizeProperty PropertyEditor)
link_directories( "${CMAKE_BINARY_DIR}/lib" )
target_link_libraries(SizeProperty PropertyEditor ${Qt5Widgets_LIBRARIES}
        ${Qt5Core_LIBRARIES} )

install(TARGETS SizeProperty ${INSTALL_PLUGINS_DEFAULT_ARGS})
