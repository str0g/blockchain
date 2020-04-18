#ifndef _NODE_DATA_H_
#define _NODE_DATA_H_

#include <vector>
#include <ostream>
#include <istream>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <openssl/sha.h>

struct node_data_t {
    struct element_t {
        char element[128];

        element_t() {
            memset(&element, '\0', sizeof(element));
        }
        operator const char*() {
            return &element[0];
        }
        operator char*() {
            return &element[0];
        }
        char& operator->() {
            return element[0];
        }

        friend std::ostream& operator<<(std::ostream&, element_t&);

        private:
            element_t& operator=(element_t const&) = delete;
    };

    using Elements = std::vector<element_t>;

    size_t block_id;
    size_t elements_nb;
    char sha[65];
    Elements elements;

    node_data_t();

    size_t size() const;

    friend std::istream& operator>>(std::istream&, node_data_t&);
    friend std::ostream& operator<<(std::ostream&, node_data_t&);

    std::vector<unsigned char> serialize() const;
    private:
        node_data_t& operator=(const node_data_t&) = delete;
};

using chain_it = std::unordered_map<std::__cxx11::basic_string<char>, node_data_t>::iterator;
using chain_pair = std::pair<const std::__cxx11::basic_string<char>, node_data_t>;

#endif
