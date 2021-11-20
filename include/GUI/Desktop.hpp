#ifndef DESKTOP_HPP_
#define DESKTOP_HPP_

#include "GUI/IDesktop.hpp"
#include "SFGUI/Desktop.hpp"

class Desktop final : public IDesktop
{
private:
    sfg::Desktop mDesktop;
public:
    bool SetProperties(const std::string& properties) override
    {
        return mDesktop.SetProperties(properties);
    }

    void Update(float seconds) override
    {
        mDesktop.Update(seconds);
    }

    void HandleEvent(const sf::Event& event) override
    {
        mDesktop.HandleEvent(event);
    }

    void Add(std::shared_ptr<sfg::Widget> widget) override
    {
        mDesktop.Add(widget);
    }

    void Remove(std::shared_ptr<sfg::Widget> widget) override
    {
        mDesktop.Remove(widget);
    }

    void RemoveAll() override
    {
        mDesktop.RemoveAll();
    }

    void Refresh() override
    {
        mDesktop.Refresh();
    }

    bool LoadThemeFromFile(const std::string& filename) override
    {
        return mDesktop.LoadThemeFromFile(filename);
    }

    sfg::Engine& GetEngine() override
    {
        return mDesktop.GetEngine();
    }

    void BringToFront(std::shared_ptr<const sfg::Widget> child) override
    {
        mDesktop.BringToFront(child);
    }

    void RemoveWidgets(
        std::vector<std::shared_ptr<sfg::Widget>>::iterator begin,
        std::vector<std::shared_ptr<sfg::Widget>>::iterator end
    ) override
    {
        for (auto widget = begin; widget != end; widget++) {
            mDesktop.Remove(*widget);
        }
    }
};

#endif // DESKTOP_HPP_
