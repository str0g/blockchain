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

#include <iostream>
#include <string>
#include <functional>
#include "getopt.h"

#include "blockchain.h"
#include "node_data.h"

void msg(int nb, const char* desc);
bool next_action(void(*fun)(const char *opt, void *ptr),void *ptr, int argc, char** argv);
void help();

int main(int argc, char **argv) {
    auto& blockchain = Blockchain::getInstance();
    blockchain.load();

    int c;
    int digit_optind = 0;
    while(1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options [] = {
            {"add", required_argument, 0, 'a'},
            {"remove", required_argument, 0, 'r'},
            {"count", no_argument, 0, 'c'},
            {"verify", no_argument, 0, 'v'},
            {"info", required_argument, 0, 'i'},
        };

        c = getopt_long(argc, argv, "a", long_options, &option_index);
        if (c ==-1)
            break;

        switch(c) {
            case 0:
                std::cout << "option" << long_options[option_index].name;
                if(optarg)
                        std::cout << " with arg " << optarg;
                std::cout << std::endl;
                break;
            case 'a':
                {
                auto get_sha = [](const char *opt, void *ptr) {
                    size_t size { strnlen(opt, sizeof(node_data_t::sha)) };
                    if (size != sizeof(node_data_t::sha)-1) {
                        std::cout << "length:" << size << " " << opt << std::endl;
                        throw std::invalid_argument("is not sha256");
                    }

                    node_data_t& node_data = *static_cast<node_data_t*>(ptr);
                    strncpy(node_data.sha, opt, size);
                };
                auto get_line = [](const char *opt, void *ptr) {
                    node_data_t& node_data = *static_cast<node_data_t*>(ptr);
                    size_t size = strnlen(opt, sizeof(node_data_t::element_t::element));
                    strncpy(node_data.elements[node_data.elements_nb], opt, size);
                    node_data.elements_nb++;
                };

                node_data_t node_data;
                int max = 10;
                node_data.elements.resize(max--);
                try {
                    node_data.block_id = std::stoull(optarg);

                    if(!next_action(get_sha, &node_data, argc, argv)) {
                        msg(3, "add");
                        exit(1);
                    }
                    if(!next_action(get_line, &node_data, argc, argv)) {
                        msg(3, "add");
                        exit(1);
                    }
                    while(next_action(get_line, &node_data, argc, argv) and --max);

                    auto size = node_data.elements.size();
                    size = max > size ? max-size : size-max;
                    node_data.elements.resize(size+1);

                    node_data.elements.shrink_to_fit();
                    node_data.elements_nb = node_data.elements.size();

                    auto& data = blockchain.add(node_data);
                    
                    std::cout<<"Summary: " << std::endl;
                    std::cout<<"block_id " << data.block_id<<std::endl;
                    std::cout<<"sha " << data.sha<<std::endl;
                    std::cout<<"elements["<< data.elements_nb<<"]:"<<std::endl;
                    for(auto&e : data.elements) {
                        if(e.element[0] == '\0')
                            break;
                        std::cout<<"\t"<<e.element<<std::endl;
                    }
                } catch(const std::invalid_argument& e) {
                    std::cout << e.what() << " [" << optarg << "]" << std::endl;
                    exit(1);
                } catch(const std::out_of_range& e) {
                    std::cout << e.what() << " [" << optarg << "]" << std::endl;
                    exit(1);
                }
                std::cout << std::endl;
                }
                break;
            case 'r':
                blockchain.remove(optarg);
                break;
            case 'c':
                {
                size_t size;
                std::cout << "elements: " << blockchain.count(size) << " size: " << size << std::endl;
                }
                break;
            case 'v':
                {
                auto v = blockchain.verify();
                if (!v.empty())
                    std::cout << "found problems with:" << std::endl;
                for (auto& sha : v)
                    std::cout << sha << std::endl;
                }
                break;
            case 'i':
                try {
                    auto data = blockchain.get(optarg);
                    std::cout << data << std::endl;
                } catch (const std::exception& e) {
                    std::cout << optarg << " not found" << std::endl;
                }
                break;
            default:
                std::cout << "getopt returned character code 0x" << std::hex << c << std::endl;
                break;
        }
    }

    if (optind < argc) {
        std::cout << "non-option ARGV-elements: ";
        while(optind < argc)
            std::cout << argv[optind++] << " ";
        std::cout << std::endl;

        help();
    }

    return 0;
}
void msg(int nb, const char* desc) {
    std::cout << "option " << desc << " requires " << nb << " arguments" << std::endl;
}

bool next_action(void(*fun)(const char *opt, void *ptr),void *ptr, int argc, char** argv) {
    if (optind < argc && *argv[optind] != '-') {
        fun(argv[optind], ptr);
        optind++;
        return true;
    } else {
        return false;
    }
}

void help() {
    std::cout <<
    "Options:\n"
            "\t--add <id> <parent sha> <line1> <linen>: Add block\n"
            "\t--remove: <arg>      Remove block by block sha\n"
            "\t--count:             Set sigma of program\n"
            "\t--verify             Print problematic nodes\n"
            "\t--info               Get node info\n"
            "\t--help:              Show help\n";
    exit(1);
}
