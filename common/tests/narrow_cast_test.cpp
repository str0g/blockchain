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
