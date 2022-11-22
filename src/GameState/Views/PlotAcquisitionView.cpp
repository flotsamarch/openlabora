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

#include "GameState/Views/PlotAcquisitionView.hpp"
#include "GUI/Common.hpp"

namespace open_labora
{

namespace plot_acquisition
{

using TextAlignment = Label::HorizontalAlignment;
using CGuiString = const GuiString;

constexpr auto kButtonsWidth = 137;
constexpr auto kChooseOneWindowHeight = 166;
constexpr auto kConfirmWindowHeight = 108;
constexpr auto kChooseOneTextHeight = 51;
constexpr auto kConfirmTextHeight = 44;
constexpr auto kChooseOneContentHeight = 193;

inline static CGuiString kSelectText{ "Select which plot type you want to buy" };
inline static CGuiString kConfirmText{ "Buy selected plot?" };

constexpr std::array kChooseOneButtonValues
{
    plot::TypeId{ plot::kCentral },
    plot::TypeId{ plot::kCentralAlt }
};

CreateWindowResult createWindowChooseOne(CreateWindowParams& params)
{
    const auto game_window = params.game_window;

    auto content_group = Group::create();

    auto window_text_hbox = HBox::create();
    auto window_text = Label::create(kSelectText);
    window_text->setHorizontalAlignment(TextAlignment::Center);
    gui::setDynamicTextSize(window_text, game_window, gui::getBigTextSize);

    window_text_hbox->add(window_text);
    window_text_hbox->setPosition(0, 0);
    window_text_hbox->setHeight(kChooseOneTextHeight);

    auto radio_group = RadioGroup::create();

    constexpr auto height = kChooseOneWindowHeight;
    auto window = ConfirmationWindow{ game_window, "15%", height };

    const auto begin = kChooseOneButtonValues.cbegin();
    auto last = RadioButton::Ptr{ nullptr };
    for (auto it = begin, end = kChooseOneButtonValues.cend(); it != end; ++it)
    {
        auto id = *it;
        auto text = std::ostringstream{ "central_lot_", std::ios_base::ate };
        text << static_cast<size_t>(id);

        auto button = RadioButton::create();
        button->setText(text.str());

        radio_group->add(button);
        if (it != begin && last != nullptr) {
            button->setPosition(0, bindBottom(last) + gui::kMargin);
        }

        const auto result = params.button_to_type_id.try_emplace(button, id);
        assert(result.second);

        button->onCheck([enable_button = window.GetEnableConfirmButtonCallback()]
        {
            enable_button();
        });

        last = button;
    };

    const auto buttons_y = bindBottom(window_text_hbox) + gui::kMargin;
    radio_group->setPosition(0, buttons_y);
    radio_group->setHeight(kButtonsWidth);

    content_group->add(window_text_hbox);
    content_group->add(radio_group);

    content_group->setSize("97%", kChooseOneContentHeight);

    window.SetContent(content_group);

    auto confirm_action =
    [radio_group,
     &button_to_type_id = params.button_to_type_id,
     hide_visible = params.hide_visible_callback,
     acquire_plot = params.acquire_plot_callback] () mutable
    {
        const auto button = radio_group->getCheckedRadioButton();
        assert(button != nullptr);
        assert(button_to_type_id.contains(button));

        const auto type_id = button_to_type_id.find(button)->second;
        auto params = plot::AcquirePlotParams{ type_id };
        acquire_plot(params);
        hide_visible();
    };

    window.SetConfirmButtonEnabled(false);
    window.SetConfirmButtonAction(confirm_action);
    window.SetDeclineButtonAction(params.decline_action);

    return{ MenuWindowId::ChooseOne, std::move(window) };
};

CreateWindowResult createWindowConfirm(CreateWindowParams& params)
{
    auto game_window = params.game_window;

    auto main_content{ HBox::create() };

    auto window_text{ Label::create(kConfirmText) };
    window_text->setHorizontalAlignment(TextAlignment::Center);
    window_text->setPosition(0, 0);
    gui::setDynamicTextSize(window_text, game_window, gui::getBigTextSize);

    main_content->add(window_text);
    main_content->setSize("97%", kConfirmTextHeight);

    auto window = ConfirmationWindow{ game_window, "15%", kConfirmWindowHeight };
    window.SetContent(main_content);

    auto confirm_action =
    [hide_visible = params.hide_visible_callback,
     acquire_plot = params.acquire_plot_callback]
    {
        auto params = plot::AcquirePlotParams{ plot::TypeId{ 0u } };
        acquire_plot(params);
        hide_visible();
    };

    window.SetConfirmButtonAction(confirm_action);
    window.SetDeclineButtonAction(params.decline_action);

    return{ MenuWindowId::Confirm, std::move(window) };
};

} // namespace plot_acquisition

} // namespace open_labora
