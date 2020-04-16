#include <gtest/gtest.h>

#include "blockchain.h"

namespace testing {

class BlockchainTest : public Test {
    void SetUp() {
        auto& blockchain = Blockchain::getInstance();
        node_data_t data;
        data.header.index = 1;
        strcpy(data.header.sha, "0000000000000000000000000000000000000000000000000000000000000000");
        data.header.elements_nb = 1;
        data.elements.resize(1);
        strcpy(data.elements[0], "line1");
        
        blockchain.add(data);
    }
};

TEST_F(BlockchainTest, remove_by_index) {
    auto& blockchain = Blockchain::getInstance();
    ASSERT_EQ(blockchain.count(), 1);

    blockchain.remove(1);

    ASSERT_EQ(blockchain.count(), 0);
}

TEST_F(BlockchainTest, remove_by_sha) {
    auto& blockchain = Blockchain::getInstance();
    ASSERT_EQ(blockchain.count(), 1);

    blockchain.remove("0000000000000000000000000000000000000000000000000000000000000000");

    ASSERT_EQ(blockchain.count(), 0);
}

TEST_F(BlockchainTest, remove_mixed) {
    auto& blockchain = Blockchain::getInstance();
    node_data_t data;
    data.header.index = 2;
    strcpy(data.header.sha, "1000000000000000000000000000000000000000000000000000000000000000");
    data.header.elements_nb = 1;
    data.elements.resize(1);
    strcpy(data.elements[0], "line2");
        
    blockchain.add(data);
    ASSERT_EQ(blockchain.count(), 2);

    blockchain.remove("0000000000000000000000000000000000000000000000000000000000000000");

    ASSERT_EQ(blockchain.count(), 1);
    blockchain.remove(2);
    ASSERT_EQ(blockchain.count(), 0);
}

}
