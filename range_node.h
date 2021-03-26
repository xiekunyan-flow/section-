#ifndef RANGE_NODE_H_INCLUDE
#define RANGE_NODE_H_INCLUDE
#include <iostream>

namespace J{
    // node
    class _Section_node_base {
    public:
        _Section_node_base* _parent;
        _Section_node_base() noexcept : _parent(nullptr)  {}
        void print();
    };
}

#include "range_node.cc"

#endif