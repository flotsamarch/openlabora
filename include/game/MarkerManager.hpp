#ifndef MARKERMANAGER_HPP_
#define MARKERMANAGER_HPP_

#include <vector>
#include <map>
#include "ExpansionMarker.hpp"
#include "GameState/Controllers/GameController.hpp"

namespace OpenLabora
{

// std::vector wrapper that ensures that expansion marker usage is correct
class MarkerManager final
{
    using MarkerType = ExpansionMarker::MarkerType;

    using MarkerVector = std::vector<ExpansionMarker::Ptr>;
    using PlotType = Plot::PlotType;
    using Widget = sfg::Widget;
    using Window = sfg::Window;
    using Button = sfg::Button;

    std::shared_ptr<GameController> mController;
    std::map<PlotType, MarkerVector> mMarkers;
    std::multimap<PlotType, Plot> mPlotsForMarkerCreation;

    Window::Ptr mCentralConfirmWindow;
    Button::Ptr mCentralConfirmButton;
    Window::Ptr mSideConfirmWindow;
    Button::Ptr mSideConfirmButton;

    unsigned int mCentralUpdateSignalId{ 0u };
    unsigned int mSideUpdateSignalId{ 0u };

    void CreateMarker(PlotType, MarkerType);

public:
    MarkerManager(GameController::Ptr, IResourceManager&,
                  Window::Ptr central_confirm_window,
                  Button::Ptr central_confirm_button,
                  Window::Ptr side_confirm_window,
                  Button::Ptr side_confirm_button);
    ~MarkerManager();

    MarkerManager(const MarkerManager&) = delete;
    MarkerManager(MarkerManager&&) = delete;

    MarkerManager& operator=(const MarkerManager&) = delete;
    MarkerManager& operator=(MarkerManager&&) = delete;

    void UpdateMarkers();
};

} // namespace OpenLabora

#endif // MARKERMANAGER_HPP_
