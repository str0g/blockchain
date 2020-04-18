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

#ifndef _BLOCKCHAIN_H_
#define _BLOCKCHAIN_H_

#include <unordered_map>

#include "load_interface.h"
#include "store_interface.h"
#include "delete_interface.h"

class Blockchain {
    public:
        static Blockchain& getInstance();

        std::vector<const char*> verify() const;
        size_t count(size_t&) const;
        void store(void* =nullptr);
        void load(void* = nullptr);
        const node_data_t& add(node_data_t&);
        void remove(const std::string&);
        std::string get_sha256(const std::vector<unsigned char>&) const;

        const node_data_t& get(const char*) const;
        
        void set_custom_load(LoadInterface*);
        void set_custom_store(StoreInterface*);

        ~Blockchain();

    private:
        Blockchain();
        chain_it find_child(const std::string&);

        Blockchain(Blockchain const&) = delete;
        Blockchain(Blockchain &&) = delete;

        Blockchain& operator=(Blockchain const&) = delete;
        Blockchain& operator=(Blockchain &&) = delete;
        /*
         * Due to fact this is a demo will use best container for my pleasure.
         * Real life project would experiment with mmap as fast access.
         */
        std::unordered_map<std::string, node_data_t> chain;
        LoadInterface* _load;
        StoreInterface* _store;
        DeleteInterface* _delete;
};

#endif
