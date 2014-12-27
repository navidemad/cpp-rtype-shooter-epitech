#pragma once

#include "IResource.hpp"

struct MYLIB_EXPORT Bullet : public IResource {
                            Bullet(void) = default;
    virtual                 ~Bullet(void) = default;
    virtual std::string     getName(void) const;
    virtual float           getHeight(void) const;
    virtual float           getWidth(void) const;
    virtual short           getLife(void) const;
    virtual float           getMoveSpeed(void) const;
    virtual float           getFireDeltaTime(void) const;
    virtual IResource::Type getType(void) const;
};
