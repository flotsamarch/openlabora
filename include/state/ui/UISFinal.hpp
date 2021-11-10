#ifndef UISFINAL_HPP_
#define UISFINAL_HPP_

#include "UiState.hpp"

class UISFinal final : public UiState
{
public:
    UISFinal(State& state) : UiState{ state } { bIsComplete = true; };
};

#endif // UISFINAL_HPP_
