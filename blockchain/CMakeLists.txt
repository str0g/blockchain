project(blockchain)

aux_source_directory(src SRC)
add_library(${PROJECT_NAME} SHARED ${SRC} ${CMAKE_CURRENT_BINARY_DIR})

if(WITH_TESTS)
    set(test_name "singleton_test")
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} ${PROJECT_NAME} ${GTEST_DEP_LIBS})
    add_test(${test_name} ${test_name})

    set(test_name "node_data_test")
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} ${PROJECT_NAME} ${GTEST_DEP_LIBS})
    add_test(${test_name} ${test_name})

endif()
