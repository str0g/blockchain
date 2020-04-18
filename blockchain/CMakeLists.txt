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

project(blockchain)

aux_source_directory(src SRC)
add_library(${PROJECT_NAME} SHARED ${SRC} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})

if(WITH_TESTS)
    set(test_name "singleton_test")
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} ${PROJECT_NAME} ${GTEST_DEP_LIBS})
    add_test(${test_name} ${test_name})

    set(test_name "openssl_sha256_test")
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} ${PROJECT_NAME} ${GTEST_DEP_LIBS})
    add_test(${test_name} ${test_name})

    set(test_name "node_data_test")
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} ${PROJECT_NAME} ${GTEST_DEP_LIBS})
    add_test(${test_name} ${test_name})

    set(test_name "blockchain_add_test")
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} ${PROJECT_NAME} ${GTEST_DEP_LIBS})
    add_test(${test_name} ${test_name})

    set(test_name "blockchain_remove_test")
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} ${PROJECT_NAME} ${GTEST_DEP_LIBS})
    add_test(${test_name} ${test_name})

    set(test_name "store_file_test")
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} ${PROJECT_NAME} ${GTEST_DEP_LIBS})
    add_test(${test_name} ${test_name})

endif()
