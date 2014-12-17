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

win32:QMAKE_CXXFLAGS	+=	-Wall /O2 /arch:SSE2 /fp:fast /MP
unix:QMAKE_CXXFLAGS	+=	-Wall -std=c++11 -g -Wno-write-strings
QMAKE_CXX = clang++
CXX = clang++

INCLUDEPATH		+=	.					\
				includes				\
				includes/Network 			\
				includes/Exceptions			\
				includes/Mutex				\
				includes/Thread				\
				includes/CondVar			\
				includes/Game			\
				includes/Script			\
				includes/Readdir			\
				includes/DynLib			\
				../shared/includes			\
				../shared/includes/Network		\
				../shared/includes/Commands		\
				../shared/includes/Script		\
                                ../shared/includes/Error                \
				dependencies/includes			\
				build					\
				build/ui				\
				build/moc

HEADERS			+=	../shared/includes/NoCopyable.hpp			\
				includes//Default.hpp							\
				includes/Exceptions/MutexException.hpp			\
				includes/Exceptions/SocketException.hpp			\
				includes/Exceptions/ThreadException.hpp			\
				includes/Exceptions/CondVarException.hpp		\
				includes/Exceptions/GameException.hpp			\
				includes/Exceptions/DynLibException.hpp			\
				includes/Exceptions/GamesManagerException.hpp		\
				includes/Mutex/ScopedLock.hpp				\
				includes/Mutex/IMutex.hpp				\
				includes/CondVar/ICondVar.hpp				\
				includes/DynLib/IDynLib.hpp				\
				includes/Readdir/IReaddir.hpp \
				includes/Network/NetworkManager.hpp     		\
				includes/Network/PlayerCommunicationManager.hpp		\
				../shared/includes/Config.hpp				\
				../shared/includes/Utils.hpp				\
				../shared/includes/Network/IClientSocket.hpp		\
				../shared/includes/Network/IServerSocket.hpp		\
                                ../shared/includes/Commands/ICommand.hpp        	\
                                ../shared/includes/Commands/CommandCreateGame.hpp	\
                                ../shared/includes/Commands/CommandDeleteGame.hpp	\
                                ../shared/includes/Commands/CommandDestroyResource.hpp	\
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
				../shared/includes/Error/ErrorStatus.hpp		\
				includes/Mutex/IMutex.hpp				\
				includes/Thread/IThread.hpp				\
				includes/Thread/ThreadPool.hpp				\
				includes/PortabilityBuilder.hpp				\
				includes/Network/ClientManager.hpp			\
				includes/Network/Client.hpp				\
				../shared/includes/Commands/ClientPacketBuilder.hpp	\
				../shared/includes/Commands/PlayerPacketBuilder.hpp	\
				../shared/includes/Commands/CommandFactory.hpp		\
				../shared/includes/Commands/CommandException.hpp	\
				../shared/includes/IResource.hpp					\
				includes/RTypeServer.hpp				\
				../shared/includes/Script/Script.hpp				\
				../shared/includes/Script/ScriptLoader.hpp			\
				../shared/includes/Script/ScriptParser.hpp			\
				../shared/includes/Script/ScriptName.hpp			\
				../shared/includes/Script/ScriptRequire.hpp			\
				../shared/includes/Script/ScriptAction.hpp			\
				../shared/includes/Script/ScriptAddCron.hpp			\
				../shared/includes/Script/ScriptRemoveCron.hpp			\
				../shared/includes/Script/ScriptException.hpp			\
				../shared/includes/Script/Parser.hpp				\
				../shared/includes/Script/IScriptCommand.hpp			\
				includes/Game/NGame.hpp 					\
				includes/Game/Game.hpp 					\
				includes/Game/GamesManager.hpp 				\
				includes/Game/GameProperties.hpp		\
				includes/Game/GameUser.hpp		\
				includes/Game/GameComponent.hpp		\
				includes/Game/GamesManager.hpp 				\
				includes/Game/Timer.hpp								\
				../shared/includes/Network/Peer.hpp

unix:HEADERS		+=	includes/Mutex/UnixMutex.hpp				\
				includes/Network/UnixTcpClient.hpp			\
				includes/Network/UnixTcpServer.hpp			\
				includes/Network/UnixUdpClient.hpp			\
				includes/CondVar/UnixCondVar.hpp 			\
				includes/Thread/UnixThread.hpp 				\
				includes/DynLib/UnixDynLib.hpp				\
				includes/Readdir/UnixReaddir.hpp				\
				includes/UnixPortabilityBuilder.hpp

win32:HEADERS		+=	includes/Mutex/WindowsMutex.hpp				\
				includes/Network/WindowsTcpClient.hpp			\
				includes/Network/WindowsTcpServer.hpp			\
				includes/Network/WindowsUdpClient.hpp			\
				includes/Network/WindowsWSAHandler.hpp 			\
				includes/CondVar/WindowsCondVar.hpp 			\
				includes/Thread/WindowsThread.hpp 			\
				includes/DynLib/WindowsDynLib.hpp				\
				includes/Readdir/WindowsReaddir.hpp				\
				includes/WindowsPortabilityBuilder.hpp

SOURCES			+=	sources/main.cpp						\
				sources/Network/NetworkManager.cpp				\
				sources/Mutex/ScopedLock.cpp            			\
				sources/Thread/ThreadPool.cpp					\
                                ../shared/sources/Error/ErrorStatus.cpp				\
				sources/Network/ClientManager.cpp				\
				sources/Network/Client.cpp					\
				sources/Network/PlayerPacketBuilder.cpp 	\
				../shared/sources/Commands/ClientPacketBuilder.cpp		\
				../shared/sources/Commands/SharedPlayerPacketBuilder.cpp		\
				sources/Network/PlayerCommunicationManager.cpp			\
				../shared/sources/Utils.cpp					\
				../shared/sources/Commands/CommandFactory.cpp			\
                                ../shared/sources/Commands/ICommand.cpp        			\
                                ../shared/sources/Commands/SharedCommandCreateGame.cpp		\
                                ../shared/sources/Commands/SharedCommandDeleteGame.cpp		\
                                ../shared/sources/Commands/SharedCommandDestroyResource.cpp	\
                                ../shared/sources/Commands/SharedCommandEndGame.cpp		\
                                ../shared/sources/Commands/SharedCommandError.cpp		\
                                ../shared/sources/Commands/SharedCommandFire.cpp		\
                                ../shared/sources/Commands/SharedCommandHandshake.cpp		\
                                ../shared/sources/Commands/SharedCommandJoinGame.cpp		\
                                ../shared/sources/Commands/SharedCommandLeaveGame.cpp		\
                                ../shared/sources/Commands/SharedCommandListGames.cpp		\
                                ../shared/sources/Commands/SharedCommandListLevels.cpp		\
                                ../shared/sources/Commands/SharedCommandMove.cpp		\
                                ../shared/sources/Commands/SharedCommandMoveResource.cpp	\
                                ../shared/sources/Commands/SharedCommandObserveGame.cpp		\
                                ../shared/sources/Commands/SharedCommandShowGame.cpp		\
                                ../shared/sources/Commands/SharedCommandShowLevel.cpp		\
                                ../shared/sources/Commands/SharedCommandTimeElapsedPing.cpp	\
                                ../shared/sources/Commands/SharedCommandUpdatePseudo.cpp	\
                                ../shared/sources/Commands/SharedCommandUpdateScore.cpp		\
                                sources/Commands/CommandCreateGame.cpp				\
                                sources/Commands/CommandDeleteGame.cpp				\
                                sources/Commands/CommandDestroyResource.cpp			\
                                sources/Commands/CommandEndGame.cpp				\
                                sources/Commands/CommandError.cpp				\
                                sources/Commands/CommandFire.cpp				\
                                sources/Commands/CommandHandshake.cpp				\
                                sources/Commands/CommandJoinGame.cpp				\
                                sources/Commands/CommandLeaveGame.cpp				\
                                sources/Commands/CommandListGames.cpp				\
                                sources/Commands/CommandListLevels.cpp				\
                                sources/Commands/CommandMove.cpp				\
                                sources/Commands/CommandMoveResource.cpp			\
                                sources/Commands/CommandObserveGame.cpp				\
                                sources/Commands/CommandShowGame.cpp				\
                                sources/Commands/CommandShowLevel.cpp				\
                                sources/Commands/CommandTimeElapsedPing.cpp			\
                                sources/Commands/CommandUpdatePseudo.cpp			\
                                sources/Commands/CommandUpdateScore.cpp 			\
                                sources/RTypeServer.cpp 					\
                                ../shared/sources/Script/Script.cpp 					\
                                ../shared/sources/Script/ScriptLoader.cpp 				\
                                ../shared/sources/Script/ScriptParser.cpp					\
								../shared/sources/Script/Parser.cpp						\
				sources/Game/Game.cpp 						\
				sources/Game/GamesManager.cpp 					\
				sources/Game/Timer.cpp

unix:SOURCES		+=	sources/Network/UnixTcpClient.cpp			\
				sources/Network/UnixTcpServer.cpp			\
				sources/Network/UnixUdpClient.cpp			\
				sources/CondVar/UnixCondVar.cpp 			\
				sources/Mutex/UnixMutex.cpp 				\
				sources/DynLib/UnixDynLib.cpp				\
				sources/Readdir/UnixReaddir.cpp				\
				sources/UnixPortabilityBuilder.cpp

win32:SOURCES		+=	sources/Network/WindowsTcpServer.cpp			\
				sources/Network/WindowsTcpClient.cpp			\
				sources/Network/WindowsUdpClient.cpp			\
				sources/Network/WindowsWSAHandler.cpp 			\
				sources/CondVar/WindowsCondVar.cpp 			\
				sources/Mutex/WindowsMutex.cpp	 			\
				sources/DynLib/WindowsDynLib.cpp			\
				sources/Readdir/WindowsReaddir.cpp				\
				sources/WindowsPortabilityBuilder.cpp

win32:LIBS	+= -lWs2_32
unix:LIBS	+= -lpthread -ldl -lm

win32: DEFINES += __OS_WINDOWS__ _CRT_SECURE_NO_WARNINGS _WINSOCK_DEPRECATED_NO_WARNINGS
unix : DEFINES += __OS_LINUX__
DEFINES        += _DEBUG
