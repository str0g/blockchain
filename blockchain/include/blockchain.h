#ifndef _BLOCKCHAIN_H_
#define _BLOCKCHAIN_H_

#include <unordered_map>

#include "load_interface.h"
#include "store_interface.h"

class Blockchain {
    public:
        static Blockchain& getInstance();

        void verify() const;
        size_t count() const;
        void store(void* =nullptr);
        void load(void* = nullptr);
        const node_data_t& add(node_data_t&);
        void remove(const std::string&);
        std::string get_sha256(const std::string&) const;
        std::string get_sha256(const std::vector<unsigned char>&) const;
        
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
};

#endif
