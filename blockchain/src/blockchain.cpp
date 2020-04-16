#include "blockchain.h"

#include <iostream>

void StoreToFile::operator()(const node_data_t&, void *extra_args) {}
void LoadFromFile::operator()(node_data_t&, void *extra_args) {}

Blockchain& Blockchain::getInstance() {
    static Blockchain out;
    return out;
}

Blockchain::Blockchain() : _load(new LoadFromFile()), _store(new StoreToFile) {
    std::cout << "Blockchain initialized" << std::endl;
}

Blockchain::~Blockchain() {
    delete _load;
    delete _store;
}

void Blockchain::set_custom_load(LoadInterface* obj) {
    delete _load;
    _load = obj;
}

void Blockchain::set_custom_store(StoreInterface* obj) {
    delete _store;
    _store = obj;
}

const node_data_t& Blockchain::add(node_data_t& obj) {
    if (!obj.header.index) {
        throw std::invalid_argument("zero is forbitten");
    }
    if (strnlen(obj.header.sha, sizeof(node_data_t::header_t::sha)) != (sizeof(node_data_t::header_t::sha)-1)) {
        throw std::invalid_argument("invalid sha");
    }
    if (chain.find(obj.header.index) != chain.end()) {
        throw std::invalid_argument("index already exist");
    }
    if (find(obj.header.sha) != chain.end()) {
        throw std::invalid_argument("sha already exist");
    }

    auto parent = chain.find(obj.header.index-1);
    if (parent == chain.end()) {
        if (not chain.empty()) {
            throw std::invalid_argument("parent has not been found");
        }
    } else {
        if(!strncmp(obj.header.sha, parent->second.header.sha, sizeof(node_data_t::header_t::sha))) {
            throw std::invalid_argument("not your parent");
        }
    }
    
    //@TODO openssl parent sha256 obj.header.sha

    auto it = chain.emplace(obj.header.index, std::move(obj));
    return it.first->second;
}

void Blockchain::remove(size_t index) {
    chain.erase(index);
}

void Blockchain::remove(const char* sha) {
    auto it = find(sha);

    if(it != chain.end()) {
        chain.erase(it);
    }
}

Blockchain::chain_it Blockchain::find(const char* sha) {
    for(auto it=chain.begin(); it!=chain.end(); it++) {
        if(!strncmp(it->second.header.sha, sha, sizeof(node_data_t::header_t::sha))) {
                return it;
        }
    }
    return chain.end();
}

size_t Blockchain::count() const {
    return chain.size();
}
