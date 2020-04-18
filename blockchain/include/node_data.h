/********************************************************************************
*    Blockchain is a sample program to to introduce into blockchain technology  *
*    Copyright (C) 2020  Łukasz Buśko                                           *
*                                                                               *
*    This program is free software: you can redistribute it and/or modify       *
*    it under the terms of the GNU General Public License as published by       *
*    the Free Software Foundation, either version 3 of the License, or          *
*    (at your option) any later version.                                        *
*                                                                               *
*    This program is distributed in the hope that it will be useful,            *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*    GNU General Public License for more details.                               *
*                                                                               *
*    You should have received a copy of the GNU General Public License          *
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.      *
*********************************************************************************/

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
