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

#ifndef DYNAMICTEXTURECOMPONENT_HPP_
#define DYNAMICTEXTURECOMPONENT_HPP_

namespace open_labora
{

class DynamicTextureComponent final
{
    bool bNeedsUpdate{ true };

public:
    bool NeedsUpdate() const noexcept
    { return bNeedsUpdate; }

    void SetUpToDate(bool value) noexcept
    { bNeedsUpdate = !value; }
};

} // namespace open_labora

#endif // DYNAMICTEXTURECOMPONENT_HPP_
