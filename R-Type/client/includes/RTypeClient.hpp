#pragma once

class RTypeClient
{
    // ctor - dtor
    public:
        explicit RTypeClient();
        ~RTypeClient();

    // copy operators
    public:
        RTypeClient(const RTypeClient &) = delete;
        RTypeClient(RTypeClient &&) = delete;
        const RTypeClient &operator=(const RTypeClient &) = delete;
        const RTypeClient &operator=(RTypeClient &&) = delete;
};
