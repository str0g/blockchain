#include "node_data.h"

std::istream& operator>>(std::istream& os, node_data_t& obj) {
    os.read((char*)&obj.header, sizeof(obj.header));
    obj.elements.resize(obj.header.elements_nb);
    for (int i=0; i<obj.header.elements_nb; i++)
        os.read((char*)&obj.elements[i], sizeof(node_data_t::element_t::element));

    return os;
}

std::ostream& operator<<(std::ostream& os, node_data_t& obj) {
    os.write((char*)&obj.header, sizeof(obj.header));
    for (auto& e: obj.elements)
        os.write((const char*)&e, sizeof(node_data_t::element_t::element)); //node_data_t::Element_t::element

    return os;
}
