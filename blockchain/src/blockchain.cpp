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

#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "load_from_file.h"
#include "store_to_file.h"
#include "delete_file.h"
#include "blockchain.h"


Blockchain& Blockchain::getInstance() {
    static Blockchain out;
    return out;
}

Blockchain::Blockchain() : _load(new LoadFromFile()), _store(new StoreToFile), _delete(new DeleteFile) {
    std::cout << "Blockchain initialized" << std::endl;
}

Blockchain::~Blockchain() {
    store();

    delete _load;
    delete _store;
    delete _delete;
}

void Blockchain::set_custom_load(LoadInterface* obj) {
    if(obj == nullptr)
        throw std::invalid_argument("instance of LoadInterface is required");

    delete _load;
    _load = obj;
}

void Blockchain::set_custom_store(StoreInterface* obj) {
    if(obj == nullptr)
        throw std::invalid_argument("instance of StoreInterface is required");

    delete _store;
    _store = obj;
}

const node_data_t& Blockchain::add(node_data_t& obj) {
    if (!obj.block_id) {
        throw std::invalid_argument("zero is forbitten");
    }
    if (strnlen(obj.sha, sizeof(node_data_t::sha)) != (sizeof(node_data_t::sha)-1)) {
        throw std::invalid_argument("invalid sha");
    }

    if(!chain.empty())
        auto parent = chain.at(obj.sha);

    auto hash = get_sha256(obj.serialize());

    if(chain.find(hash) != chain.end()) {
        throw std::invalid_argument("already exist");
    }

    std::cout << "obj created " << hash << std::endl;
    auto it = chain.emplace(std::move(hash), std::move(obj));

    return it.first->second;
}

void Blockchain::remove(const std::string& sha) {
    if(sha.length() != sizeof(node_data_t::sha)-1) {
        throw std::invalid_argument("expected sha256");
    }

    auto obj = chain.find(sha);
    if(obj == chain.end())
        return;

    auto child = find_child(sha);
    if(child != chain.end())
        std::cout << "New orphane " << child->first << std::endl;

    (*_delete)(obj->first, obj->second);
    chain.erase(obj);
}

chain_it Blockchain::find_child(const std::string& sha) {
    for(auto it=chain.begin(); it!=chain.end(); it++) {
        if(it->second.sha == sha) {
            return it;
        }
    }
    return chain.end();
}

size_t Blockchain::count(size_t &size) const {
    size = 0;
    for(auto &e : chain) {
        size += e.second.size();
    }

    return chain.size();
}

std::string Blockchain::get_sha256(const std::vector<unsigned char>& in) const {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    int err;

    SHA256_CTX sha256;
    err = SHA256_Init(&sha256);
    if( err!= 1 ) {
        std::cout << strerror(errno) << std::endl;
        throw std::runtime_error(strerror(errno));
    }
    err = SHA256_Update(&sha256, &in[0], in.size());
    if( err != 1 ) {
        std::cout << strerror(errno) << std::endl;
        throw std::runtime_error(strerror(errno));
    }
    err = SHA256_Final(hash, &sha256);
    if( err != 1 ) {
        std::cout << strerror(errno) << std::endl;
        throw std::runtime_error(strerror(errno));
    }

    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for(int i=0; i<SHA256_DIGEST_LENGTH; i++) {
        ss << std::setw(2) << (unsigned int)hash[i];
    }

    return ss.str();
}

void Blockchain::store(void *extra_args) {
    for(auto& e : chain) {
        (*_store)(e, extra_args);
    }
}

void Blockchain::load(void *extra_args) {
    while(true) {
        try {
            node_data_t data;
            (*_load)(data, extra_args);

            auto hash = get_sha256(data.serialize());
            auto it = chain.emplace(std::move(hash), std::move(data));
        } catch (std::out_of_range) {
            std::cout << chain.size() <<" blocks has been loaded" << std::endl;
            break;
        }
    }
}

std::vector<const char*> Blockchain::verify() const {
    std::vector<const char*> v;
    for(auto& n : chain) {
        const char* sha {n.second.sha};
        try {
            chain.at(sha);
        } catch(const std::out_of_range& e) {
            v.push_back(sha);
        }
    }
    return v;
}

const node_data_t& Blockchain::get(const char* sha) const {
    return chain.at(sha);
}
