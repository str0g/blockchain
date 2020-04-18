#include "store_to_file.h"
#include <fstream>

void StoreToFile::operator()(const chain_pair& it, void *extra_args) {
        const node_data_t& data = it.second;
        std::string file = path + std::to_string(data.block_id) + "_" + it.first;

        auto v = data.serialize();

        //TODO error checks...
        std::ofstream f(file, std::ios::binary);
        f.write((const char*)&v[0], v.size());
        f.close();
}
//@TODO WITH_TEST
void StoreToFile::set_path(const std::string& _path) {
    path = _path;
}

StoreToFile::~StoreToFile() {}
//
