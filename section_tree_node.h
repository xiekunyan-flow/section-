#ifndef SECTION_TREE_NODE_H_INCLUDE
#define SECTION_TREE_NODE_H_INCLUDE
#include "section_node.h"
namespace J{
    namespace tree_node{
        template<typename _Key,_typename _Tp>
            class _Section_tree_node : public _Section_tree_node_base {
            public:
                typedef bool _Child_exist;
                typedef std::pair<const _Key, _Tp>		value_type;
                typedef _Tp mapped_type;
                //typedef bool _Is_leaf; 
                _Section_leaf_node() noexcept : _next(nullptr), _prev(nullptr) {}

                //_Child_exist _Left_child;  //removed in F.0.2 
                //_Child_exist _Right_child; //removed in F.0.2
            private:
                bool _Is_leaf; //mark if its child is leaf
                value_type _M_field;
                mapped_type _M_marked;
                //操作标记
                void _M_change_mark(mapped_type __val){
                    _M_marked += val;
                }
                void _M_clear_mark(){
                    _M_marked  = 0;
                }
            };

    }
}
#endif