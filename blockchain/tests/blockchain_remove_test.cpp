#include <gtest/gtest.h>

#include "blockchain.h"

namespace testing {

class BlockchainTest : public Test {
    void SetUp() {
        auto& blockchain = Blockchain::getInstance();
        node_data_t data;
        data.block_id = 1;
        strcpy(data.sha, "0000000000000000000000000000000000000000000000000000000000000000");
        data.elements_nb = 1;
        data.elements.resize(1);
        strcpy(data.elements[0], "line1");
        
        blockchain.add(data);
    }
};

TEST_F(BlockchainTest, remove_by_sha) {
    auto& blockchain = Blockchain::getInstance();
    ASSERT_EQ(blockchain.count(), 1);

    blockchain.remove("d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");

    ASSERT_EQ(blockchain.count(), 0);
}

TEST_F(BlockchainTest, remove_two) {
    auto& blockchain = Blockchain::getInstance();
    node_data_t data;
    data.block_id = 2;
    strcpy(data.sha, "d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");
    data.elements_nb = 1;
    data.elements.resize(1);
    strcpy(data.elements[0], "line2");
        
    blockchain.add(data);
    ASSERT_EQ(blockchain.count(), 2);

    blockchain.remove("d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");

    ASSERT_EQ(blockchain.count(), 1);
    blockchain.remove("b160fc9b85d33f334a2c85c0398523ea9a8be0dc0da758c30ddeccd376daac08");
    ASSERT_EQ(blockchain.count(), 0);
}

TEST_F(BlockchainTest, remove_invalid_sha) {
    auto& blockchain = Blockchain::getInstance();

    ASSERT_EQ(blockchain.count(), 1);
    blockchain.remove("b160fc9b85d33f334a2c85c0398523ea9a8be0dc0da758c30ddeccd376daac08");
    ASSERT_EQ(blockchain.count(), 1);

    ASSERT_THROW(blockchain.remove("invalid_length"), std::invalid_argument);
}

}
