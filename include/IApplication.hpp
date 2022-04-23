#ifndef IAPPLICATION_HPP_
#define IAPPLICATION_HPP_

namespace OpenLabora
{

template<class TStateIdsVariant>
class IApplication
{
public:
    virtual ~IApplication() = default;

    virtual void ChangeState(TStateIdsVariant state_id) = 0;
};

}

#endif // IAPPLICATION_HPP_
