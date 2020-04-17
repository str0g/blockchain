#include "common_store_load.h"

#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <cstring>
CommonStoreLoad::CommonStoreLoad() {
    if(path.empty()) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            throw std::runtime_error("could not get current directory");
        }

        path = std::string(cwd) + "/chain_data/";
    }
}

std::string CommonStoreLoad::path;
