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

#ifndef IAPPLICATION_HPP_
#define IAPPLICATION_HPP_

namespace open_labora
{

template<class TStateIdsVariant>
class IApplication
{
public:
    virtual ~IApplication() = default;

    virtual void ChangeState(TStateIdsVariant state_id) = 0;
};

} // namespace open_labora

#endif // IAPPLICATION_HPP_
