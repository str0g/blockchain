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

#ifndef _STORE_TO_FILE_H_
#define _STORE_TO_FILE_H_

#include "store_interface.h"
#include "common_store_load.h"

class StoreToFile: public StoreInterface, public CommonStoreLoad {
    public:
        void operator()(const chain_pair&, void *extra_args);
#ifdef WITH_TESTS
        void set_path(const std::string& path);
        virtual ~StoreToFile();
#endif
};

#endif
