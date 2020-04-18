#ifndef _DELETE_FILE_H_
#define _DELETE_FILE_H_

#include "delete_interface.h"
#include "common_store_load.h"

class DeleteFile: public DeleteInterface, public CommonStoreLoad {
    public:
        void operator()(const std::string&, const node_data_t&);
};

#endif
