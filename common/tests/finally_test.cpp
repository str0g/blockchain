#include <gtest/gtest.h>
#include "finally.h"

namespace testing {

TEST_F(Test, finally_test) {
    int *obj = new int[15];

    {
        auto clean = finally([&]() {
            delete[] obj;
            obj = nullptr;
        });
    }

    ASSERT_EQ(obj, nullptr);
}

}
