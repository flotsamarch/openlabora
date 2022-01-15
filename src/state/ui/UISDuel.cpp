#include "state/ui/UISDuel.hpp"

#include <cassert>
#include <SFGUI/Box.hpp>
#include "GUI/IngameButton.hpp"
#include "state/State.hpp"
#include "state/AppStateDefs.hpp"
#include "state/gs/GSDuel.hpp"
#include "IRenderer.hpp"
#include "game/Location.hpp"

UISDuel::UISDuel(std::shared_ptr<State> state,
                 const sf::VideoMode& vm)
    : UISCommon{ state, vm }
{
    auto btn_height = 40.f;
    auto btn_width = 240.f;
    auto margin = 5.f;

    using LT = Location::LocationType;

    std::vector<LT> buildable = {
        LT::Forest, LT::Peat, LT::HouseBoat, LT::FishingVillage, LT::ClayMound
    };

    auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, margin);

    for (auto type : buildable) {
        auto location_name = std::string(Location::GetLocationName(type));
        auto btn = IngameButton::Create(mState.lock(), location_name);

        btn->GetSignal(sfg::Widget::OnLeftClick).Connect(
        [type, state_ptr = this->mState]
        {
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
