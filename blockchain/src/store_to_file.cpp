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

#include "store_to_file.h"
#include <fstream>

void StoreToFile::operator()(const chain_pair& it, void *extra_args) {
        const node_data_t& data = it.second;
        std::string file = path + std::to_string(data.block_id) + "_" + it.first;

        auto v = data.serialize();

        //TODO error checks...
        std::ofstream f(file, std::ios::binary);
        f.write((const char*)&v[0], v.size());
        f.close();
}

#ifdef WITH_TESTS
void StoreToFile::set_path(const std::string& _path) {
    path = _path;
}

StoreToFile::~StoreToFile() {}
#endif
