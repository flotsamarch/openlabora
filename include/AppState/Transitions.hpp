#ifndef TRANSITIONS_HPP_
#define TRANSITIONS_HPP_

#include <memory>
#include <concepts>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>

#include "StateIds.hpp"
#include "AppState.hpp"
#include "IApplication.hpp"
#include "Misc/PtrView.hpp"
#include "Resource/IResourceManager.hpp"

#include "GameState/Views/GVMainMenu.hpp"
#include "GameState/Views/GVDuel.hpp"
#include "GameState/Views/GVFinal.hpp"

#include "GameState/Controllers/GCMainMenu.hpp"
#include "GameState/Controllers/GCDuel.hpp"
#include "GameState/Controllers/GCFinal.hpp"

namespace OpenLabora
{

// ----------------------- ADD ALL STATES HERE ----------------------------------
using MainMenuState = AppState<GVMainMenu, GCMainMenu>;
using DuelState = AppState<GVDuel, GCDuel>;
using FinalState = AppState<GVFinal, GCFinal>;

using State = std::variant<MainMenuState, DuelState, FinalState>;

/**
 * Callable that allows transitions between application states. Intended to be
 * used as callable for std::visit
 *
 * @arg Empty struct which represents one of possible application states
 * @return New AppState object or std::nullopt if there is no overload for @arg
 */
class Transitions final
{
    using IApplication = IApplication<StateIdsVariant>;

    template<class TView, class TController>
    AppState<TView, TController>
    CreateState()
    {
        using std::make_shared;
        auto controller = make_shared<TController>(mApp, mResManager, mModel);
        TView view{ mApp, mGui, controller, PtrView<const Model>(mModel.Get()) };
        return AppState<TView, TController>{ controller, std::move(view) };
    }

    PtrView<IApplication> mApp;
    IResourceManager::Ptr mResManager;
    PtrView<tgui::GuiSFML> mGui;
    PtrView<Model> mModel;

public:
    using StateOpt = std::optional<State>;

    Transitions(PtrView<IApplication> app, IResourceManager::Ptr res_manager,
                PtrView<tgui::GuiSFML> gui, PtrView<Model> model)
        : mApp{ app }, mResManager{ res_manager }, mGui{ gui }, mModel{ model }
        {}

// ----------------------- ADD ALL TRANSITIONS HERE -----------------------------
    StateOpt operator()(const MainMenuStateId&)
    {
        return CreateState<GVMainMenu, GCMainMenu>();
    };

    StateOpt operator()(const DuelStateId&)
    {
        return CreateState<GVDuel, GCDuel>();
    };

    StateOpt operator()(const FinalStateId&)
    {
        return CreateState<GVFinal, GCFinal>();
    };

    template<class T>
    StateOpt operator()(const T&)
    {
        return std::nullopt;
    }
};

} // namespace OpenLabora

#endif // TRANSITIONS_HPP_
