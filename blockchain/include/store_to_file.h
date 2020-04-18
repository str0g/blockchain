#ifndef _STORE_TO_FILE_H_
#define _STORE_TO_FILE_H_

#include "store_interface.h"
#include "common_store_load.h"

class StoreToFile: public StoreInterface, public CommonStoreLoad {
    public:
        void operator()(const chain_pair&, void *extra_args);
#ifdef WITH_TESTS
        void set_path(const std::string& path);
        virtual ~StoreToFile();
#endif
};

#endif
