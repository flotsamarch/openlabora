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

#ifndef MATCHERS_HPP_
#define MATCHERS_HPP_

#include <gmock/gmock.h>
#include "LibTypedefs.hpp"

namespace test
{

namespace ol = open_labora;

MATCHER_P(Vector2fEq, vector, "")
{
    using testing::FloatEq;
    using testing::Field;
    using testing::AllOf;

    return ExplainMatchResult(
        AllOf(Field("x", &ol::Vector2f::x, FloatEq(vector.x)),
              Field("y", &ol::Vector2f::y, FloatEq(vector.y))),
              arg, result_listener);
}


} // namespace test

#endif // MATCHERS_HPP_
