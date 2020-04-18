#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <sstream>

#include "node_data.h"

namespace testing {

TEST_F(Test, serlization_stream_test) {
    char sha[] {"b481ebad7343f698124bbe7896443381aff70ec4ba3077d87b3721d6fced985a"};
    const char *elements[] = {"line1", "line2", "line3"};

    node_data_t node_data;
    node_data.block_id = 1;
    memcpy(node_data.sha, sha, sizeof(sha));
    node_data.elements_nb = 3;
    node_data.elements.resize(node_data.elements_nb);
    for(int i=0; i<node_data.elements_nb; i++) {
        memcpy(&node_data.elements[i], elements[i], sizeof(node_data.elements_nb));
    }

    std::stringstream s;
    auto v = node_data.serialize();
    s.write((const char*)&v[0], v.size());

    node_data_t input_node_data;
    s >> input_node_data;
    std::stringstream s2;
    s2 << input_node_data;


    ASSERT_EQ(input_node_data.block_id, 1);
    ASSERT_EQ(input_node_data.elements_nb, 3);
    ASSERT_EQ(strlen(input_node_data.sha), sizeof(node_data_t::sha)-1);
    ASSERT_STREQ(input_node_data.sha, sha);
    for(int i=0; i<input_node_data.elements_nb; i++) {
        ASSERT_STREQ(input_node_data.elements[i], elements[i]);
    }
}

TEST_F(Test, serialize) {
    char sha[] {"b481ebad7343f698124bbe7896443381aff70ec4ba3077d87b3721d6fced985a"};
    const char *elements[] = {"line1", "line2", "line3"};

    node_data_t node_data;
    node_data.block_id = 1;
    memcpy(node_data.sha, sha, sizeof(sha));
    node_data.elements_nb = 3;
    node_data.elements.resize(node_data.elements_nb);
    for(int i=0; i<node_data.elements_nb; i++) {
        memcpy(&node_data.elements[i], elements[i], sizeof(node_data.elements_nb));
    }

    auto v = node_data.serialize();
    ASSERT_EQ(465, v.size());
}

}
