if(WITH_TESTS)
    set(test_name "narrow_cast_test")
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} ${GTEST_DEP_LIBS})
    add_test(${test_name} ${test_name})

    set(test_name "finally_test")
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} ${GTEST_DEP_LIBS})
    add_test(${test_name} ${test_name})

endif()
