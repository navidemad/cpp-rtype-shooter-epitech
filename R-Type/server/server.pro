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
										includes/Mutex				\
										includes/Thread				\
										../shared/includes		\
										dependencies/includes	\
										build									\
										build/ui							\
										build/moc

HEADERS				+=		includes/Exceptions/MutexException.hpp		\
										includes/Exceptions/SocketException.hpp		\
										includes/Exceptions/ThreadException.hpp		\
										includes/Mutex/ScopedLock.hpp							\
										includes/Mutex/IMutex.hpp							\
										includes/Network/NetworkManager.hpp				\
										../shared/includes/IClientSocket.hpp			\
										../shared/includes/IServerSocket.hpp			\
										includes/Mutex/IMutex.hpp							\
										includes/Thread/IThread.hpp			\
										includes/PortabilityBuilder.hpp

unix:HEADERS	+=		includes/Mutex/UnixMutex.hpp							\
										includes/Network/UnixTcpClient.hpp				\
										includes/Network/UnixTcpServer.hpp				\
										includes/Network/UnixUdpClient.hpp				\
										includes/Thread/UnixThread.hpp

win32:HEADERS	+=		includes/Mutex/WindowsMutex.hpp						\
										includes/Network/WindowsTcpClient.hpp			\
										includes/Network/WindowsTcpServer.hpp			\
										includes/Network/WindowsUdpClient.hpp			\
										includes/Thread/WindowsThread.hpp

SOURCES				+=	sources/main.cpp														\
									sources/Network/NetworkManager.cpp					\
									sources/PortabilityBuilder.cpp							\
									sources/Mutex/ScopedLock.cpp

unix:SOURCES	+=	sources/Network/UnixTcpClient.cpp						\
									sources/Network/UnixTcpServer.cpp						\
									sources/Network/UnixUdpClient.cpp						\
									sources/Mutex/UnixMutex.cpp

win32:SOURCES	+=	sources/Network/WindowsTcpServer.cpp				\
									sources/Network/WindowsTcpClient.cpp				\
									sources/Network/WindowsUdpClient.cpp				\
									sources/Mutex/WindowsMutex.cpp

unix:LIBS			+= -lpthread

win32:DEFINES	+= _WIN32_WINNT=0x0501 _CRT_SECURE_NO_WARNINGS
