#ifndef RENDERERMOCK_HPP_
#define RENDERERMOCK_HPP_

#include <gmock/gmock.h>
#include "IRenderer.hpp"
#include "game/GameObject.hpp"

namespace Test
{


class RendererMock : public IRenderer
{
public:
    MOCK_METHOD(bool, IsWindowOpen, (), (const, override));

    MOCK_METHOD(bool, PollEvent, (sf::Event&), (override));

    MOCK_METHOD(void, RequestCloseWindow, (), (noexcept, override));

    MOCK_METHOD(void, Render,
                (const float, GameObject::Iter, GameObject::Iter), (override));

    MOCK_METHOD(void, HandleEvent, (const sf::Event&), (override));

    MOCK_METHOD(IDesktop&, GetDesktop, (), (ref(&), noexcept, override));

    MOCK_METHOD(sf::VideoMode, GetVideoMode, (), (override));

    MOCK_METHOD(void, MoveView, (float offset_x, float offset_y), (override));

    MOCK_METHOD(void, MoveView, (const sf::Vector2f& offset), (override));

    MOCK_METHOD(sf::Vector2f, mapPixelToCoords,
                (const sf::Vector2i&), (override));

    MOCK_METHOD(sf::Vector2i, mapCoordsToPixel,
                (const sf::Vector2f&), (override));
};

class DesktopMock : public IDesktop
{
public:
    MOCK_METHOD(
        bool, SetProperties, (const std::string& properties), (override)
    );

    MOCK_METHOD(void, Update, (float seconds), (override));

    MOCK_METHOD(void, HandleEvent, (const sf::Event& event), (override));

    MOCK_METHOD(void, Add, (std::shared_ptr<sfg::Widget> widget), (override));

    MOCK_METHOD(
        void, Remove, (std::shared_ptr<sfg::Widget> widget), (override)
    );

    MOCK_METHOD(void, RemoveAll, (), (override));

    MOCK_METHOD(void, Refresh, (), (override));

    MOCK_METHOD(
        bool, LoadThemeFromFile, (const std::string& filename), (override)
    );

    MOCK_METHOD(sfg::Engine&, GetEngine, (), (override));

    MOCK_METHOD(void, BringToFront,
                (std::shared_ptr<const sfg::Widget> child), (override));

    MOCK_METHOD(void, RemoveWidgets,
        (std::vector<std::shared_ptr<sfg::Widget>>::iterator begin,
        std::vector<std::shared_ptr<sfg::Widget>>::iterator end), (override));
};

} // namespace Test

#endif // RENDERERMOCK_HPP_
