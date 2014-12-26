#pragma once

#include "IResource.hpp"

struct MYLIB_EXPORT Caster : public IResource {
   								    Caster(void) = default;
    virtual 					    ~Caster(void) = default;
    virtual std::string             getName(void) const;
    virtual short                  getHeight(void) const;
    virtual short                  getWidth(void) const;
    virtual short                     getLife(void) const;
    virtual double 			        getMoveSpeed(void) const;
    virtual double                  getFireDeltaTime(void) const;
    virtual IResource::Type         getType(void) const;
	virtual IResource::Vec2         move(double deltaTime) const;
	virtual IResource::Vec2         fire(double deltaTime) const;
};
