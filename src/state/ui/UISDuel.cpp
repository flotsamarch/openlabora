#include "state/ui/UISDuel.hpp"

#include <cassert>
#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include "state/State.hpp"
#include "state/AppStateDefs.hpp"
#include "state/gs/GSDuel.hpp"
#include "IRenderer.hpp"
#include "game/Location.hpp"

UISDuel::UISDuel(std::shared_ptr<State> state,
                               const sf::VideoMode& vm) :
    UISEscapeMenu{ state, vm }
{
    auto btn_height = 40.f;
    auto btn_width = 240.f;
    auto margin = 5.f;

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
                static_cast<GSDuel&>(state_ptr.lock()->GetGameState());

            if (!state.IsPaused()) {
                state.EnableBuildMode(type);
            }
        });

        box->Pack(btn);
    }

    box->SetAllocation(sf::FloatRect(margin,
                                     mVideoMode.height - margin - btn_height,
                                     (btn_width + margin) * buildable.size(),
                                     btn_height));

    mDesktop.Add(box);
}
