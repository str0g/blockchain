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
    size_t size;
    ASSERT_EQ(blockchain.count(size), 1);
    ASSERT_EQ(size, 209);

    blockchain.remove("d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");

    ASSERT_EQ(blockchain.count(size), 0);
    ASSERT_EQ(size, 0);
}

TEST_F(BlockchainTest, remove_two) {
    auto& blockchain = Blockchain::getInstance();
    node_data_t data;
    data.block_id = 2;
    strcpy(data.sha, "d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");
    data.elements_nb = 1;
    data.elements.resize(1);
    strcpy(data.elements[0], "line2");

    size_t size;
    blockchain.add(data);
    ASSERT_EQ(blockchain.count(size), 2);
    ASSERT_EQ(size, 418);

    blockchain.remove("d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");

    ASSERT_EQ(blockchain.count(size), 1);
    ASSERT_EQ(size, 209);
    blockchain.remove("b160fc9b85d33f334a2c85c0398523ea9a8be0dc0da758c30ddeccd376daac08");
    ASSERT_EQ(blockchain.count(size), 0);
    ASSERT_EQ(size, 0);
}

TEST_F(BlockchainTest, remove_invalid_sha) {
    auto& blockchain = Blockchain::getInstance();

    size_t size;
    ASSERT_EQ(blockchain.count(size), 1);
    ASSERT_EQ(size, 209);
    blockchain.remove("b160fc9b85d33f334a2c85c0398523ea9a8be0dc0da758c30ddeccd376daac08");
    ASSERT_EQ(blockchain.count(size), 1);
    ASSERT_EQ(size, 209);

    ASSERT_THROW(blockchain.remove("invalid_length"), std::invalid_argument);
}

}
