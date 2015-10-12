# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(DateProperty)

include_directories(BEFORE "${CMAKE_SOURCE_DIR}/lib" )

set(Date_SRCS date.cpp)
QT5_WRAP_CPP(Date_SRCS date.h)

add_library(DateProperty SHARED ${Date_SRCS})
add_dependencies(DateProperty PropertyEditor)
link_directories( "${CMAKE_BINARY_DIR}/lib" )
target_link_libraries(DateProperty PropertyEditor ${Qt5Widgets_LIBRARIES}
        ${Qt5Core_LIBRARIES} )

install(TARGETS DateProperty ${INSTALL_PLUGINS_DEFAULT_ARGS})
