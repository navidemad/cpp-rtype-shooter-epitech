TEMPLATE		=	app
TARGET			=	server
QT     			-= 	gui core network
LIBS   			-= 	-lQtGui -lQtCore
CONFIG			+=	console

DESTDIR			=	build
OBJECTS_DIR		=	build/obj
MOC_DIR			=	build/moc
UI_DIR			=	build/ui
RCC_DIR			=	build/rcc

win32:QMAKE_CXXFLAGS	+=	-Wall /MP
unix:QMAKE_CXXFLAGS		+=	-Wall -Wextra -pedantic -std=c++11 -Wno-write-strings

QMAKE_CXXFLAGS  -= -O2
QMAKE_CXXFLAGS  -= -O1
QMAKE_CXXFLAGS  -= -O2
QMAKE_CXXFLAGS  -= -O1
win32:QMAKE_CXXFLAGS  += /O2
unix:QMAKE_CXXFLAGS  += -Ofast

INCLUDEPATH		+=	.														\
				includes													\
				includes/Network 											\
				includes/Exceptions											\
				includes/Mutex												\
				includes/Thread												\
				includes/CondVar											\
				includes/Game                  								\
				includes/Script                								\
				includes/Readdir											\
				../shared/includes/Exceptions   							\
				../shared/includes/DynLib									\
				../shared/includes											\
				../shared/includes/Network									\
				../shared/includes/Commands									\
				../shared/includes/Error       								\
				dependencies/includes										\
				build														\
				build/ui													\
				build/moc

HEADERS			+=	includes/RTypeServer.hpp								\
				includes/Exceptions/MutexException.hpp						\
				includes/Exceptions/SocketException.hpp						\
				includes/Exceptions/ThreadException.hpp						\
				includes/Exceptions/CondVarException.hpp					\
				includes/Exceptions/GameException.hpp						\
				includes/Exceptions/ScriptException.hpp						\
				includes/Exceptions/GamesManagerException.hpp				\
				../shared/includes/Config.hpp								\
				../shared/includes/Utils.hpp    							\
				../shared/includes/IResource.hpp							\
				../shared/includes/NoCopyable.hpp							\
				../shared/includes/Exceptions/DynLibException.hpp			\
				../shared/includes/DynLib/IDynLib.hpp						\
				../shared/includes/Network/IClientSocket.hpp				\
				../shared/includes/Network/IServerSocket.hpp				\
				../shared/includes/Network/Peer.hpp							\
				../shared/includes/Commands/ICommand.hpp					\
				../shared/includes/Commands/CommandCreateGame.hpp			\
				../shared/includes/Commands/CommandDeleteGame.hpp			\
				../shared/includes/Commands/CommandDestroyResource.hpp		\
				../shared/includes/Commands/CommandEndGame.hpp				\
				../shared/includes/Commands/CommandError.hpp				\
				../shared/includes/Commands/CommandFire.hpp					\
				../shared/includes/Commands/CommandHandshake.hpp			\
				../shared/includes/Commands/CommandJoinGame.hpp				\
				../shared/includes/Commands/CommandLeaveGame.hpp			\
				../shared/includes/Commands/CommandListGames.hpp			\
				../shared/includes/Commands/CommandListLevels.hpp			\
				../shared/includes/Commands/CommandMove.hpp					\
				../shared/includes/Commands/CommandMoveResource.hpp			\
				../shared/includes/Commands/CommandObserveGame.hpp			\
				../shared/includes/Commands/CommandShowGame.hpp				\
				../shared/includes/Commands/CommandShowLevel.hpp			\
				../shared/includes/Commands/CommandTimeElapsedPing.hpp		\
				../shared/includes/Commands/CommandUpdatePseudo.hpp			\
				../shared/includes/Commands/CommandUpdateScore.hpp			\
				../shared/includes/Commands/ClientPacketBuilder.hpp			\
				../shared/includes/Commands/PlayerPacketBuilder.hpp			\
				../shared/includes/Commands/CommandFactory.hpp				\
				../shared/includes/Commands/CommandException.hpp			\
				../shared/includes/Error/ErrorStatus.hpp					\
				includes/Default.hpp										\
				includes/Mutex/IMutex.hpp									\
				includes/Mutex/ScopedLock.hpp								\
				includes/CondVar/ICondVar.hpp								\
				includes/Readdir/IReaddir.hpp								\
				includes/Network/NetworkManager.hpp     					\
				includes/Network/PlayerCommunicationManager.hpp				\
				includes/Network/ClientManager.hpp							\
				includes/Network/Client.hpp									\
				includes/Thread/IThread.hpp									\
				includes/Thread/ThreadPool.hpp								\
				includes/PortabilityBuilder.hpp								\
				includes/Script/Script.hpp									\
				includes/Script/ScriptLoader.hpp							\
				includes/Script/ScriptParser.hpp							\
				includes/Script/Parser.hpp									\
				includes/Script/IScriptCommand.hpp							\
				includes/Game/NGame.hpp 									\
				includes/Game/Game.hpp 										\
				includes/Game/Manager.hpp 									\
				includes/Game/Timer.hpp										\
				includes/Game/Properties.hpp								\
				includes/Game/User.hpp										\
				includes/Game/Component.hpp

UNIX:HEADERS	+=	../shared/includes/DynLib/UnixDynLib.hpp				\
				includes/Mutex/UnixMutex.hpp								\
				includes/Network/UnixTcpClient.hpp							\
				includes/Network/UnixTcpServer.hpp							\
				includes/Network/UnixUdpClient.hpp							\
				includes/CondVar/UnixCondVar.hpp 							\
				includes/Thread/UnixThread.hpp 								\
				includes/Readdir/UnixReaddir.hpp							\
				includes/UnixPortabilityBuilder.hpp

win32:HEADERS	+=	../shared/includes/DynLib/WindowsDynLib.hpp				\
				includes/Mutex/WindowsMutex.hpp								\
				includes/Network/WindowsTcpClient.hpp						\
				includes/Network/WindowsTcpServer.hpp						\
				includes/Network/WindowsUdpClient.hpp						\
				includes/Network/WindowsWSAHandler.hpp 						\
				includes/CondVar/WindowsCondVar.hpp 						\
				includes/Thread/WindowsThread.hpp 							\
				includes/Readdir/WindowsReaddir.hpp							\
				includes/WindowsPortabilityBuilder.hpp

SOURCES			+=	sources/main.cpp										\
                sources/RTypeServer.cpp 									\
				../shared/sources/Utils.cpp									\
				../shared/sources/Error/ErrorStatus.cpp						\
				../shared/sources/Commands/ICommand.cpp        				\
				../shared/sources/Commands/CommandFactory.cpp				\
				../shared/sources/Commands/ClientPacketBuilder.cpp			\
				../shared/sources/Commands/SharedPlayerPacketBuilder.cpp	\
				../shared/sources/Commands/SharedCommandCreateGame.cpp		\
				../shared/sources/Commands/SharedCommandDeleteGame.cpp		\
				../shared/sources/Commands/SharedCommandDestroyResource.cpp	\
				../shared/sources/Commands/SharedCommandEndGame.cpp			\
				../shared/sources/Commands/SharedCommandError.cpp			\
				../shared/sources/Commands/SharedCommandFire.cpp			\
				../shared/sources/Commands/SharedCommandHandshake.cpp		\
				../shared/sources/Commands/SharedCommandJoinGame.cpp		\
				../shared/sources/Commands/SharedCommandLeaveGame.cpp		\
				../shared/sources/Commands/SharedCommandListGames.cpp		\
				../shared/sources/Commands/SharedCommandListLevels.cpp		\
				../shared/sources/Commands/SharedCommandMove.cpp			\
				../shared/sources/Commands/SharedCommandMoveResource.cpp	\
				../shared/sources/Commands/SharedCommandObserveGame.cpp		\
				../shared/sources/Commands/SharedCommandShowGame.cpp		\
				../shared/sources/Commands/SharedCommandShowLevel.cpp		\
				../shared/sources/Commands/SharedCommandTimeElapsedPing.cpp	\
				../shared/sources/Commands/SharedCommandUpdatePseudo.cpp	\
				../shared/sources/Commands/SharedCommandUpdateScore.cpp		\
				sources/Network/NetworkManager.cpp							\
				sources/Mutex/ScopedLock.cpp            					\
				sources/Thread/ThreadPool.cpp								\
				sources/Network/ClientManager.cpp							\
				sources/Network/Client.cpp									\
				sources/Network/PlayerPacketBuilder.cpp 					\
				sources/Network/PlayerCommunicationManager.cpp				\
				sources/Commands/CommandCreateGame.cpp						\
				sources/Commands/CommandDeleteGame.cpp						\
				sources/Commands/CommandDestroyResource.cpp					\
				sources/Commands/CommandEndGame.cpp							\
				sources/Commands/CommandError.cpp							\
				sources/Commands/CommandFire.cpp							\
				sources/Commands/CommandHandshake.cpp						\
				sources/Commands/CommandJoinGame.cpp						\
				sources/Commands/CommandLeaveGame.cpp						\
				sources/Commands/CommandListGames.cpp						\
				sources/Commands/CommandListLevels.cpp						\
				sources/Commands/CommandMove.cpp							\
				sources/Commands/CommandMoveResource.cpp					\
				sources/Commands/CommandObserveGame.cpp						\
				sources/Commands/CommandShowGame.cpp						\
				sources/Commands/CommandShowLevel.cpp						\
				sources/Commands/CommandTimeElapsedPing.cpp					\
				sources/Commands/CommandUpdatePseudo.cpp					\
				sources/Commands/CommandUpdateScore.cpp 					\
				sources/Script/Script.cpp 									\
				sources/Script/ScriptLoader.cpp 							\
				sources/Script/ScriptParser.cpp								\
				sources/Script/Parser.cpp									\
				sources/Game/Game.cpp 										\
				sources/Game/Manager.cpp 									\
				sources/Game/Properties.cpp									\
				sources/Game/Timer.cpp										\
				sources/Game/User.cpp										\
				sources/Game/Component.cpp

unix:SOURCES		+=	../shared/sources/DynLib/UnixDynLib.cpp				\
				sources/Network/UnixTcpClient.cpp							\
				sources/Network/UnixTcpServer.cpp							\
				sources/Network/UnixUdpClient.cpp							\
				sources/CondVar/UnixCondVar.cpp 							\
				sources/Mutex/UnixMutex.cpp 								\
				sources/Readdir/UnixReaddir.cpp								\
				sources/UnixPortabilityBuilder.cpp

win32:SOURCES		+=	../shared/sources/DynLib/WindowsDynLib.cpp			\
				sources/Network/WindowsTcpServer.cpp						\
				sources/Network/WindowsTcpClient.cpp						\
				sources/Network/WindowsUdpClient.cpp						\
				sources/Network/WindowsWSAHandler.cpp 						\
				sources/CondVar/WindowsCondVar.cpp 							\
				sources/Mutex/WindowsMutex.cpp	 							\
				sources/Readdir/WindowsReaddir.cpp							\
				sources/WindowsPortabilityBuilder.cpp

win32:LIBS	+= -lWs2_32
unix:LIBS	+= -lpthread -ldl -lm

win32: DEFINES += __OS_WINDOWS__ _CRT_SECURE_NO_WARNINGS _WINSOCK_DEPRECATED_NO_WARNINGS
unix : DEFINES += __OS_LINUX__
#DEFINES        += _DEBUG
