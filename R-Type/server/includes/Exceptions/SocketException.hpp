#pragma once

#include <stdexcept>

class SocketException : public std::runtime_error {
public:
    SocketException(const std::string & error) throw() : std::runtime_error(error), mWhat(error) { }
    const SocketException & operator = (const SocketException &) throw() = delete;
    virtual ~SocketException(void) throw() {}
    virtual const char *what(void) const throw() { return mWhat.c_str(); }
private:
    const std::string mWhat;
};
