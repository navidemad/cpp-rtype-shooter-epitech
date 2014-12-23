#pragma once

#include "IResource.hpp"

struct MYLIB_EXPORT Melee : public IResource {
   								    Melee(void) = default;
    virtual 					    ~Melee(void) = default;
    virtual std::string             getName(void) const;
    virtual double                  getHeight(void) const;
    virtual double                  getWidth(void) const;
	virtual int                     getLife(void) const;
	virtual double 			        getMoveSpeed(void) const;
	virtual double                  getFireSpeed(void) const;
    virtual IResource::Type         getType(void) const;
	virtual IResource::Vec2         move(double deltaTime) const;
	virtual IResource::Vec2         fire(double deltaTime) const;
};
