#ifndef SECTION_TREE_NODE_H_INCLUDE
#define SECTION_TREE_NODE_H_INCLUDE
#include "section.h"
namespace J{
    namespace tree_node{
        template<typename _Key,_typename _Tp>
            class _Section_tree_node : public _Section_tree_node_base {
            public:
                typedef bool _Child_exist;
                //typedef bool _Is_leaf; 
                _Section_leaf_node() noexcept : _next(nullptr), _prev(nullptr) {}

                _Child_exist _Left_child;
                _Child_exist _Right_child;
                bool _Is_leaf; //mark if its child is leaf
                
            };

    }
}
#endif