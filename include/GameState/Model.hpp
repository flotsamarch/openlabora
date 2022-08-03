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

#include "Misc/PtrView.hpp"
#include "LibTypedefs.hpp"

namespace open_labora
{

class Model final
{
    DrawableContainer mDrawableObjects;

    bool bPaused{ false };
    static constexpr uint32_t kMaxPlayers = 4;

    Vector2f mWorldMousePosition{};

public:
    enum PlayerAffiliation { Player1, Player2, Player3, Player4 };

    using Ptr = PtrView<Model>;

public:
    bool IsPaused() const noexcept
    { return bPaused; }

    void SetPaused(bool value)
    { bPaused = value; }

    DrawableRangeConst GetDrawableObjects() const noexcept
    { return { mDrawableObjects.cbegin(), mDrawableObjects.cend() }; }

    void ClearDrawableObjects() noexcept
    { mDrawableObjects.clear(); }

    void AddDrawableObject(DrawablePtr drawable)
    { mDrawableObjects.emplace_back(std::move(drawable)); }

    void SetWorldMousePosition(const Vector2f& position)
    { mWorldMousePosition = position; }

    Vector2f GetWorldMousePosition() const
    { return mWorldMousePosition; }
};

} // namespace open_labora

#endif // MODEL_HPP_
