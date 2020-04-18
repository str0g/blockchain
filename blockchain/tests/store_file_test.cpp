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
#include <stdlib.h>
#include <dirent.h>

#include "finally.h"
#include "blockchain.h"
#include "store_to_file.h"
#include "load_from_file.h"

namespace testing {

class ChangeStoreLocation : public StoreToFile {
    public:
        ChangeStoreLocation() {
            char tx[] = "/tmp/blockchain_store.XXXXXX";
            auto px = mkdtemp(tx);
            if(px == nullptr) {
                std::cerr << "mkdtemp failed: " << strerror(errno) << std::endl;
            }
            temp_dir = px;

            std::cout << temp_dir << std::endl;
            set_path(temp_dir + "/");
        }

        int count_files() {
            int ret = 0;
            DIR *d = opendir(temp_dir.c_str());
            if(!d) {
                std::cout << "Could not open " << temp_dir << " " << strerror(errno) << std::endl;
                return -1;
            }
            auto clean_dir = finally([&] {
                closedir(d);
            });

            dirent *dir;
            while((dir=readdir(d)) != nullptr) {
                if(dir->d_type == DT_REG)
                    ret++;
            }

            return ret;
        }

        std::string temp_dir;
};

class ChangeLoadLocation : public LoadFromFile {
    public:
        ChangeLoadLocation(const std::string& str) : temp_dir(str+"/") {
            set_path(temp_dir);
        }

        std::string temp_dir;
};

class BlockchainTest : public Test {
    void SetUp() {
        auto& blockchain = Blockchain::getInstance();

        node_data_t data;
        data.block_id = 1;
        strcpy(data.sha, "0000000000000000000000000000000000000000000000000000000000000000");
        data.elements_nb = 1;
        data.elements.resize(1);
        strcpy(data.elements[0], "line1");

        auto& obj = blockchain.add(data);
    }
    void TearDown() {
        auto& blockchain = Blockchain::getInstance();
        blockchain.remove("d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");
        blockchain.remove("6a4388448f39ebdcf030aa80bcd9b246e31a9c66c07333c5274a88645f5de87a");
    }
};

class BlockchainTestLoad : public Test {
    void SetUp() {
        auto& blockchain = Blockchain::getInstance();
        blockchain.remove("d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");
        blockchain.remove("6a4388448f39ebdcf030aa80bcd9b246e31a9c66c07333c5274a88645f5de87a");
    }
    void teardown() {
        auto& blockchain = Blockchain::getInstance();
        blockchain.remove("d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");
        blockchain.remove("6a4388448f39ebdcf030aa80bcd9b246e31a9c66c07333c5274a88645f5de87a");
    }
};

TEST_F(BlockchainTest, Store) {
    auto& blockchain = Blockchain::getInstance();
    blockchain.set_custom_store(new ChangeStoreLocation());
    blockchain.store();
}

TEST_F(BlockchainTestLoad, Load) {
    auto& blockchain = Blockchain::getInstance();
    size_t size;
    ASSERT_EQ(blockchain.count(size), 0);
    ASSERT_EQ(size, 0);
    char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) == nullptr)
        std::cerr << "could not get current directory" << std::endl;
    auto load = new ChangeLoadLocation(std::string(cwd) + "/chain_data");
    blockchain.set_custom_load(load);
    blockchain.load();
    ASSERT_EQ(blockchain.count(size), 2);
    ASSERT_EQ(size, 546);
}

TEST_F(BlockchainTest, Store_2) {
    node_data_t data;
    data.block_id = 2;
    strcpy(data.sha,"d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");
    data.elements_nb = 2;
    data.elements.resize(2);
    strcpy(data.elements[0], "line1");
    strcpy(data.elements[1], "line2x");

    auto& blockchain = Blockchain::getInstance();
    auto& obj = blockchain.add(data);
    
    auto store = new ChangeStoreLocation();

    blockchain.set_custom_store(store);
    blockchain.store();

    ASSERT_EQ(store->count_files(), 2);
}

TEST_F(BlockchainTest, StoreRemoveLoadVerifyNotOk) {
    auto& blockchain = Blockchain::getInstance();
    size_t size;
    ASSERT_EQ(blockchain.count(size), 1);
    ASSERT_EQ(size, 209);

    node_data_t data;
    data.block_id = 2;
    strcpy(data.sha,"d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");
    data.elements_nb = 2;
    data.elements.resize(2);
    strcpy(data.elements[0], "line1");
    strcpy(data.elements[1], "line2x");

    blockchain.add(data);
    ASSERT_EQ(blockchain.count(size), 2);
    ASSERT_EQ(size, 546);

    auto store = new ChangeStoreLocation();
    blockchain.set_custom_store(store);
    blockchain.store();
    ASSERT_EQ(store->count_files(), 2);

    blockchain.remove("d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");
    blockchain.remove("6a4388448f39ebdcf030aa80bcd9b246e31a9c66c07333c5274a88645f5de87a");
    ASSERT_EQ(blockchain.count(size), 0);
    ASSERT_EQ(size, 0);

    auto load = new ChangeLoadLocation(store->temp_dir);
    blockchain.set_custom_load(load);
    blockchain.load();
    auto v = blockchain.verify();
    ASSERT_EQ(blockchain.count(size), 2);
    ASSERT_EQ(size, 546);
    ASSERT_EQ(v.size(), 1);
    ASSERT_STREQ(v[0], "0000000000000000000000000000000000000000000000000000000000000000");
}

    //blockchain.remove("f74b1d6e137590d66430503966064410908100a4895024f1f2355495701abf35");
}
