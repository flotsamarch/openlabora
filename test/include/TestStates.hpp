#ifndef TESTSTATES_HPP_
#define TESTSTATES_HPP_

#include <gmock/gmock.h>
#include <memory>
#include "state/ILogicState.hpp"
#include "state/gs/IGameState.hpp"
#include "state/ui/IUiState.hpp"
#include "state/gs/GameState.hpp"
#include "state/ui/UiState.hpp"

namespace Test
{
using ::testing::NiceMock;

class GSTest final : public GameState
{
public:
    GSTest(std::shared_ptr<State> state) : GameState{ state } {};
};

class UISTest final : public UiState
{
public:
    UISTest(std::shared_ptr<State> state) : UiState{ state } {};
};

class GSMock : public IGameState
{
public:
    GSMock(std::shared_ptr<State>) {};
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), (override));
    MOCK_METHOD(void, HandleEventImpl, (const sf::Event&), (override));
    MOCK_METHOD(void, Update, (const float secondsSinceLastUpdate), (override));
    MOCK_METHOD(void, SetPaused, (bool), (noexcept, override));
    MOCK_METHOD(bool, IsPaused, (), (noexcept, override));
    MOCK_METHOD(IDrawable::Iter, GetGameObjectBegin, (), (noexcept));
    MOCK_METHOD(IDrawable::Iter, GetGameObjectEnd, (), (noexcept));
};

class UISMock : public IUiState
{
public:
    UISMock(std::shared_ptr<State>) {};
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), (override));
    MOCK_METHOD(void, HandleEventImpl, (const sf::Event&), (override));
    MOCK_METHOD(void, Update, (const float secondsSinceLastUpdate), (override));
    MOCK_METHOD(IRenderer&, GetRenderer, (), (ref(&), const, override));
    MOCK_METHOD(void, AddWidgetToDesktop, (sfg::Widget::Ptr), (override));
    MOCK_METHOD(void, RemoveAllWidgets, (), (override));
};

struct StateMock final {
    using gs_type = NiceMock<GSMock>;
    using ui_type = NiceMock<UISMock>;
};

struct StateTest final {
    using gs_type = GSTest;
    using ui_type = UISTest;
};

} // namespace Test

#endif // TESTSTATES_HPP_
