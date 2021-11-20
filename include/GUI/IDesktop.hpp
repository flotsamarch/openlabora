#ifndef IDESKTOP_HPP_
#define IDESKTOP_HPP_

#include <string>
#include <memory>
#include <SFGUI/Engine.hpp>
#include <SFGUI/Widget.hpp>
#include <SFML/Window/Event.hpp>

// Interface for adapting sfg::Desktop
class IDesktop
{
public:
    virtual inline ~IDesktop() noexcept = 0;

    virtual bool SetProperties(const std::string& properties) = 0;

    virtual void Update(float seconds) = 0;

    virtual void HandleEvent(const sf::Event& event) = 0;

    virtual void Add(std::shared_ptr<sfg::Widget> widget) = 0;

    virtual void Remove(std::shared_ptr<sfg::Widget> widget) = 0;

    virtual void RemoveAll() = 0;

    virtual void Refresh() = 0;

    virtual bool LoadThemeFromFile(const std::string& filename) = 0;

    virtual sfg::Engine& GetEngine() = 0;

    virtual void BringToFront(std::shared_ptr<const sfg::Widget> child) = 0;

    virtual void RemoveWidgets(
        std::vector<std::shared_ptr<sfg::Widget>>::iterator begin,
        std::vector<std::shared_ptr<sfg::Widget>>::iterator end
    ) = 0;
};

inline IDesktop::~IDesktop() noexcept {}

#endif // IDESKTOP_HPP_
