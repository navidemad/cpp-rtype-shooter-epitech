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

HEADERS         +=      includes/RTypeClient.hpp		\
			includes/Audio/SoundManager.hpp		\
			includes/Core/CollisionSystem.hpp	\
			includes/Core/DamageSystem.hpp		\
			includes/Core/DrawableSystem.hpp	\
			includes/Core/MovementSystem.hpp	\
			includes/Core/System.hpp		\
			includes/Engine/Collision.hpp		\
			includes/Engine/Component.hpp		\
			includes/Engine/Controllable.hpp	\
			includes/Engine/Drawable.hpp		\
			includes/Engine/ECSManager.hpp		\
			includes/Engine/Entity.hpp		\
			includes/Engine/Position.hpp		\
			includes/Engine/Script.hpp		\
			includes/GUI/ContentManager.hpp		\
			includes/GUI/FontManager.hpp		\
			includes/GUI/IGraphic.hpp		\
			includes/GUI/IRessourceManager.hpp	\
			includes/GUI/SFMLGraphic.hpp		\
			includes/GUI/TextureManager.hpp		\
			includes/Network/INetworkManager.hpp

SOURCES         +=      sources/main.cpp			\
			sources/RTypeClient.cpp			\
			sources/Audio/SoundManager.cpp		\
			sources/Core/CollisionSystem.cpp	\
			sources/Core/DamageSystem.cpp		\
			sources/Core/DrawableSystem.cpp		\
			sources/Core/MovementSystem.cpp		\
			sources/Core/System.cpp			\
			sources/Engine/Collision.cpp		\
			sources/Engine/Component.cpp		\
			sources/Engine/Controllable.cpp		\
			sources/Engine/Drawable.cpp		\
			sources/Engine/ECSManager.cpp		\
			sources/Engine/Entity.cpp		\
			sources/Engine/Position.cpp		\
			sources/Engine/Script.cpp		\
			sources/GUI/ContentManager.cpp		\
			sources/GUI/FontManager.cpp		\
			sources/GUI/SFMLGraphic.cpp		\
			sources/GUI/TextureManager.cpp

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system

win32:LIBS      +=      -ldependencies/libs/sfml-audio		\
			-ldependencies/libs/sfml-graphics	\
			-ldependencies/libs/sfml-main		\
			-ldependencies/libs/sfml-network	\
			-ldependencies/libs/sfml-system		\
			-ldependencies/libs/sfml-window

unix:LIBS       +=     	
