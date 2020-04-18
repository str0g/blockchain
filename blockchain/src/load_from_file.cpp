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

#include "load_from_file.h"
#include "node_data.h"
#include "finally.h"

#include <fstream>
#include <dirent.h>
#include <string.h>

void LoadFromFile::operator()(node_data_t& out, void *extra_args) {
    if(it == files.end()) {
        throw std::out_of_range("No more files");
    }
    std::ifstream f(path+*it, std::fstream::binary);
    if (!f.is_open()) {
        std::cerr <<path << *it << std::endl;
        throw std::runtime_error("file not found");
    }
    f  >> out;
    f.close();

    *it++;
}

void LoadFromFile::set_files() {
    DIR *d = opendir(path.c_str());
    if(!d) {
        std::cout << "Could not open " << path << " " << strerror(errno) << std::endl;
        throw std::runtime_error("could not open path");
    }
    auto clean_dir = finally([&] {
        closedir(d);
    });

    dirent *dir;
    while((dir=readdir(d)) != nullptr) {
        if(dir->d_type != DT_REG)
            continue;

        std::string _file {dir->d_name};
        if(_file.length() > sizeof(node_data_t::sha))
            files.emplace_back(std::move(_file));
    }
    it = files.begin();
}

LoadFromFile::LoadFromFile() {
    set_files();
}

#ifdef WITH_TESTS
LoadFromFile::~LoadFromFile() {}
void LoadFromFile::set_path(const std::string& _path) {
    path = _path;
}
#endif
