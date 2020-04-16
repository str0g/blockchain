#include <gtest/gtest.h>

#include "blockchain.h"

namespace testing {

TEST_F(Test, Singleton) {
    auto& obj = Blockchain::getInstance();
    auto& obj2 = Blockchain::getInstance();

    ASSERT_EQ(&obj, &obj2);
}

}
