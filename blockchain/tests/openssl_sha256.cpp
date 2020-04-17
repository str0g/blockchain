#include <gtest/gtest.h>
#include <cstring>

#include "blockchain.h"

namespace testing {

struct exp_t {
    std::string data;
    const char* sha;
};


TEST_F(Test, sha256) {
    exp_t exp {"test", "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08"};
    auto& blockchain = Blockchain::getInstance();

    auto sig = blockchain.get_sha256(exp.data);

    ASSERT_STREQ(sig.c_str(), exp.sha);
}

};
