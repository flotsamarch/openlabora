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

#ifndef APPLICATIONSTATE_HPP_
#define APPLICATIONSTATE_HPP_

#include <concepts>
#include "LibTypedefs.hpp"
#include "Misc/PtrView.hpp"

namespace open_labora
{

class Input;

template<class T>
concept CDrawable = std::derived_from<std::remove_cvref_t<T>, Drawable>;

template<class T>
concept CApplicationState = requires(T t, float f, PtrView<const Input> i)
{
    stateUpdate(t, f);
    stateHandleInput(t, i);
    { stateGetDrawableObjects(t) } -> std::same_as<DrawableRangeConst>;
    { stateGetFlagIsFinal(t) } -> std::same_as<bool>;
};

/**
 * Application state interface
 *
 * Apart from requirements imposed by CApplicationState concept implementation of
 * this * interface also requires definition of function which maps tag T to
 * TImpl and * calls ApplicationContext::ChangeState<TImpl>(...):
 * void changeState(ApplicationContext::Ptr, T)
 *
 * changeState(...) function should also be forward declared with the tag T in a
 * separate file to move dependency between states from compilation to linkage
 */
class ApplicationState final
{
    struct StateConcept
    {
        virtual ~StateConcept() = default;

        virtual void Update(float update_delta_seconds) = 0;

        virtual void HandleInput(PtrView<const Input>) = 0;

        virtual DrawableRangeConst GetDrawableObjects() = 0;

        virtual bool IsFinal() noexcept = 0;
    };

    template<CApplicationState T>
    struct StateModel : public StateConcept
    {
        T mState;

        template<typename... Args>
        StateModel(Args&&... args) : mState{ std::forward<Args>(args)... } {}

        void Update(float update_delta_seconds) override
        { stateUpdate(mState, update_delta_seconds); }

        void HandleInput(PtrView<const Input> input) override
        { stateHandleInput(mState, input); }

        DrawableRangeConst GetDrawableObjects() override
        { return stateGetDrawableObjects(mState); }

        bool IsFinal() noexcept override
        { return stateGetFlagIsFinal(mState); }
    };

    std::unique_ptr<StateConcept> mSelf;

public:
    template<CApplicationState T, typename... Args>
    void ChangeState(Args&&... args)
    {
        mSelf.reset(); // This breaks strong exception safety guarantee.
                       // But state objects are memory expensive and having two
                       // instances at the same time is not desirable.
        mSelf = std::make_unique<StateModel<T>>(std::forward<Args>(args)...);
    }

    friend void stateUpdate(ApplicationState& state, float update_delta_seconds)
    { state.mSelf->Update(update_delta_seconds); }

    friend void stateHandleInput(ApplicationState& state,
                                 PtrView<const Input> input)
    { state.mSelf->HandleInput(input); }

    friend DrawableRangeConst stateGetDrawableObjects(ApplicationState& state)
    { return state.mSelf->GetDrawableObjects(); }

    friend bool stateGetFlagIsFinal(const ApplicationState& state) noexcept
    { return state.mSelf->IsFinal(); }
};

} // namespace open_labora

#endif // APPLICATIONSTATE_HPP_
