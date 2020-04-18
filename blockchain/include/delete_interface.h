#ifndef _DELETE_INTERFACE_
#define _DELETE_INTERFACE_

#include "node_data.h"

class DeleteInterface {
    public:
        virtual void operator()(const std::string&, const node_data_t&) = 0;
        virtual ~DeleteInterface(){}
};

#endif
