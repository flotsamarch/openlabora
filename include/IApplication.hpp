#ifndef IAPPLICATION_HPP_
#define IAPPLICATION_HPP_

namespace OpenLabora
{

class IApplication
{
public:
    virtual ~IApplication() {};

    virtual int run() = 0;
};

}

#endif // IAPPLICATION_HPP_
