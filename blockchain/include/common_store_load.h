#ifndef _COMMON_STORE_LOAD_H_
#define _COMMON_STORE_LOAD_H_

#include <string>

class CommonStoreLoad {
    public:
        CommonStoreLoad();
    protected:
        static std::string path;
    private:
        CommonStoreLoad(const CommonStoreLoad&) = delete;
        CommonStoreLoad(CommonStoreLoad&&) = delete;
        CommonStoreLoad& operator=(const CommonStoreLoad&) = delete;
        CommonStoreLoad& operator=(CommonStoreLoad&&) = delete;
};

#endif
