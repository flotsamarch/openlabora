#ifndef UISDUEL_HPP_
#define UISDUEL_HPP_

#include "UISCommon.hpp"

class UISDuel final : public UISCommon
{
public:
    UISDuel(std::shared_ptr<State>, const sf::VideoMode&);
};

#endif // UISDUEL_HPP_
