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

#include "common_store_load.h"

#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <cstring>
CommonStoreLoad::CommonStoreLoad() {
    if(path.empty()) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) == nullptr) {
            throw std::runtime_error("could not get current directory");
        }

        path = std::string(cwd) + "/chain_data/";
    }
}

CommonStoreLoad::~CommonStoreLoad() {
}

std::string CommonStoreLoad::path;
