#include "state/ui/UISDuelHotSeat.hpp"

#include <cassert>
#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include "state/State.hpp"
#include "state/AppStateDefs.hpp"
#include "state/gs/GSFinal.hpp"
#include "state/ui/UISFinal.hpp"
#include "IRenderer.hpp"

UISDuelHotSeat::UISDuelHotSeat(std::shared_ptr<State> state) :
    UISEscapeMenu{ state }
{
}
