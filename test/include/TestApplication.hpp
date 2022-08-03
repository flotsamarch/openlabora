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

#ifndef TESTAPPLICATION_HPP_
#define TESTAPPLICATION_HPP_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ApplicationState/ApplicationContext.hpp"

namespace test
{

namespace ol = open_labora;

struct TestApplication : public ol::ApplicationContext
{
    ol::ApplicationState& GetState() noexcept
    { return mState; }
};

} // namespace test

#endif // TESTAPPLICATION_HPP_
