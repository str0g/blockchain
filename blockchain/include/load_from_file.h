#ifndef _LOAD_FROM_FILE_H_
#define _LOAD_FROM_FILE_H_

#include "load_interface.h"
#include "common_store_load.h"
#include "node_data.h"

class LoadFromFile: public LoadInterface, public CommonStoreLoad {
    public:
        void operator()(node_data_t&, void *extra_args); 
};

#endif
