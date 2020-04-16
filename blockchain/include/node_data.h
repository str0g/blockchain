#ifndef _NODE_DATA_H_
#define _NODE_DATA_H_

#include <vector>
#include <ostream>
#include <istream>
#include <cstring>
#include <iostream>

struct node_data_t {
    struct element_t {
        char element[256];

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

        private:
            element_t& operator=(element_t const&) = delete;
    };

    using Elements = std::vector<element_t>;

    struct header_t {
        unsigned index;
        size_t elements_nb;
        char sha[65];
    
        header_t() : index(0), elements_nb(0) {
            memset(&sha, '\0', sizeof(sha));
        }

        private:
            header_t(const header_t&) = delete;
            header_t(header_t&&) = delete;
            header_t& operator=(const header_t&) = delete;
            header_t& operator=(header_t&&) = delete;
    };
    header_t header;
    Elements elements;


    friend std::istream& operator>>(std::istream&, node_data_t&);
    friend std::ostream& operator<<(std::ostream&, node_data_t&);

    node_data_t() = default;

    private:
        node_data_t(const node_data_t&) = delete;
        node_data_t(node_data_t&&) = delete;
        node_data_t& operator=(const node_data_t&) = delete;
        node_data_t& operator=(node_data_t&&) = delete;
};


#endif
