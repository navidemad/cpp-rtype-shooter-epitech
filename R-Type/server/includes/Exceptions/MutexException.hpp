#pragma once

#include <stdexcept>

class MutexException : public std::runtime_error {
public:
    MutexException(const std::string & error) throw() : std::runtime_error(error), mWhat(error) { }
    const MutexException & operator = (const MutexException &) throw() = delete;
    virtual ~MutexException(void) throw() {}
    virtual const char *what(void) const throw() { return mWhat.c_str(); }
private:
    const std::string mWhat;
};
