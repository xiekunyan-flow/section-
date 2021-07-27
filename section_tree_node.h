#ifndef SECTION_TREE_NODE_H_INCLUDE
#define SECTION_TREE_NODE_H_INCLUDE
#include "section_node.h"
namespace J{
    namespace tree_node{
        template<typename _Key, typename _Tp>
            class _Section_tree_node : public _Section_tree_node_base {
            public:
            //     typedef bool _Child_exist;
            //     typedef std::pair<const _Key, _Tp>		value_type;
            //     typedef _Tp mapped_type;
            //     //typedef bool _Is_leaf; 

            //     //家福在这想想初始化_Is_leaf为什么比较好
            //     _Section_leaf_node() noexcept :  _Is_leaf(false), _M_Field(value_type()), {}

            //     //_Child_exist _Left_child;  //removed in F.0.2 
            //     //_Child_exist _Right_child; //removed in F.0.2
            // private:
            //     bool _Is_leaf; //mark if its child is leaf
            //     value_type _M_field;
            //     mapped_type _M_marked;

                typedef _Section_tree_node<_Key, _Tp>* _Tree_link_type;
            
            public:
                _Key _right_key;
                bool _has_mid;
                bool _Is_leaf;
                _Tp _sum; //当前版本只能求和
            public:
                _Section_tree_node<_Key, _Tp>() noexcept : _right_key(_Key()), _has_mid(false), _Is_leaf(false), _sum(_Tp()) {}

                _Section_tree_node<_Key, _Tp>(_Key __right_key, _Tp __sum) noexcept :  _right_key(__right_key), _has_mid(false), _Is_leaf(false), _sum(__sum) {}

                void maintance() {
                    auto r(static_cast<_Section_tree_node<_Key, _Tp>*>(_right));
                    _sum = r->_sum;
                    _right_key = r->_right_key;

                    if (_left != nullptr) {
                        auto l(static_cast<_Section_tree_node<_Key, _Tp>*>(_left));
                        _sum += l->_sum;
                    }
                }

                const _Key& right_key() {
                    return _right_key;
                }
                virtual void swap(const _Tree_link_type& __L) {
                    //TODO 补充这里
                    auto p(__L->_left);
                    __L->_left = _left;
                    _left = p;
                }

                virtual _Tree_link_type insert_topasa(_Tree_link_type p) {
                    const _Tree_link_type& a(this);
                    _Tree_link_type p2(static_cast<_Tree_link_type>(p->_right));
                    auto __key(a->right_key());
                    if (!p->_has_mid) { //p只有一个孩子
                        if (__key == p2->right_key())
                            return nullptr;
                        else if (__key > p2->right_key()) {
                            a->swap(p2);
                        }
                        a->_parent = p;
                        p->_left = a;
                        //TODO 干脆这里直接返回自己的父节点，然后在insert中判断
                        for(auto pc(p); pc != &_M_header; pc = static_cast<_Tree_link_type>(pc->_parent))
                            pc->maintance();
                        _M_header._node_count++;
                        _M_header._size++;
                        return nullptr;
                    }

                    return nullptr;
                }
            };

    }
}
#endif