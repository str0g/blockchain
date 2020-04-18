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

#include "node_data.h"

std::istream& operator>>(std::istream& os, node_data_t& obj) {
    os.read((char*)&obj.block_id, sizeof(obj.block_id));
    os.read((char*)&obj.elements_nb, sizeof(obj.elements_nb));
    os.read((char*)&obj.sha, sizeof(obj.sha));
    if (obj.elements_nb > 0)
        obj.elements.resize(obj.elements_nb);
        obj.elements.shrink_to_fit();
        os.read((char*)&obj.elements[0], obj.elements_nb * sizeof(node_data_t::element_t));

    return os;
}

std::ostream& operator<<(std::ostream& os, node_data_t::element_t& obj) {
    return os << obj.element;
}

std::ostream& operator<<(std::ostream& os, node_data_t& obj) {
    os << "Parent: " << obj.sha << std::endl;
    os << "Block_id: " << obj.block_id << std::endl;
    os << "Elements[" << obj.elements_nb << "]:" << std::endl;
    for(auto &e : obj.elements)
        os << "\t" << e << std::endl;
    return os;
}

node_data_t::node_data_t () : block_id(0), elements_nb(0) {
    memset(&sha, '\0', sizeof(sha));
}

std::vector<unsigned char> node_data_t::serialize() const {
    std::vector<unsigned char> v;
    v.resize(size());
    memset(&v[0], '\0', v.size());

    size_t i = 0;
    memcpy(&v[i], &block_id, sizeof(block_id));
    i += sizeof(block_id);
    memcpy(&v[i], &elements_nb, sizeof(elements_nb));
    i += sizeof(elements_nb);
    memcpy(&v[i], &sha[0], sizeof(sha));
    i += sizeof(sha);
    if (elements_nb > 0)
        memcpy(&v[i], &elements[0], elements_nb * sizeof(element_t));

    return v;
}

size_t node_data_t::size() const {
    return sizeof(block_id) + sizeof(sha) + sizeof(block_id) + elements_nb*sizeof(element_t);
}
