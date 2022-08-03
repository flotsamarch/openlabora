// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef GAMECONTROLLER_HPP_
#define GAMECONTROLLER_HPP_

#include "ApplicationState/ApplicationContext.hpp"
#include "Resource/IResourceManager.hpp"
#include "LibTypedefs.hpp"
#include "Input/Input.hpp"
// TODO: Reimplement Build Mode
// #include "Game/Location.hpp"

namespace open_labora
{

// General game logic base class
template<class TModel>
class GameController final
{
protected:
    ApplicationContext::Ptr mApp;
    IResourceManager::Ptr mResourceMgr;
    typename TModel::Ptr mModel;

public:
    GameController(ApplicationContext::Ptr app,
                   IResourceManager::Ptr,
                   typename TModel::Ptr,
                   uint32_t player_count);

    void HandleInput(Input::PtrConst);

    void Update(const float update_delta_seconds);

    void SetPaused(bool value) noexcept
    { mModel->SetPaused(value); };

    typename TModel::Ptr GetModel() const
    { return mModel; }

    IResourceManager::Ptr GetResourceManager() const noexcept
    { return mResourceMgr; }

    void SetWorldMousePosition(const sf::Vector2f& position)
    { mModel->SetWorldMousePosition(position); }
};

template<class TModel>
GameController<TModel>::GameController(ApplicationContext::Ptr app,
                                       IResourceManager::Ptr resource_mgr,
                                       typename TModel::Ptr model,
                                       [[maybe_unused]]uint32_t player_count)
    : mApp{ app },
      mResourceMgr{ resource_mgr },
      mModel{ model }
{
    #if 0
    auto pf_width = static_cast<float>(playfield::kMaxFieldWidth);
    auto pf_margin = pf_width * tile::kTileWidth + 3 * tile::kTileWidth;

    for (uint32_t player{0}; auto&& pf : mModel->GetPlayfields()) {
        auto position = sf::Vector2f{ 0.f, 0.f };
        pf.reset();
        if (player < player_count) {
            pf = playfield::create(resource_mgr, position);
            AddEntity(pf);
            position.x += pf_margin;
            player++;
        }
    }
    #endif
}

template<class TModel>
void GameController<TModel>::HandleInput(Input::PtrConst)
{
}

template<class TModel>
void GameController<TModel>
::Update([[maybe_unused]]const float update_delta_seconds)
{
}

} // namespace open_labora

#endif // GAMECONTROLLER_HPP_
