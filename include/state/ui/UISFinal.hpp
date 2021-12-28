#ifndef UISFINAL_HPP_
#define UISFINAL_HPP_

#include "UiState.hpp"

class UISFinal final : public UiState
{
public:
    UISFinal(std::shared_ptr<State> state, const sf::VideoMode& vm)
        : UiState{ state, vm } {};
};

#endif // UISFINAL_HPP_
