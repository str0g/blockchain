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
