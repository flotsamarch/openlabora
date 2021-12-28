#ifndef IAPPLICATION_HPP_
#define IAPPLICATION_HPP_

#include <memory>
#include "resource/IResourceManager.hpp"

class State;

class IApplication
{
public:
    virtual ~IApplication() noexcept {};

    virtual int run() = 0;
};

#endif // IAPPLICATION_HPP_
