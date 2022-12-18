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

#ifndef GAMECONTROLLERMOCK_HPP_
#define GAMECONTROLLERMOCK_HPP_

#include <gmock/gmock.h>
#include "ApplicationState/ApplicationContext.hpp"
#include "Resource/IResourceManager.hpp"
#include "Input/Input.hpp"

namespace test
{

namespace ol = open_labora;

template<class TModel>
struct GameControllerMock
{
    GameControllerMock(ol::ApplicationContext::Ptr,
                       ol::IResourceManager::Ptr,
                       ol::PtrView<TModel>,
                       int player_count) {};

    MOCK_METHOD(void, HandleInput, (ol::Input::PtrConst));

    MOCK_METHOD(void, Update, (const float update_delta_seconds));

    MOCK_METHOD(void, SetPaused, (bool value), (noexcept));

    MOCK_METHOD(typename TModel::Ptr, GetModel, (), (const));

    MOCK_METHOD(ol::IResourceManager::Ptr, GetResourceManager, (),
                (const, noexcept));

    MOCK_METHOD(void, SetWorldMousePosition, (const sf::Vector2f& position));
};


} // namespace test

#endif // GAMECONTROLLERMOCK_HPP_
