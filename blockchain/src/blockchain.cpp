#include "blockchain.h"

#include <iostream>

Blockchain& Blockchain::getInstance() {
    static Blockchain out;
    return out;
}

Blockchain::Blockchain() {
    std::cout << "Blockchain created" << std::endl;
}
