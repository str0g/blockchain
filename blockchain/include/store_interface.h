#ifndef _STOREINTERFACE_H_
#define _STOREINTERFACE_H_

#include "node_data.h"

/**
 * Prepare custom class to store object
 */
class StoreInterface {
    public:
        virtual void operator()(const chain_pair &, void* extra_args) = 0;
        virtual ~StoreInterface() {}
};

#endif
