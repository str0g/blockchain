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

#ifndef _LOAD_FROM_FILE_H_
#define _LOAD_FROM_FILE_H_

#include "load_interface.h"
#include "common_store_load.h"

class LoadFromFile: public LoadInterface, public CommonStoreLoad {
    public:
        void operator()(node_data_t&, void *extra_args);

        LoadFromFile();
#ifdef WITH_TESTS
        virtual ~LoadFromFile();
        void set_path(const std::string&);
    protected:
#else
    private:
#endif
        std::vector<std::string> files;
        std::vector<std::string>::iterator it;

        void set_files();
};

#endif
