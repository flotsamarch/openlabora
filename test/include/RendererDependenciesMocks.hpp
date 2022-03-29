#ifndef TESTRENDERERDEPENDENCIES_HPP_
#define TESTRENDERERDEPENDENCIES_HPP_

#include <gmock/gmock.h>
#include <utility>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/String.hpp>

namespace Test
{

/**
 * Mock class for render target of graphics library. Template parameters allow
 * to control method calls expectations without dependency injection.
 *
 * @tparam TEnableExpectations - Boolean indicating whether expectations are
 *    set up in constructor or not. Unset expectations do not cause tests to fail
 *
 * @tparam TEnable*MethodName*Expectations - Boolean indicating whether to setup
 *     expectation on a call to *MethodName()*. Unset expectations on a call mean
 *     that call is uninteresting and will not cause a test failure.
 *
 * @tparam T*MethodName*CallCount - Amount of expected calls to *MethodName()*
 *
 * @tparam T*MethodName*TrueCount - Amount of calls to *MethodName()* that return
 *     true
 *
 * @tparam TDisplayClearCallCount - Expected call amount to display() and
 *     clear() methods. The parameter is applied to two methods because amount
 *     of calls should always be the same
 */
template<bool TEnableExpectations,
         bool TEnableIsOpenExpectations = false,
         uint32_t TIsOpenCallCount = 0u,
         uint32_t TIsOpenTrueCount = 0u,
         bool TEnablePollEventExpectations = false,
         uint32_t TPollEventCallCount = 0u,
         uint32_t TPollEventTrueCount = 0u,
         uint32_t TDisplayClearCallCount = 0u,
         uint32_t TDrawCallCount = 0u,
         uint32_t TGetSizeCallCount = 0u>
class WindowMock
{

public:
    WindowMock()
    {
        using ::testing::Return;
        using ::testing::_;
        using ::testing::Mock;

        if constexpr (TEnableExpectations) {
            EXPECT_CALL(*this, create);

            EXPECT_CALL(*this, setFramerateLimit);

            EXPECT_CALL(*this, setVerticalSyncEnabled);

            EXPECT_CALL(*this, resetGLStates());

            EXPECT_CALL(*this, close());

            if (TEnableIsOpenExpectations) {
                static_assert(TIsOpenTrueCount <= TIsOpenCallCount);
                const auto false_count = TIsOpenCallCount - TIsOpenTrueCount;

                if (false_count > 0) {
                    EXPECT_CALL(*this, isOpen())
                        .Times(false_count)
                        .WillRepeatedly(Return(false));
                }

                if (TIsOpenTrueCount > 0) {
                    EXPECT_CALL(*this, isOpen())
                        .Times(TIsOpenTrueCount)
                        .WillRepeatedly(Return(true))
                        .RetiresOnSaturation();
                }
            } else {
                ON_CALL(*this, isOpen())
                    .WillByDefault(Return(false));
            }

            if (TEnablePollEventExpectations) {
                static_assert(TPollEventTrueCount <= TPollEventCallCount);
                const auto false_count =
                    TPollEventCallCount - TPollEventTrueCount;

                if (false_count > 0) {
                    EXPECT_CALL(*this, pollEvent)
                        .Times(false_count)
                        .WillRepeatedly(Return(false));
                }
                if (TPollEventTrueCount > 0) {
                    EXPECT_CALL(*this, pollEvent)
                        .Times(TPollEventTrueCount)
                        .WillRepeatedly(Return(true))
                        .RetiresOnSaturation();
                }
            } else {
                ON_CALL(*this, pollEvent)
                    .WillByDefault(Return(false));
            }

            EXPECT_CALL(*this, display())
                .Times(TDisplayClearCallCount);

            EXPECT_CALL(*this, clear())
                .Times(TDisplayClearCallCount);

            EXPECT_CALL(*this, draw)
                .Times(TDrawCallCount);

            auto&& expect_size = EXPECT_CALL(*this, getSize())
                .Times(TGetSizeCallCount);

            if (TGetSizeCallCount) {
                expect_size.WillRepeatedly(Return(sf::Vector2u{ 0, 0 }));
            }
        } else {
            Mock::AllowLeak(this);

            ON_CALL(*this, pollEvent)
                .WillByDefault(Return(false));

            ON_CALL(*this, isOpen())
                .WillByDefault(Return(false));
        }
    }
    virtual ~WindowMock() {};
    MOCK_METHOD(void, create, (sf::VideoMode, const std::string&, uint32_t), ());
    MOCK_METHOD(void, setFramerateLimit, (uint32_t), ());
    MOCK_METHOD(void, setVerticalSyncEnabled, (bool), ());
    MOCK_METHOD(void, resetGLStates, (), ());
    MOCK_METHOD(void, display, (), ());
    MOCK_METHOD(void, close, (), ());
    MOCK_METHOD(bool, isOpen, (), (const));
    MOCK_METHOD(void, clear, (), ());
    MOCK_METHOD(void, draw, (const sf::Drawable&), ());
    MOCK_METHOD(sf::Vector2u, getSize, (), (const));
    MOCK_METHOD(bool, pollEvent, (sf::Event&), ());
};


/**
 * Mock class for GUI library. Template parameters allow to control function
 * calls expectations without dependency injection.
 *
 * @tparam TWindow - Render target class of graphics library
 *
 * @tparam TEnableExpectations - Boolean indicating whether expectations are
 *    set up in constructor or not. Unset expectations do not cause tests to fail
 *
 * @tparam TEnable*MethodName*Expectations - Boolean indicating whether to setup
 *     expectation on a call to *MethodName()*. Unset expectations on a call mean
 *     that call is uninteresting and will not cause a test failure.
 *
 * @tparam T*MethodName*CallCount - Amount of expected calls to *MethodName()*
 *
 * @tparam T*MethodName*TrueCount - Amount of calls to *MethodName()* that return
 *     true
 *
 * @tparam THandleEventCallsSequence - Sequence of integer pairs. Every odd
 *     element of sequence represents amount of times when handleEvent() function
 *     returns false. Every even element of sequence represents amount of times
 *     when handleEvent() returns true. Sequencing in pairs allows to alternate
 *     how many times handleEvent() returns true or false and in what order.
 */
template<class TWindow,
         bool TEnableExpectations,
         uint32_t TDrawCallCount = 0u,
         uint32_t TRemoveAllWidgetsCallCount = 0u,
         uint32_t... THandleEventCallsSequence>
class GuiMock
{
    template<uint32_t TReturnFalseCount,
             uint32_t TReturnTrueCount,
             uint32_t... TTail>
    constexpr void SetupHandleEventExpectations()
    {
        using ::testing::Return;

        if (TReturnFalseCount > 0) {
            EXPECT_CALL(*this, handleEvent)
                .Times(TReturnFalseCount)
                .WillRepeatedly(Return(false))
                .RetiresOnSaturation();
        }

        if (TReturnTrueCount > 0) {
            EXPECT_CALL(*this, handleEvent)
                .Times(TReturnTrueCount)
                .WillRepeatedly(Return(true))
                .RetiresOnSaturation();
        }

        if constexpr (sizeof...(TTail) > 1) {
            SetupHandleEventExpectations(TTail...);
        }
    }

public:
    GuiMock() {
        using ::testing::Return;
        using ::testing::Mock;

        if constexpr (TEnableExpectations) {
            EXPECT_CALL(*this, setTarget)
                .Times(1);

            EXPECT_CALL(*this, draw())
                .Times(TDrawCallCount);

            EXPECT_CALL(*this, removeAllWidgets())
                .Times(TRemoveAllWidgetsCallCount);

            if constexpr (sizeof...(THandleEventCallsSequence) > 1) {
                SetupHandleEventExpectations<THandleEventCallsSequence...>();
            }
        } else {
            Mock::AllowLeak(this);

            ON_CALL(*this, handleEvent)
                .WillByDefault(Return(false));
        }
    }
    virtual ~GuiMock() {};
    MOCK_METHOD(void, setTarget, (TWindow&), ());
    MOCK_METHOD(bool, handleEvent, (sf::Event), ());
    MOCK_METHOD(void, draw, (), ());
    MOCK_METHOD(void, add, (tgui::Widget::Ptr, const tgui::String&), ());
    MOCK_METHOD(void, removeAllWidgets, (), ());
};

} // namespace Test

#endif // TESTRENDERERDEPENDENCIES_HPP_
