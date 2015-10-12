# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(propertyEditor)

set(PE_SRCS propertydelegate.cpp  propertyeditor.cpp  propertyinterface.cpp  propertymodel.cpp)
QT5_WRAP_CPP(PE_SRCS propertydelegate.h  propertyeditor.h  propertyinterface.h  propertymodel.h propertyvalidator.h)

if (WIN32)
  add_definitions(-DLIB_EXPORTS)
endif(WIN32)

add_library(PropertyEditor SHARED ${PE_SRCS})
set_target_properties(PropertyEditor PROPERTIES	SOVERSION "${PROPERTYEDITOR_VERSION_MAJOR}.${PROPERTYEDITOR_VERSION_MINOR}"
                                                VERSION ${PROPERTYEDITOR_VERSION})
target_link_libraries(PropertyEditor ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} )

install(TARGETS PropertyEditor ${INSTALL_TARGETS_DEFAULT_ARGS} )
install(FILES propertydelegate.h propertyeditor.h propertyinterface.h propertymodel.h propertyvalidator.h DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT Devel)
