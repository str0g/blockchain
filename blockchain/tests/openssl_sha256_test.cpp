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

#include <gtest/gtest.h>
#include <cstring>

#include "blockchain.h"

namespace testing {

struct exp_t {
    std::string data;
    const char* sha;
};


TEST_F(Test, sha256) {
    exp_t exp {"test", "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08"};
    auto& blockchain = Blockchain::getInstance();

    std::vector<unsigned char> v (exp.data.begin(), exp.data.end());

    auto sig = blockchain.get_sha256(v);

    ASSERT_STREQ(sig.c_str(), exp.sha);
}

};
