TEMPLATE	=	app
TARGET		=	client
QT		+=	core widgets gui network
CONFIG		+=	console

DESTDIR		=	build
OBJECTS_DIR	=	build/obj
MOC_DIR		=	build/moc
UI_DIR		=	build/ui
RCC_DIR		=	build/rcc

win32:RC_ICONS 	+= 	
ICON 		= 	

win32:QMAKE_CXXFLAGS	+=	-Wall /O2 /arch:SSE2 /fp:fast /MP
unix:QMAKE_CXXFLAGS	+=	-Wall -std=c++11 -g -Wno-write-strings

INCLUDEPATH	+=	.					\
			includes				\
			../shared/includes			\
			../shared/includes/Network		\
			../shared/includes/Commands		\
			../shared/includes/Error		\
			dependencies/includes			\
			build					\
			build/ui				\
			build/moc

HEADERS		+=	includes/RTypeClient.hpp				\
			includes/Audio/SoundManager.hpp				\
			includes/Core/CollisionSystem.hpp			\
			includes/Core/DamageSystem.hpp				\
			includes/Core/DrawableSystem.hpp			\
			includes/Core/InputManager.hpp				\
			includes/Core/MovementSystem.hpp			\
			includes/Core/System.hpp				\
			includes/Engine/Collision.hpp				\
			includes/Engine/Component.hpp				\
			includes/Engine/Controllable.hpp			\
			includes/Engine/Drawable.hpp				\
			includes/Engine/ECSManager.hpp				\
			includes/Engine/Entity.hpp				\
			includes/Engine/Position.hpp				\
			includes/Engine/Script.hpp				\
			includes/GUI/ContentManager.hpp				\
			includes/GUI/FontManager.hpp				\
			includes/GUI/IGraphic.hpp				\
			includes/GUI/IResourceManager.hpp			\
			includes/GUI/SFMLGraphic.hpp				\
			includes/GUI/SpriteManager.hpp				\
			includes/GUI/SpriteModel.hpp				\
			includes/GUI/TextureManager.hpp				\
			includes/Network/INetworkManager.hpp			\
			includes/Network/CommandPacketBuilder.hpp		\
			includes/Network/INetworkManager.hpp			\
			includes/Network/ServerCommunication.hpp		\
			includes/Network/TcpClient.hpp				\
			includes/Network/UdpClient.hpp				\
			../shared/includes/Config.hpp				\
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
			../shared/includes/Commands/CommandUpdateScore.hpp	

SOURCES		+=	sources/main.cpp				\
			sources/RTypeClient.cpp				\
			sources/Audio/SoundManager.cpp			\
			sources/Core/CollisionSystem.cpp		\
			sources/Core/DamageSystem.cpp			\
			sources/Core/DrawableSystem.cpp			\
			sources/Core/InputManager.cpp			\
			sources/Core/MovementSystem.cpp			\
			sources/Core/System.cpp				\
			sources/Engine/Collision.cpp			\
			sources/Engine/Component.cpp			\
			sources/Engine/Controllable.cpp			\
			sources/Engine/Drawable.cpp			\
			sources/Engine/ECSManager.cpp			\
			sources/Engine/Entity.cpp			\
			sources/Engine/Position.cpp			\
			sources/Engine/Script.cpp			\
			sources/GUI/ContentManager.cpp			\
			sources/GUI/FontManager.cpp			\
			sources/GUI/SFMLGraphic.cpp			\
			sources/GUI/SpriteManager.cpp			\
			sources/GUI/SpriteModel.cpp			\
			sources/GUI/TextureManager.cpp			\
			sources/Network/CommandPacketBuilder.cpp	\
			sources/Network/ServerCommunication.cpp		\
			sources/Network/TcpClient.cpp			\
			sources/Network/UdpClient.cpp

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

win32: DEFINES += __OS_WINDOWS__ _CRT_SECURE_NO_WARNINGS
unix : DEFINES += __OS_LINUX__
DEFINES        += _DEBUG