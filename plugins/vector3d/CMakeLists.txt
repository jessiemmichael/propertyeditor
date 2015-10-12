# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(Vector3DProperty)

include_directories(BEFORE "${CMAKE_SOURCE_DIR}/lib" )

set(Vector3D_SRCS vector3d.cpp)
QT5_WRAP_CPP(Vector3D_SRCS vector3d.h)


add_library(Vector3DProperty SHARED ${Vector3D_SRCS})
add_dependencies(Vector3DProperty PropertyEditor)
link_directories( "${CMAKE_BINARY_DIR}/lib" )
target_link_libraries(Vector3DProperty PropertyEditor ${Qt5Widgets_LIBRARIES}
        ${Qt5Core_LIBRARIES} )

install(TARGETS Vector3DProperty ${INSTALL_PLUGINS_DEFAULT_ARGS})
