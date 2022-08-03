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

#ifndef APPLICATIONCONTEXT_HPP_
#define APPLICATIONCONTEXT_HPP_

#include "ApplicationState.hpp"
#include "Misc/PtrView.hpp"

namespace open_labora
{

namespace state
{

// Ensure StateId is an empty class/struct and has default constructor
template<class T>
concept CStateId = requires(T t)
{
    T{};
    std::is_empty_v<T>;
};

template<CStateId TId, typename... Args>
void changeState(Args&&... args)
{ changeState(TId{}, std::forward<Args>(args)...); }

} // namespace state

class ApplicationContext
{
protected:
    ApplicationState mState;

public:
    using Ptr = PtrView<ApplicationContext>;

    virtual ~ApplicationContext() = 0;

    template<class TState, typename... Args>
    void ChangeState(Args&&... args)
    { mState.ChangeState<TState>(PtrView{ this }, std::forward<Args>(args)...); }
};

inline ApplicationContext::~ApplicationContext() = default;

} // namespace open_labora

#endif // APPLICATIONCONTEXT_HPP_
