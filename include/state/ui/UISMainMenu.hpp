#ifndef UISMAINMENU_HPP_
#define UISMAINMENU_HPP_

#include "UiState.hpp"

class UISMainMenu final : public UiState
{
public:
    UISMainMenu(std::shared_ptr<State>, const sf::VideoMode&);
};


#endif // UISMAINMENU_HPP_
