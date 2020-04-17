#ifndef _LOADFROMINTERFACE_H_
#define _LOADFROMINTERFACE_H_

#include "node_data.h"

/*
 * Prepare custom class to load data
 */
class LoadInterface {
    public:
        virtual void operator()(node_data_t &in_and_out, void* extra_args) = 0;
};

#endif
