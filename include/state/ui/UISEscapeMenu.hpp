#ifndef UISESCAPEMENU_HPP_
#define UISESCAPEMENU_HPP_

#include "UiState.hpp"

class UISEscapeMenu : public UiState
{
    bool bIsMenuHidden{ true };
    std::vector<sfg::Widget::Ptr> mMenuWidgets;
public:
    UISEscapeMenu(std::shared_ptr<State>, const sf::VideoMode&);

    void HandleEvent(const sf::Event&) override;
};

#endif // UISESCAPEMENU_HPP_
