#include <gtest/gtest.h>

#include "blockchain.h"

namespace testing {

class BlockchainTest : public Test {
    void TearDown() {
        auto& blockchain = Blockchain::getInstance();
        blockchain.remove(1);
        blockchain.remove(2);
    }
};

TEST_F(BlockchainTest, add_one) {
    auto& blockchain = Blockchain::getInstance();

    node_data_t data;
    data.header.index = 1;
    strcpy(data.header.sha, "0000000000000000000000000000000000000000000000000000000000000000");
    data.header.elements_nb = 1;
    data.elements.resize(1);
    strcpy(data.elements[0], "line1");

    auto& obj = blockchain.add(data);

    ASSERT_EQ(obj.header.index, data.header.index);
    ASSERT_STREQ(obj.header.sha, data.header.sha);
    ASSERT_EQ(obj.header.elements_nb, data.header.elements_nb);
    ASSERT_EQ(obj.elements.size(), data.elements.size());
    for(size_t i=0; i<obj.elements.size(); i++) {
        ASSERT_STREQ(obj.elements[i].element, data.elements[i].element);
    }
}

TEST_F(BlockchainTest, add_with_parent) {
    auto& blockchain = Blockchain::getInstance();

    {
    node_data_t data;
    data.header.index = 1;
    strcpy(data.header.sha, "0000000000000000000000000000000000000000000000000000000000000000");
    data.header.elements_nb = 1;
    data.elements.resize(1);
    strcpy(data.elements[0], "line1");

    auto& obj = blockchain.add(data);

    ASSERT_EQ(obj.header.index, data.header.index);
    ASSERT_STREQ(obj.header.sha, data.header.sha);
    ASSERT_EQ(obj.header.elements_nb, data.header.elements_nb);
    ASSERT_EQ(obj.elements.size(), data.elements.size());
    for(size_t i=0; i<obj.elements.size(); i++) {
        ASSERT_STREQ(obj.elements[i].element, data.elements[i].element);
    }

    }
    {
    node_data_t data;
    data.header.index = 2;
    strcpy(data.header.sha, "1000000000000000000000000000000000000000000000000000000000000000");
    data.header.elements_nb = 2;
    data.elements.resize(2);
    strcpy(data.elements[0], "line1");
    strcpy(data.elements[0], "line2x");
    
    auto& obj = blockchain.add(data);

    ASSERT_EQ(obj.header.index, data.header.index);
    ASSERT_STREQ(obj.header.sha, data.header.sha);
    ASSERT_EQ(obj.header.elements_nb, data.header.elements_nb);
    ASSERT_EQ(obj.elements.size(), data.elements.size());
    for(size_t i=0; i<obj.elements.size(); i++) {
        ASSERT_STREQ(obj.elements[i].element, data.elements[i].element);
    }

    }
    //@TODO not implemented
}

TEST_F(BlockchainTest, add_same_twice) {
    auto& blockchain = Blockchain::getInstance();

    node_data_t data;
    data.header.index = 1;
    strcpy(data.header.sha, "0000000000000000000000000000000000000000000000000000000000000000");
    data.header.elements_nb = 1;
    data.elements.resize(1);
    strcpy(data.elements[0], "line1");

    auto& obj = blockchain.add(data);

    ASSERT_EQ(obj.header.index, data.header.index);
    ASSERT_STREQ(obj.header.sha, data.header.sha);
    ASSERT_EQ(obj.header.elements_nb, data.header.elements_nb);
    ASSERT_EQ(obj.elements.size(), data.elements.size());
    for(size_t i=0; i<obj.elements.size(); i++) {
        ASSERT_STREQ(obj.elements[i].element, data.elements[i].element);
    }
    
    ASSERT_THROW(blockchain.add(data), std::invalid_argument);

    data.header.index = 2;
    ASSERT_THROW(blockchain.add(data), std::invalid_argument);

    data.header.index = 1;
    strcpy(data.header.sha, "1000000000000000000000000000000000000000000000000000000000000000");
    ASSERT_THROW(blockchain.add(data), std::invalid_argument);
}

TEST_F(BlockchainTest, zero_index) {
    auto& blockchain = Blockchain::getInstance();

    node_data_t data;
    data.header.index = 0;
    ASSERT_THROW(blockchain.add(data), std::invalid_argument);
}

TEST_F(BlockchainTest, empty_sha) {
    auto& blockchain = Blockchain::getInstance();

    node_data_t data;
    data.header.index = 1;
    data.header.elements_nb = 1;
    data.elements.resize(1);
    strcpy(data.elements[0], "line1");
    ASSERT_THROW(blockchain.add(data), std::invalid_argument);
}

}
