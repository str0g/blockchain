#ifndef _STORE_TO_FILE_H_
#define _STORE_TO_FILE_H_

#include "store_interface.h"
#include "common_store_load.h"

class StoreToFile: public StoreInterface, CommonStoreLoad {
    public:
        void operator()(const chain_pair&, void *extra_args);
//@TODO WITH_DEBUG
        void swap_path(std::string& path);
//
};

#endif
