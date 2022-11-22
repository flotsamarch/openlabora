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

#ifndef PLOTACQUISITIONVIEWMODELMOCK_HPP_
#define PLOTACQUISITIONVIEWMODELMOCK_HPP_

#include <gmock/gmock.h>
#include "LibTypedefs.hpp"
#include "Game/Plot.hpp"

namespace test
{

struct PlotAcquisitionViewModelMock
{
    virtual ~PlotAcquisitionViewModelMock() = default;

    MOCK_METHOD(void, HighlightMarker, (const open_labora::Vector2f&));

    MOCK_METHOD(bool, SelectMarker, (const open_labora::Vector2f&));

    MOCK_METHOD(open_labora::lot::Type, GetSelectedMarkerLotType, ());

    MOCK_METHOD(void, DeselectMarker, ());

    MOCK_METHOD(open_labora::plot::AcquireReturnType,
                AcquirePlot,
                (open_labora::plot::AcquirePlotParams&));
};

} // namespace test


#endif // PLOTACQUISITIONVIEWMODELMOCK_HPP_
