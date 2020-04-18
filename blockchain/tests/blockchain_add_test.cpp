#include <gtest/gtest.h>

#include "blockchain.h"

namespace testing {

class BlockchainTest : public Test {
    void TearDown() {
        auto& blockchain = Blockchain::getInstance();
        blockchain.remove("d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");
        blockchain.remove("f74b1d6e137590d66430503966064410908100a4895024f1f2355495701abf35");
    }
};

TEST_F(BlockchainTest, add_one) {
    auto& blockchain = Blockchain::getInstance();

    node_data_t data;
    data.block_id = 1;
    strcpy(data.sha, "0000000000000000000000000000000000000000000000000000000000000000");
    data.elements_nb = 1;
    data.elements.resize(1);
    strcpy(data.elements[0], "line1");

    auto& obj = blockchain.add(data);

    ASSERT_EQ(obj.block_id, data.block_id);
    ASSERT_STREQ(obj.sha, data.sha);
    ASSERT_EQ(obj.elements_nb, data.elements_nb);
    ASSERT_EQ(obj.elements.size(), data.elements.size());
    for(size_t i=0; i<obj.elements.size(); i++) {
        ASSERT_STREQ(obj.elements[i].element, data.elements[i].element);
    }
}

TEST_F(BlockchainTest, add_with_parent) {
    auto& blockchain = Blockchain::getInstance();

    size_t size;
    ASSERT_EQ(blockchain.count(size), 0);
    ASSERT_EQ(size, 0);
    {
    node_data_t data;
    data.block_id = 1;
    strcpy(data.sha, "0000000000000000000000000000000000000000000000000000000000000000");
    data.elements_nb = 1;
    data.elements.resize(1);
    strcpy(data.elements[0], "line1");

    auto& obj = blockchain.add(data);

    ASSERT_EQ(obj.block_id, data.block_id);
    ASSERT_STREQ(obj.sha, data.sha);
    ASSERT_EQ(obj.elements_nb, data.elements_nb);
    ASSERT_EQ(obj.elements.size(), data.elements.size());
    for(size_t i=0; i<obj.elements.size(); i++) {
        ASSERT_STREQ(obj.elements[i].element, data.elements[i].element);
    }

    }

    { // d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd
    node_data_t data;
    data.block_id = 2;
    strcpy(data.sha,"d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");
    data.elements_nb = 2;
    data.elements.resize(2);
    strcpy(data.elements[0], "line1");
    strcpy(data.elements[0], "line2x");
    
    auto& obj = blockchain.add(data);

    ASSERT_EQ(obj.block_id, data.block_id);
    ASSERT_STREQ(obj.sha, data.sha);
    ASSERT_EQ(obj.elements_nb, data.elements_nb);
    ASSERT_EQ(obj.elements.size(), data.elements.size());
    for(size_t i=0; i<obj.elements.size(); i++) {
        ASSERT_STREQ(obj.elements[i].element, data.elements[i].element);
    }

    }

    ASSERT_EQ(blockchain.count(size), 2);
    ASSERT_EQ(size, 546);
}

TEST_F(BlockchainTest, add_same_twice) {
    auto& blockchain = Blockchain::getInstance();

    node_data_t data;
    data.block_id = 1;
    strcpy(data.sha, "0000000000000000000000000000000000000000000000000000000000000000");
    data.elements_nb = 1;
    data.elements.resize(1);
    strcpy(data.elements[0], "line1");

    auto& obj = blockchain.add(data);

    ASSERT_THROW(blockchain.add(data), std::out_of_range);
}

TEST_F(BlockchainTest, add_no_parent) {
    auto& blockchain = Blockchain::getInstance();

    node_data_t data;
    data.block_id = 1;
    strcpy(data.sha, "0000000000000000000000000000000000000000000000000000000000000000");
    data.elements_nb = 1;
    data.elements.resize(1);
    strcpy(data.elements[0], "line1");

    auto& obj = blockchain.add(data);

    strcpy(data.sha, "f74b1d6e137590d66430503966064410908100a4895024f1f2355495701abf35");
    ASSERT_THROW(blockchain.add(data), std::out_of_range);
}

TEST_F(BlockchainTest, zero_block_id) {
    auto& blockchain = Blockchain::getInstance();

    node_data_t data;
    data.block_id = 0;
    ASSERT_THROW(blockchain.add(data), std::invalid_argument);
}

TEST_F(BlockchainTest, empty_sha) {
    auto& blockchain = Blockchain::getInstance();

    node_data_t data;
    data.block_id = 1;
    data.elements_nb = 1;
    data.elements.resize(1);
    strcpy(data.elements[0], "line1");
    ASSERT_THROW(blockchain.add(data), std::invalid_argument);
}

TEST_F(BlockchainTest, short_sha) {
    auto& blockchain = Blockchain::getInstance();

    node_data_t data;
    data.block_id = 1;
    data.elements_nb = 1;
    strcpy(data.sha, "toshort");
    data.elements.resize(1);
    strcpy(data.elements[0], "line1");
    ASSERT_THROW(blockchain.add(data), std::invalid_argument);
}

TEST_F(BlockchainTest, too_long_sha) {
    auto& blockchain = Blockchain::getInstance();

    node_data_t data;
    data.block_id = 1;
    data.elements_nb = 1;
    strcpy(data.sha, "10000000000000000000000000000000000000000000000000000000000000001");
    data.elements.resize(1);
    strcpy(data.elements[0], "line1");
    ASSERT_THROW(blockchain.add(data), std::invalid_argument);
}

}
