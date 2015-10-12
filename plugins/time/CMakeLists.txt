# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(TimeProperty)

include_directories(BEFORE "${CMAKE_SOURCE_DIR}/lib" )

set(Time_SRCS timeprop.cpp)
QT5_WRAP_CPP(Time_SRCS timeprop.h)

add_library(TimeProperty SHARED ${Time_SRCS})
add_dependencies(TimeProperty PropertyEditor)
link_directories( "${CMAKE_BINARY_DIR}/lib" )
target_link_libraries(TimeProperty PropertyEditor ${Qt5Widgets_LIBRARIES}
        ${Qt5Core_LIBRARIES} )

install(TARGETS TimeProperty ${INSTALL_PLUGINS_DEFAULT_ARGS})
