#include <gtest/gtest.h>
#include <stdlib.h>


#include "blockchain.h"
#include "store_to_file.h"
#include "load_from_file.h"

namespace testing {

class ChangeStoreLocation : public StoreToFile {
    public:
        ChangeStoreLocation() : destruct(true) {
            char tx[] = "/tmp/blockchain_store.XXXXXX";
            px = mkdtemp(tx);
            if(px == nullptr) {
                std::cerr << "mkdtemp failed: " << strerror(errno) << std::endl;
            }
            std::string _path {px};
            _path += '/';
            std::cout << _path << std::endl;
            swap_path(_path);
        }

        ~ChangeStoreLocation() {
            if(destruct) {
                rmdir(px);
                free(px);
            }
        }

        char *px;
        bool destruct;
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
        blockchain.remove("f74b1d6e137590d66430503966064410908100a4895024f1f2355495701abf35");
    }
};

TEST_F(BlockchainTest, Store) {
    auto& blockchain = Blockchain::getInstance();
    blockchain.set_custom_store(new ChangeStoreLocation());
    blockchain.store();
}

TEST_F(BlockchainTest, Store_2) {
    node_data_t data;
    data.block_id = 2;
    strcpy(data.sha,"d49c6e345abe45eee2cd0adf49c5049801971eec65256ecef8f08d97e2ee54bd");
    data.elements_nb = 2;
    data.elements.resize(2);
    strcpy(data.elements[0], "line1");
    strcpy(data.elements[0], "line2x");
    
//    auto& obj = blockchain.add(data);
}

TEST_F(BlockchainTest, ReplaceStoreModelAndSave) {
    auto& blockchain = Blockchain::getInstance();
    blockchain.set_custom_store(new StoreToFile());
}

}
