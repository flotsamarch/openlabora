#ifndef IAPPLICATION_HPP_
#define IAPPLICATION_HPP_

namespace OpenLabora
{

template<class TStateIdsVariant>
class IApplication
{
public:
    // No need for virtual destructor
    // Application is never heap allocated
    virtual void ChangeState(TStateIdsVariant state_id) = 0;
};

}

#endif // IAPPLICATION_HPP_
