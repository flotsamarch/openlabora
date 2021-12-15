#include "state/ui/UISDuelHotSeat.hpp"

#include <cassert>
#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include "state/State.hpp"
#include "state/AppStateDefs.hpp"
#include "state/gs/GSFinal.hpp"
#include "state/ui/UISFinal.hpp"
#include "state/gs/GSDuelHotSeat.hpp"
#include "IRenderer.hpp"
#include "game/Location.hpp"

UISDuelHotSeat::UISDuelHotSeat(std::shared_ptr<State> state) :
    UISEscapeMenu{ state }
{
    auto video_mode = GetRenderer().GetVideoMode();
    auto btn_height = 40.f;
    auto btn_width = 240.0f;
    auto margin = 5.0f;

    auto state_ptr = mState;

    using LT = Location::LocationType;

    std::vector<LT> buildable = {
        LT::Forest, LT::Peat, LT::HouseBoat, LT::FishingVillage, LT::ClayMound
    };

    auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, margin);

    for (auto type : buildable) {
        auto btn =
            sfg::Button::Create(std::string(Location::GetLocationName(type)));

        btn->GetSignal(sfg::Widget::OnLeftClick).Connect([type, state_ptr]{
            assert(!state_ptr.expired());
            auto&& state =
                static_cast<GSDuelHotSeat&>(state_ptr.lock()->GetGameState());

            if (!state.IsPaused()) {
                state.EnableBuildMode(type);
            }
        });

        box->Pack(btn);
    }

    box->SetAllocation(sf::FloatRect(margin,
                                     video_mode.height - margin - btn_height,
                                     (btn_width + margin) * buildable.size(),
                                     btn_height));

    AddWidgetToDesktop(box);
}
