#ifndef SECTION_NODE_H_INCLUDE
#define SECTION_NODE_H_INCLUDE
#include <iostream>

namespace J{
    namespace basic{
        // There are 6 kinds of nodes used in Section:
        // 1. _Section_node_base
        // 2. _Section_leaf_node_base : _Section_node_base
        // 3. _Section_tree_node_base : _Section_node_base
        // 4. _Section_node_header : _Section_leaf_node_base
        // 5. _Section_nonleaf_node : _Section_tree_node_base
        // 6. _Section_leaf_node : _Section_leaf_node_base, 
        //                         _Section_tree_node_base
        // Base nodes(1, 2, 3) are not templated while others(5, 6)
        // are templated, except _Section_node_header(4)
        class _Section_node_base {
        public:
            _Section_node_base* _parent;
            _Section_node_base() noexcept : _parent(nullptr)  {}
            std::string print();
        };
        
        class _Section_leaf_node_base : public _Section_node_base {
        public:
            _Section_leaf_node_base* _next;
            _Section_leaf_node_base* _prev;
            _Section_leaf_node_base() noexcept : _next(nullptr), _prev(nullptr) {}
        };

        class _Section_tree_node_base : public _Section_node_base {
        public:
            _Section_tree_node_base* _left;
            _Section_tree_node_base* _right;
            _Section_tree_node_base() noexcept : _left(nullptr), _right(nullptr) {}
        };

    }
}

#include "section_node.cc"

#endif
