TEMPLATE	=	app
TARGET		=	client
QT		+=	network widgets
CONFIG		+=	console debug

DESTDIR		=	build
OBJECTS_DIR	=	build/obj
MOC_DIR		=	build/moc
UI_DIR		=	build/ui
RCC_DIR		=	build/rcc

win32:RC_ICONS 	+= assets/icon/icon.ico

win32:QMAKE_CXXFLAGS	+=	-Wall /MP
unix:QMAKE_CXXFLAGS		+=	-Wall -Wextra -pedantic -std=c++11 -Wno-write-strings

QMAKE_CXXFLAGS  -= -O2
QMAKE_CXXFLAGS  -= -O1
QMAKE_CXXFLAGS  -= -O2
QMAKE_CXXFLAGS  -= -O1
win32:QMAKE_CXXFLAGS  += /O2
unix:QMAKE_CXXFLAGS  += -Ofast

INCLUDEPATH	+=	.					\
			includes				\
			../shared/includes			\
			../shared/includes/Network		\
			../shared/includes/Commands		\
			../shared/includes/Error		\
			../shared/includes/DynLib		\
			../shared/includes/Exceptions		\
			dependencies/includes			\
			build					\
			build/ui				\
			build/moc

HEADERS		+=	../shared/includes/NoCopyable.hpp			\
			includes/RTypeClient.hpp				\
			../shared/includes/Exceptions/DynLibException.hpp			\
			../shared/includes/DynLib/IDynLib.hpp				\
			includes/PortabilityBuilder.hpp				\
			includes/Default.hpp					\
			includes/Audio/MusicManager.hpp				\
			includes/Audio/SoundManager.hpp				\
			includes/Core/DrawableSystem.hpp			\
                        includes/Core/ButtonSystem.hpp                          \
                        includes/Core/VelocitySystem.hpp			\
                        includes/Core/BackgroundSystem.hpp                          \
                        includes/Core/DrawableFontSystem.hpp			\
			includes/Core/InputManager.hpp				\
                        includes/Core/TextInputSystem.hpp			\
                        includes/Core/ListSystem.hpp                    	\
			includes/Core/System.hpp				\
			includes/Engine/Component.hpp				\
                        includes/Engine/ComponentType.h				\
                        includes/Engine/Compenent/List.hpp              	\
                        includes/Engine/Compenent/Cursor.hpp            	\
                        includes/Engine/Compenent/Button.hpp                    \
                        includes/Engine/Compenent/Drawable.hpp			\
                        includes/Engine/Compenent/Background.hpp		\
                        includes/Engine/Compenent/Velocity.hpp			\
                        includes/Engine/Compenent/TextInput.hpp			\
                        includes/Engine/Compenent/TextInput.hpp			\
			includes/Engine/ECSManager.hpp				\
                        includes/Engine/ECSManagerNetwork.hpp			\
			includes/Engine/Entity.hpp				\
                        includes/Engine/Compenent/Position.hpp			\
                        includes/Engine/Compenent/Font.hpp			\
			includes/GUI/ContentManager.hpp				\
			includes/GUI/FontManager.hpp				\
			includes/GUI/IGraphic.hpp				\
			includes/GUI/IResourceManager.hpp			\
			includes/GUI/SFMLGraphic.hpp				\
			includes/GUI/SpriteManager.hpp				\
			includes/GUI/SpriteModel.hpp				\
			includes/GUI/TextureManager.hpp				\
			includes/Network/ServerCommunication.hpp		\
			includes/Network/TcpClient.hpp				\
			includes/Network/UdpClient.hpp				\
			includes/Gameplay/Gameplay.hpp				\
			includes/Gameplay/GameplaySystem.hpp				\
			../shared/includes/Config.hpp				\
			../shared/includes/IResource.hpp			\
			../shared/includes/Network/IClientSocket.hpp		\
			../shared/includes/Network/IServerSocket.hpp		\
			../shared/includes/Commands/CommandException.hpp 	\ 							\
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
			../shared/includes/Commands/CommandUpdateScore.hpp      \
			../shared/includes/Commands/ClientPacketBuilder.hpp     \
			../shared/includes/Commands/PlayerPacketBuilder.hpp     \
			../shared/includes/Network/Peer.hpp                     \
			../shared/includes/Network/SocketException.hpp 		\
			../shared/includes/Commands/CommandFactory.hpp		\
			../shared/includes/Error/ErrorStatus.hpp

unix:HEADERS += 	includes/UnixPortabilityBuilder.hpp 			\
			../shared/includes/DynLib/UnixDynLib.hpp

win32:HEADERS += 	includes/WindowsPortabilityBuilder.hpp			\
			../shared/includes/DynLib/WindowsDynLib.hpp

SOURCES		+=	sources/main.cpp						\
			sources/RTypeClient.cpp						\
			sources/Audio/MusicManager.cpp					\
			sources/Audio/SoundManager.cpp					\
			sources/Core/DrawableSystem.cpp					\
			sources/Core/BackgroundSystem.cpp				\
                        sources/Core/VelocitySystem.cpp					\
                        sources/Core/DrawableFontSystem.cpp				\
                        sources/Core/TextInputSystem.cpp				\
                        sources/Core/ListSystem.cpp					\
                        sources/Core/ButtonSystem.cpp					\
			sources/Core/InputManager.cpp					\
			sources/Core/System.cpp						\
                        sources/Engine/Button.cpp					\
                        sources/Engine/List.cpp                 			\
                        sources/Engine/Cursor.cpp					\
			sources/Engine/Component.cpp					\
                        sources/Engine/Font.cpp                         		\
                        sources/Engine/TextInput.cpp                         		\
			sources/Engine/Drawable.cpp					\
			sources/Engine/Background.cpp					\
			sources/Engine/Velocity.cpp					\
			sources/Engine/ECSManager.cpp					\
                        sources/Engine/ECSManagerNetwork.cpp				\
			sources/Engine/Entity.cpp					\
                        sources/Engine/Position.cpp					\
			sources/GUI/ContentManager.cpp					\
			sources/GUI/FontManager.cpp					\
			sources/GUI/SFMLGraphic.cpp					\
			sources/GUI/SpriteManager.cpp					\
			sources/GUI/SpriteModel.cpp					\
			sources/GUI/TextureManager.cpp					\
			sources/Network/ServerCommunication.cpp				\
			sources/Network/TcpClient.cpp					\
			sources/Network/UdpClient.cpp 					\
			sources/Gameplay/Gameplay.cpp 					\
			sources/Gameplay/GameplaySystem.cpp 				\
                        sources/Command/PlayerPacketBuilder.cpp                         \
			../shared/sources/Commands/CommandFactory.cpp                   \
			../shared/sources/Commands/SharedPlayerPacketBuilder.cpp        \
			../shared/sources/Commands/ICommand.cpp                         \
			../shared/sources/Commands/SharedCommandCreateGame.cpp		\
			sources/Command/CommandCreateGame.cpp				\
			../shared/sources/Commands/SharedCommandDeleteGame.cpp		\
			sources/Command/CommandDeleteGame.cpp				\
			../shared/sources/Commands/SharedCommandDestroyResource.cpp	\
			sources/Command/CommandDestroyResource.cpp			\
			../shared/sources/Commands/SharedCommandEndGame.cpp		\
			sources/Command/CommandEndGame.cpp				\
			../shared/sources/Commands/SharedCommandError.cpp		\
			sources/Command/CommandError.cpp				\
			../shared/sources/Commands/SharedCommandFire.cpp		\
			sources/Command/CommandFire.cpp					\
			../shared/sources/Commands/SharedCommandHandshake.cpp		\
			sources/Command/CommandHandshake.cpp				\
			../shared/sources/Commands/SharedCommandJoinGame.cpp		\
			sources/Command/CommandJoinGame.cpp				\
			../shared/sources/Commands/SharedCommandLeaveGame.cpp		\
			sources/Command/CommandLeaveGame.cpp				\
			../shared/sources/Commands/SharedCommandListGames.cpp		\
			sources/Command/CommandListGames.cpp				\
			../shared/sources/Commands/SharedCommandListLevels.cpp		\
			sources/Command/CommandListLevels.cpp				\
			../shared/sources/Commands/SharedCommandMove.cpp		\
			sources/Command/CommandMove.cpp					\
			../shared/sources/Commands/SharedCommandMoveResource.cpp	\
			sources/Command/CommandMoveResource.cpp				\
			../shared/sources/Commands/SharedCommandObserveGame.cpp		\
			sources/Command/CommandObserveGame.cpp				\
			../shared/sources/Commands/SharedCommandShowGame.cpp		\
			sources/Command/CommandShowGame.cpp				\
			../shared/sources/Commands/SharedCommandShowLevel.cpp		\
			sources/Command/CommandShowLevel.cpp				\
			../shared/sources/Commands/SharedCommandTimeElapsedPing.cpp	\
			sources/Command/CommandTimeElapsedPing.cpp			\
			../shared/sources/Commands/SharedCommandUpdatePseudo.cpp	\
			sources/Command/CommandUpdatePseudo.cpp				\
			../shared/sources/Commands/SharedCommandUpdateScore.cpp		\
                        sources/Command/CommandUpdateScore.cpp                          \
			../shared/sources/Commands/ClientPacketBuilder.cpp

unix:SOURCES		+= ../shared/sources/DynLib/UnixDynLib.cpp \
						sources/UnixPortabilityBuilder.cpp
win32:SOURCES		+= ../shared/sources/DynLib/WindowsDynLib.cpp \
						sources/WindowsPortabilityBuilder.cpp

#CONFIG(release, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main -lsfml-network-d -lsfml-window-d -lsfml-system-d
#CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system

win32:LIBS	+=	-ldependencies/libs/sfml-audio-d	\
			-ldependencies/libs/sfml-graphics-d	\
			-ldependencies/libs/sfml-main		\
			-ldependencies/libs/sfml-network-d	\
			-ldependencies/libs/sfml-system-d	\
			-ldependencies/libs/sfml-window-d

#win32:LIBS	+=	-ldependencies/libs/sfml-audio		\
#			-ldependencies/libs/sfml-graphics	\
#			-ldependencies/libs/sfml-main		\
#			-ldependencies/libs/sfml-network	\
#			-ldependencies/libs/sfml-system		\
#			-ldependencies/libs/sfml-window

unix:LIBS	+=	-lsfml-audio 		\
			-lsfml-graphics 	\
			-lsfml-network 		\
			-lsfml-window 		\
			-lsfml-system

unix:LIBS += -ldl

win32: DEFINES += __OS_WINDOWS__ _CRT_SECURE_NO_WARNINGS
unix : DEFINES += __OS_LINUX__

#CONFIG(debug, debug|release): DEFINES += _DEBUG