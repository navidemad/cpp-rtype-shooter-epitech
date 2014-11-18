TEMPLATE        =       app
TARGET          =       client
QT              +=      core widgets gui network
CONFIG		+=	console

DESTDIR         =       build
OBJECTS_DIR     =       build/obj
MOC_DIR         =       build/moc
UI_DIR          =       build/ui
RCC_DIR         =       build/rcc

win32:RC_ICONS 	+= 	
ICON 		= 	

win32:QMAKE_CXXFLAGS	+=	-Wall /MP
unix:QMAKE_CXXFLAGS	+=	-Wall -std=c++11 -g -Wno-write-strings

INCLUDEPATH     +=      .					\
			includes				\
			../shared/includes			\
			dependencies/includes			\
			build					\
			build/ui				\
			build/moc

HEADERS         +=      

SOURCES         +=      sources/main.cpp                        		

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system

win32:LIBS      +=      -ldependencies/libs/sfml-audio		\
			-ldependencies/libs/sfml-graphics	\
			-ldependencies/libs/sfml-main		\
			-ldependencies/libs/sfml-network	\
			-ldependencies/libs/sfml-system		\
			-ldependencies/libs/sfml-window

unix:LIBS       +=     	
