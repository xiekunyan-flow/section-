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
            _Section_node_base(_Section_node_base* __parent) noexcept : _parent(__parent) {}

            //
            // @brief Only used for test.
            // 
            std::string print();
        };
        
        class _Section_leaf_node_base : public _Section_node_base {
        public:
            _Section_leaf_node_base* _next; // next node
            _Section_leaf_node_base* _prev; // prev node
            _Section_leaf_node_base() noexcept : _next(nullptr), _prev(nullptr) {}
            _Section_leaf_node_base(_Section_node_base* __parent, _Section_leaf_node_base* __next, _Section_leaf_node_base* __prev) noexcept : _Section_node_base{__parent}, _next(__next), _prev(__prev) {}
        };

        class _Section_tree_node_base : public _Section_node_base {
        public:
            _Section_tree_node_base* _left;  // left child
            _Section_tree_node_base* _right; // right child
            _Section_tree_node_base() noexcept : _left(nullptr), _right(nullptr) {}
            _Section_tree_node_base(_Section_node_base* __parent, _Section_tree_node_base* __left, _Section_tree_node_base* __right) : _Section_node_base{__parent}, _left(__left), _right(__right) {}
        };

        class _Section_node_header : public _Section_leaf_node_base {
        public:
            std::size_t _node_count; // Keeps track of number of nodes in tree.
            std::size_t _size; // Number of leaf nodes.
        };
    }
}

#include "section_node.cc"

#endif
