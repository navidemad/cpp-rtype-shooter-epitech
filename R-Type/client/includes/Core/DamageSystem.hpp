#pragma once

class DamageSystem
{
    // ctor - dtor
    public:
        explicit DamageSystem();
        ~DamageSystem();

    // copy operators
    public:
        DamageSystem(const DamageSystem &) = delete;
        DamageSystem(DamageSystem &&) = delete;
        const DamageSystem &operator=(const DamageSystem &) = delete;
        const DamageSystem &operator=(DamageSystem &&) = delete;
};
