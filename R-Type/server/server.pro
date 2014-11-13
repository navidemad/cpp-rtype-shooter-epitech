TEMPLATE		=	app
TARGET			=	server
QT				+=	core network
CONFIG			+=	console c++11

DESTDIR			=	build
OBJECTS_DIR		=	build/obj
MOC_DIR			=	build/moc
UI_DIR			=	build/ui
RCC_DIR			=	build/rcc

win32:QMAKE_CXXFLAGS	+=	-Wall /O2 /arch:SSE2 /fp:fast /MP
unix:QMAKE_CXXFLAGS		+=	-Wall -std=c++11 -g -Wno-write-strings

DEPENDPATH 		+= 		$$PWD/../shared/dependencies/

INCLUDEPATH		+=		.									\
						includes							\
						../shared/includes					\
						dependencies/includes				\
						../shared/dependencies/includes		\
						build								\
						build/ui							\
						build/moc

HEADERS			+=	../shared/dependencies/includes/pthread.h	\
					../shared/dependencies/includes/sched.h		\
					../shared/dependencies/includes/semaphore.h
					
HEADERS			+=	../shared/includes/Thread/ThreadUnix.hpp	\
					../shared/includes/Thread/ThreadWindows.hpp	\
					../shared/includes/Thread/IThread.hpp		\
					../shared/includes/Thread/Thread.hpp

SOURCES			+=	../shared/sources/Thread/ThreadUnix.cpp		\
					../shared/sources/Thread/ThreadWindows.cpp

SOURCES			+=	sources/main.cpp

LIBS			+= -L$$PWD/../shared/dependencies/libs -lpthreadVC2
unix:LIBS		+= 
win32:LIBS 		+= 

win32:DEFINES	+= _WIN32_WINNT=0x0501 _CRT_SECURE_NO_WARNINGS