TEMPLATE		=	app
TARGET			=	server
QT			+=	core network
CONFIG		+=	console

DESTDIR			=	build
OBJECTS_DIR		=	build/obj
MOC_DIR			=	build/moc
UI_DIR			=	build/ui
RCC_DIR			=	build/rcc

win32:QMAKE_CXXFLAGS	+=	-Wall /O2 /arch:SSE2 /fp:fast /MP
unix:QMAKE_CXXFLAGS	+=	-Wall -std=c++11 -g -Wno-write-strings
unix:QMAKE_CXX = clang++
INCLUDEPATH		+=	.					\
				includes				\
				includes/Network 			\
				includes/Exceptions			\
				includes/Mutex				\
				includes/Thread				\
				includes/CondVar			\
				../shared/includes			\
				../shared/includes/Network		\
				../shared/includes/Commands		\
                                ../shared/includes/Error                \
				dependencies/includes			\
				build					\
				build/ui				\
				build/moc

HEADERS			+=	includes/Exceptions/MutexException.hpp			\
				includes/Exceptions/SocketException.hpp			\
				includes/Exceptions/ThreadException.hpp			\
				includes/Exceptions/CondVarException.hpp		\
				includes/Mutex/ScopedLock.hpp				\
				includes/Mutex/IMutex.hpp				\
				includes/CondVar/ICondVar.hpp				\
				includes/Network/NetworkManager.hpp     		\
				../shared/includes/Config.hpp		\
				../shared/includes/Network/IClientSocket.hpp		\
				../shared/includes/Network/IServerSocket.hpp		\
                                ../shared/includes/Commands/ICommand.hpp        	\
                                ../shared/includes/Commands/CommandCreateGame.hpp	\
                                ../shared/includes/Commands/CommandDeleteGame.hpp	\
                                ../shared/includes/Commands/CommandDestroyResource.hpp	\
                                ../shared/includes/Commands/CommandDisconnect.hpp	\
                                ../shared/includes/Commands/CommandEndGame.hpp		\
                                ../shared/includes/Commands/CommandError.hpp		\
                                ../shared/includes/Commands/CommandFire.hpp		\
                                ../shared/includes/Commands/CommandHandshake.hpp	\
                                ../shared/includes/Commands/CommandJoinGame.hpp		\
                                ../shared/includes/Commands/CommandLeaveGame.hpp	\
                                ../shared/includes/Commands/CommandListGames.hpp	\
                                ../shared/includes/Commands/CommandListLevels.hpp	\
                                ../shared/includes/Commands/CommandMove.hpp		\
                                ../shared/includes/Commands/CommandMoveResource.hpp	\
                                ../shared/includes/Commands/CommandObserveGame.hpp	\
                                ../shared/includes/Commands/CommandShowGame.hpp		\
                                ../shared/includes/Commands/CommandShowLevel.hpp	\
                                ../shared/includes/Commands/CommandTimeElapsedPing.hpp	\
                                ../shared/includes/Commands/CommandUpdatePseudo.hpp	\
                                ../shared/includes/Commands/CommandUpdateScore.hpp	\
				includes/Mutex/IMutex.hpp				\
				includes/Thread/IThread.hpp				\
				includes/Thread/ThreadPool.hpp				\
				includes/PortabilityBuilder.hpp				\
				includes/Observer.hpp

unix:HEADERS		+=	includes/Mutex/UnixMutex.hpp		\
				includes/Network/UnixTcpClient.hpp	\
				includes/Network/UnixTcpServer.hpp	\
				includes/Network/UnixUdpClient.hpp	\
				includes/CondVar/UnixCondVar.hpp \
				includes/Thread/UnixThread.hpp \
				includes/UnixPortabilityBuilder.hpp

win32:HEADERS		+=	includes/Mutex/WindowsMutex.hpp		\
				includes/Network/WindowsTcpClient.hpp	\
				includes/Network/WindowsTcpServer.hpp	\
				includes/Network/WindowsUdpClient.hpp	\
				includes/Network/WindowsWSAHandler.hpp \
				includes/CondVar/WindowsCondVar.hpp \
				includes/Thread/WindowsThread.hpp \
				includes/WindowsPortabilityBuilder.hpp

SOURCES			+=	sources/main.cpp			\
				sources/Network/NetworkManager.cpp	\
				sources/Mutex/ScopedLock.cpp            \
				sources/Thread/ThreadPool.cpp		\
                                ../shared/sources/Error/ErrorStatus.cpp

unix:SOURCES		+=	sources/Network/UnixTcpClient.cpp	\
				sources/Network/UnixTcpServer.cpp	\
				sources/Network/UnixUdpClient.cpp	\
				sources/CondVar/UnixCondVar.cpp \
				sources/Mutex/UnixMutex.cpp \
				sources/UnixPortabilityBuilder.cpp

win32:SOURCES		+=	sources/Network/WindowsTcpServer.cpp	\
				sources/Network/WindowsTcpClient.cpp	\
				sources/Network/WindowsUdpClient.cpp	\
				sources/Network/WindowsWSAHandler.cpp \
				sources/CondVar/WindowsCondVar.cpp \
				sources/Mutex/WindowsMutex.cpp \
				sources/WindowsPortabilityBuilder.cpp

win32:LIBS	+= -lWs2_32
unix:LIBS	+= -lpthread

win32:DEFINES	+= _CRT_SECURE_NO_WARNINGS
