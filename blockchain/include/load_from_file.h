#ifndef _LOAD_FROM_FILE_H_
#define _LOAD_FROM_FILE_H_

#include "load_interface.h"
#include "common_store_load.h"

class LoadFromFile: public LoadInterface, public CommonStoreLoad {
    public:
        void operator()(node_data_t&, void *extra_args);

        LoadFromFile();
#ifdef WITH_TESTS
        virtual ~LoadFromFile();
        void set_path(const std::string&);
    protected:
#else
    private:
#endif
        std::vector<std::string> files;
        std::vector<std::string>::iterator it;

        void set_files();
};

#endif
