TEMPLATE = lib

CONFIG += exceptions \
dll \
plugin \
  rtti

HEADERS += vector3d.h 

SOURCES += vector3d.cpp 

TARGET = Vector3DProperty

DESTDIR = .

INCLUDEPATH += $$[PROPERTY_EDITOR_INSTALL_HEADERS]

macx{
	QMAKE_LFLAGS +=  -F$$[PROPERTY_EDITOR_INSTALL_LIBS]
 	LIBS += -framework PropertyEditor
}else{
	LIBS += -L$$[PROPERTY_EDITOR_INSTALL_LIBS] -lPropertyEditor 
}

target.path = $$[PROPERTY_EDITOR_INSTALL_PLUGINS]/propertyEditor

INSTALLS += target

