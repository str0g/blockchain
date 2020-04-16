#ifndef _BLOCKCHAIN_H_
#define _BLOCKCHAIN_H_

#include <unordered_map>

#include "StoreInterface.h"
#include "LoadInterface.h"

class StoreToFile: public StoreInterface {
    void operator()(const node_data_t&, void *extra_args);
};

class LoadFromFile: public LoadInterface {
    void operator()(node_data_t&, void *extra_args); 
};

class Blockchain {
    public:
        static Blockchain& getInstance();

        void verify() const;
        size_t count() const;
        void store(void*);
        void load(void*);
        const node_data_t& add(node_data_t&);
        void remove(size_t);
        void remove(const char*);
        
        void set_custom_load(LoadInterface*);
        void set_custom_store(StoreInterface*);

        ~Blockchain();

    private:
        using chain_it = std::__detail::_Node_iterator<std::pair<const long unsigned int, node_data_t>, false, false>;
        Blockchain();
        chain_it find(const char* sha);

        Blockchain(Blockchain const&) = delete;
        Blockchain(Blockchain &&) = delete;

        Blockchain& operator=(Blockchain const&) = delete;
        Blockchain& operator=(Blockchain &&) = delete;
        /*
         * due to fact this is a demo will use best container for my pleasure
         * In real life project mmap as fast access bufer would be preferable choice.
         */
        std::unordered_map<size_t, node_data_t> chain;
        LoadInterface* _load;
        StoreInterface* _store;
};

#endif
