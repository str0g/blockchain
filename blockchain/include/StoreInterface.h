#ifndef _STOREINTERFACE_H_
#define _STOREINTERFACE_H_

#include "node_data.h"

/**
 * Prepare custom class to store object
 */
class StoreInterface {
    public:
        virtual void operator()(const node_data_t &in, void* extra_args) = 0;
};

#endif
