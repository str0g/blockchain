#################################################################################
#    Blockchain is a sample program to to introduce into blockchain technology  #
#    Copyright (C) 2020  Łukasz Buśko                                           #
#                                                                               #
#    This program is free software: you can redistribute it and/or modify       #
#    it under the terms of the GNU General Public License as published by       #
#    the Free Software Foundation, either version 3 of the License, or          #
#    (at your option) any later version.                                        #
#                                                                               #
#    This program is distributed in the hope that it will be useful,            #
#    but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#    GNU General Public License for more details.                               #
#                                                                               #
#    You should have received a copy of the GNU General Public License          #
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.      #
#################################################################################

cmake_minimum_required(VERSION 3.17)
project(blockchain_test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(PKG_CONFIG_REQUIRED_VERSION 1.6.1)

option(WITH_TESTS "Build unit tests" FALSE)
if(WITH_TESTS)
    add_definitions(-DWITH_TESTS)
    set(GTEST_DEP_LIBS -lgtest gtest_main)
    enable_testing()
endif()


#dependenices
find_package(PkgConfig ${PKG_CONFIG_REQUIRED_VERSION} REQUIRED)
if(WITH_TESTS)
    pkg_check_modules(GTEST REQUIRED gtest>=1.8.1)
endif()
pkg_search_module(OPENSSL REQUIRED openssl)

#force out source build
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Build)

#includes
include_directories(common/include)
include_directories(blockchain/include)

#libs
add_subdirectory(${PROJECT_SOURCE_DIR}/blockchain ${CMAKE_CURRENT_BINARY_DIR}/blockchain)
if(WITH_TESTS)
    add_subdirectory(${PROJECT_SOURCE_DIR}/common ${CMAKE_CURRENT_BINARY_DIR}/common)
endif()

#project options
add_executable(blockchain_test src/main.cpp)
target_link_libraries(blockchain_test PUBLIC blockchain)
