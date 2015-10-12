# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(BoolProperty)

include_directories(BEFORE "${CMAKE_SOURCE_DIR}/lib" )

set(Bool_SRCS bool.cpp)
QT5_WRAP_CPP(Bool_SRCS bool.h)
QT5_ADD_RESOURCES(Bool_SRCS resource.qrc)


add_library(BoolProperty SHARED ${Bool_SRCS})
add_dependencies(BoolProperty PropertyEditor)
link_directories( "${CMAKE_BINARY_DIR}/lib" )

target_link_libraries(BoolProperty PropertyEditor ${Qt5Widgets_LIBRARIES}
        ${Qt5Core_LIBRARIES} )

install(TARGETS BoolProperty ${INSTALL_PLUGINS_DEFAULT_ARGS})
