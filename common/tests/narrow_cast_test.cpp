/********************************************************************************
*    Blockchain is a sample program to to introduce into blockchain technology  *
*    Copyright (C) 2020  Łukasz Buśko                                           *
*                                                                               *
*    This program is free software: you can redistribute it and/or modify       *
*    it under the terms of the GNU General Public License as published by       *
*    the Free Software Foundation, either version 3 of the License, or          *
*    (at your option) any later version.                                        *
*                                                                               *
*    This program is distributed in the hope that it will be useful,            *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*    GNU General Public License for more details.                               *
*                                                                               *
*    You should have received a copy of the GNU General Public License          *
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.      *
*********************************************************************************/

#include <gtest/gtest.h>
#include <limits>

#include "narrow_cast.h"

namespace testing {

TEST_F(Test, platform_test) {
    auto max = std::numeric_limits<unsigned short>::max();
    short ret_max = static_cast<short>(max);
    ASSERT_EQ(-1, ret_max);

    auto min = std::numeric_limits<unsigned short>::min();
    short ret_min = static_cast<short>(min);
    ASSERT_EQ(min, ret_min);
}

TEST_F(Test, narrow_cast) {
    auto max = std::numeric_limits<unsigned short>::max();
    ASSERT_THROW(
        narrow_cast<short>(max), std::out_of_range
        );

    auto min = std::numeric_limits<unsigned short>::min();
    ASSERT_NO_THROW(narrow_cast<short>(min));
    short ret_min = narrow_cast<short>(min);
    ASSERT_EQ(min, ret_min);
}

}
