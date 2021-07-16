#ifndef SECTION_TLEAF_NODE_H_INCLUDE
#define SECTION_LEAF_NODE_H_INCLUDE
#include "section_node.h"

namespace J{
    namespace leaf_node{

        // _Section_leaf_node inherit from _Section_leaf_node_base 
        // and _Section_tree_node_base
        // _Section_leaf_node_base dont have templated data, while 
        // _Section_leaf_node has
        // The templated data stored in std::pair
        template<typename _Key, typename _Tp>
        class _Section_leaf_node : public _Section_leaf_node_base, public _Section_tree_node_base {
        public:
            std::pair<_Key, _Tp> _pair;
            typedef _Section_leaf_node<_Key, _Tp>* _Link_type;
            typedef std::pair<_Key, _Tp> _Val;
            _Section_leaf_node() noexcept : _pair(std::pair<_Key, _Tp>()) { }
            _Section_leaf_node(_Key __key, _Tp __value) :  _Section_leaf_node_base(), _Section_tree_node_base(), _pair(_Val(__key, __value)){}
            _Val* _valptr() { return &_pair; }

            const _Val* _valptr() const { return static_cast<const _Val*>(&_pair); }
        };
    }
}

#endif