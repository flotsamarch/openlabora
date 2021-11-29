#ifndef IAPPLICATION_HPP_
#define IAPPLICATION_HPP_

#include "IRenderer.hpp"

class State;

class IApplication
{
public:
    virtual ~IApplication() noexcept {};

    virtual IRenderer* GetRenderer() const noexcept = 0;

    virtual std::shared_ptr<State> GetState() const noexcept = 0;

    virtual int run() = 0;
};

#endif // IAPPLICATION_HPP_
