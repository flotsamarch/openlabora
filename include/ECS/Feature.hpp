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

#ifndef FEATURE_HPP_
#define FEATURE_HPP_

#include <ecs.hpp/ecs.hpp>

namespace open_labora
{

class Feature final
{
    ecs_hpp::feature& mFeature;

public:
    Feature(ecs_hpp::feature& feature) noexcept
        : mFeature{ feature } {};

    Feature& Enable() noexcept
    { mFeature.enable(); return *this; }

    Feature& Disable() noexcept
    { mFeature.disable(); return *this; }

    bool IsEnabled() const noexcept
    { return mFeature.is_enabled(); }

    bool IsDisabled() const noexcept
    { return mFeature.is_disabled(); }

    template<class TSystem, class... Args>
    Feature& AddSystem(Args&&... args)
    { mFeature.add_system<TSystem>(std::forward<Args>(args)...); return *this; }
};

class ConstFeature final
{
    const ecs_hpp::feature& mFeature;

public:
    ConstFeature(const ecs_hpp::feature& feature) noexcept
        : mFeature{ feature } {};

    bool IsEnabled() const noexcept
    { return mFeature.is_enabled(); }

    bool IsDisabled() const noexcept
    { return mFeature.is_disabled(); }
};

} // namespace open_labora

#endif // FEATURE_HPP_
