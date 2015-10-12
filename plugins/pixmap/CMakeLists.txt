# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(PixmapProperty)

include_directories(BEFORE "${CMAKE_SOURCE_DIR}/lib" )

set(Pixmap_SRCS pixmap.cpp  pixmapdialog.cpp)
QT5_WRAP_CPP(Pixmap_SRCS pixmapdialog.h  pixmap.h)
QT5_WRAP_UI(Pixmap_SRCS pixmapDialog.ui)

add_library(PixmapProperty SHARED ${Pixmap_SRCS})
add_dependencies(PixmapProperty PropertyEditor)
link_directories( "${CMAKE_BINARY_DIR}/lib" )
target_link_libraries(PixmapProperty PropertyEditor ${Qt5Widgets_LIBRARIES}
        ${Qt5Core_LIBRARIES} )

install(TARGETS PixmapProperty ${INSTALL_PLUGINS_DEFAULT_ARGS})
