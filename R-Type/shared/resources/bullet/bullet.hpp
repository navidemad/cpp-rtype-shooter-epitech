#pragma once

#include "IResource.hpp"

struct MYLIB_EXPORT Bullet : public IResource {
                                    Bullet(void) = default;
    virtual 					    ~Bullet(void) = default;
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
