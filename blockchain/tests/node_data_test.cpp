#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <sstream>

#include "node_data.h"

namespace testing {

TEST_F(Test, serlization) {
    char sha[] {"b481ebad7343f698124bbe7896443381aff70ec4ba3077d87b3721d6fced985a"};
    const char *elements[] = {"line1", "line2", "line3"};

    node_data_t node_data; 
    node_data.header.index = 1;
    memcpy(node_data.header.sha, sha, sizeof(sha));
    node_data.header.elements_nb = 3;
    node_data.elements.resize(node_data.header.elements_nb);
    for(int i=0; i<node_data.header.elements_nb; i++) {
        memcpy(&node_data.elements[i], elements[i], sizeof(node_data.header.elements_nb));
    }

    std::stringstream s;
    s << node_data;

    node_data_t input_node_data;
    s >> input_node_data;
    std::stringstream s2;
    s2 << input_node_data;


    ASSERT_EQ(input_node_data.header.index, 1);
    ASSERT_EQ(input_node_data.header.elements_nb, 3);
    ASSERT_EQ(strlen(input_node_data.header.sha), sizeof(node_data_t::header_t::sha)-1);
    ASSERT_STREQ(input_node_data.header.sha, sha);
    for(int i=0; i<input_node_data.header.elements_nb; i++) {
        ASSERT_STREQ(input_node_data.elements[i], elements[i]);
    }
//    ASSERT_EQ(s.str(), s2.str());
}

}
