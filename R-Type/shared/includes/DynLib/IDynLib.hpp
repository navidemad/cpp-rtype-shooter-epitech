#pragma once

#include <string>

/*
Usage:

typedef RETURN_TYPE (*NAME_PTR_FCT) (PARAMETERS...);

auto            lib = PortabilityBuilder::getDynLib();
void*           fctPtr;
RETURN_TYPE     entity;

// il va automatiquement ajouter .so ou bien .dll en fonction de l'OS
lib->libraryLoad(std::string("./build/tinymonster"));

// fonction trampoline (extern C)
fctPtr = lib->functionLoad("createAndFill");

// creation de l'objet
entity = ((NAME_PTR_FCT)(fctPtr))(800, 600, 100, 100, 1);

// appel d'une fonction de l'objet généré
std::cout << entity->getSpeed() << std::endl;

*/
class IDynLib {

	// ctor dtor
	public:
		virtual ~IDynLib(void) {}

	// interface implementation
	public:
        virtual void    libraryLoad(const std::string&) = 0;
		virtual void*   functionLoad(const std::string&) const = 0;
        virtual void    libraryFree(void) = 0;

};
