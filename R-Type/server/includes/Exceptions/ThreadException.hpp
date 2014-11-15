#pragma once

#include <stdexcept>

class ThreadException : public std::runtime_error {
public:
    ThreadException(const std::string & error) throw() : std::runtime_error(error), mWhat(error) { }
    const ThreadException & operator = (const ThreadException &) throw() = delete;
    virtual ~ThreadException(void) throw() {}
    virtual const char *what(void) const throw() { return mWhat.c_str(); }
private:
    const std::string mWhat;
};
