#include "GameState/Views/GVDuel.hpp"

namespace OpenLabora
{

GVDuel::GVDuel(PtrView<IApplication<StateIdsVariant>> app,
               PtrView<tgui::GuiSFML> gui,
               std::shared_ptr<GCDuel> controller,
               PtrView<const Model> model)
    : GameView(app, gui, controller, model)
{
    // TODO fix GUI. Move this to GameView
#if 0
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

#endif // duel ui
}

} //namespace OpenLabora
