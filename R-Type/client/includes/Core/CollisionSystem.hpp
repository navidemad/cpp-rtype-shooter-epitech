#pragma once

class CollisionSystem
{
    // ctor - dtor
    public:
        explicit CollisionSystem();
        ~CollisionSystem();

    // copy operators
    public:
        CollisionSystem(const CollisionSystem &) = delete;
        CollisionSystem(CollisionSystem &&) = delete;
        const CollisionSystem &operator=(const CollisionSystem &) = delete;
        const CollisionSystem &operator=(CollisionSystem &&) = delete;
};
