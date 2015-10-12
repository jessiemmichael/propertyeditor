# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(StringListProperty)

include_directories(BEFORE "${CMAKE_SOURCE_DIR}/lib" )

set(StringList_SRCS stringlist.cpp  stringlisteditor.cpp)
QT5_WRAP_CPP(StringList_SRCS stringlisteditor.h  stringlist.h)
QT5_WRAP_UI(StringList_SRCS stringlisteditor.ui)
QT5_ADD_RESOURCES(StringList_SRCS stringlist.qrc)

add_library(StringListProperty SHARED ${StringList_SRCS})
add_dependencies(StringListProperty PropertyEditor)
link_directories( "${CMAKE_BINARY_DIR}/lib" )
target_link_libraries(StringListProperty PropertyEditor ${Qt5Widgets_LIBRARIES}
        ${Qt5Core_LIBRARIES} )

install(TARGETS StringListProperty ${INSTALL_PLUGINS_DEFAULT_ARGS})
