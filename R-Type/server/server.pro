TEMPLATE		=	app
TARGET			=	server
QT			+=	core network
CONFIG			+=	console

DESTDIR			=	build
OBJECTS_DIR		=	build/obj
MOC_DIR			=	build/moc
UI_DIR			=	build/ui
RCC_DIR			=	build/rcc

win32:QMAKE_CXXFLAGS	+=	-Wall /MP
unix:QMAKE_CXXFLAGS	+=	-Wall -std=c++11 -g -Wno-write-strings

INCLUDEPATH		+=	.			\
				includes		\
				../shared/includes	\
				dependencies/includes	\
				build			\
				build/ui		\
				build/moc

HEADERS			+=

SOURCES			+=	sources/main.cpp

win32:LIBS		+=
unix:LIBS		+=
