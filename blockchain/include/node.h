#ifndef _NODE_H_
#define _NODE_H_

#include "node_data.h"

/**
 * Prepare custom class to store object
 */
class StoreToInterface {
    public:
        virtual void operator()(const node_data_t &in) = 0;
};

/*
 * Prepare custom class to load data
 */
class LoadFromInterface {
    public:
        virtual void operator()(node_data_t &in_and_out) = 0;
};


class Node {
    public:
        node_data_t data;

        void store(StoreToInterface &);
        void load(LoadFromInterface &);

    private:
        Node(const Node &) = delete;
        Node(Node &&) = delete;
        Node& operator=(const Node &) = delete;
        Node& operator=(Node &&) = delete;
};

#endif
