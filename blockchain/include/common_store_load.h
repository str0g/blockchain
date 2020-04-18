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

#ifndef _COMMON_STORE_LOAD_H_
#define _COMMON_STORE_LOAD_H_

#include <string>

class CommonStoreLoad {
    public:
        CommonStoreLoad();
        virtual ~CommonStoreLoad();
    protected:
        static std::string path;
    private:
        CommonStoreLoad(const CommonStoreLoad&) = delete;
        CommonStoreLoad(CommonStoreLoad&&) = delete;
        CommonStoreLoad& operator=(const CommonStoreLoad&) = delete;
        CommonStoreLoad& operator=(CommonStoreLoad&&) = delete;
};

#endif
