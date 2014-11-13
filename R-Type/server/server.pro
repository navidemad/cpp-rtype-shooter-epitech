TEMPLATE		=	app
TARGET			=	server
QT					+=	core network
CONFIG			+=	console c++11

DESTDIR			=	build
OBJECTS_DIR	=	build/obj
MOC_DIR			=	build/moc
UI_DIR			=	build/ui
RCC_DIR			=	build/rcc

win32:QMAKE_CXXFLAGS	+=	-Wall /O2 /arch:SSE2 /fp:fast /MP
unix:QMAKE_CXXFLAGS		+=	-Wall -std=c++11 -g -Wno-write-strings

INCLUDEPATH			+=	.											\
										includes							\
										includes/Network 			\
										includes/Exceptions		\
										../shared/includes		\
										dependencies/includes	\
										build									\
										build/ui							\
										build/moc

HEADERS				+=	includes/Network/NetworkManager.hpp					\
									includes/Exceptions/SocketException.hpp			\
								../shared/includes/Thread/IThread.hpp					\
								../shared/includes/Thread/Thread.hpp

unix:HEADERS	+=	includes/Network/UnixTcpClient.hpp					\
									includes/Network/UnixTcpServer.hpp					\
									includes/Network/UnixUdpClient.hpp					\
									../shared/includes/Thread/ThreadUnix.hpp

win32:HEADERS	+=	includes/Network/WindowsTcpServer.hpp				\
									includes/Network/WindowsTcpClient.hpp				\
									includes/Network/WindowsUdpClient.hpp				\
									../shared/includes/Thread/ThreadWindows.hpp

SOURCES				+=	sources/main.cpp														\
									sources/Network/NetworkManager.cpp

unix:SOURCES	+=	sources/Network/UnixTcpClient.cpp						\
									sources/Network/UnixTcpServer.cpp						\
									sources/Network/UnixUdpClient.cpp						\
									../shared/sources/Thread/ThreadUnix.cpp

win32:SOURCES	+=	sources/Network/WindowsTcpServer.cpp				\
									sources/Network/WindowsTcpClient.cpp				\
									sources/Network/WindowsUdpClient.cpp				\
									../shared/sources/Thread/ThreadWindows.cpp

unix:LIBS			+= 
win32:LIBS		+= -L$$PWD/../shared/dependencies/libs -lpthreadVC2

win32:DEFINES	+= _WIN32_WINNT=0x0501 _CRT_SECURE_NO_WARNINGS

win32:LIBS		+=
unix:LIBS			+=
