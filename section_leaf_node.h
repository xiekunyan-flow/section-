#ifndef SECTION_TLEAF_NODE_H_INCLUDE
#define SECTION_LEAF_NODE_H_INCLUDE
#include "section_node.h"

namespace J{
    namespace leaf_node{
        class _Section_leaf_node : public _Section_leaf_node_base {
        public:
            _Section_tree_node_base* _left;
            _Section_tree_node_base* _right;
            _Section_tree_node_base() noexcept : _left(nullptr), _right(nullptr) {}
        };
    }
}

#endif