#ifndef UISFINAL_HPP_
#define UISFINAL_HPP_

#include "UiState.hpp"

class UISFinal final : public UiState
{
public:
    UISFinal(std::shared_ptr<State> state) : UiState{ state } {};
};

#endif // UISFINAL_HPP_
