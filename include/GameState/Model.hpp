// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "ECS/Registry.hpp"
#include "Misc/PtrView.hpp"
#include "Misc/CommonTypedefs.hpp"
#include "LibTypedefs.hpp"

namespace open_labora
{

class Model final
{
    Registry mRegistry;
    DrawableContainer mDrawableObjects;

    bool bPaused{ false };
    static constexpr uint kMaxPlayers = 4;

    Vector2f mWorldMousePosition{};

public:
    enum PlayerAffiliation { Player1, Player2, Player3, Player4 };

    using Ptr = PtrView<Model>;

    bool IsPaused() const noexcept
    { return bPaused; }

    void SetPaused(bool value) noexcept
    { bPaused = value; }

    DrawableRangeConst GetDrawableObjects() const noexcept
    { return { mDrawableObjects.cbegin(), mDrawableObjects.cend() }; }

    void ClearDrawableObjects() noexcept
    { mDrawableObjects.clear(); }

    void AddDrawableObject(const Drawable& drawable) noexcept
    { mDrawableObjects.emplace_back(drawable); }

    void SetWorldMousePosition(const Vector2f& position)
    { mWorldMousePosition = position; }

    Vector2f GetWorldMousePosition() const
    { return mWorldMousePosition; }

    Registry& GetRegistry() noexcept
    { return mRegistry; }

    const Registry& GetRegistry() const noexcept
    { return mRegistry; }
};

} // namespace open_labora

#endif // MODEL_HPP_
