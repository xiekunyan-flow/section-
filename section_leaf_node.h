#ifndef SECTION_TLEAF_NODE_H_INCLUDE
#define SECTION_LEAF_NODE_H_INCLUDE
#include "section_node.h"
#include "section_tree_node.h"

namespace J{
    using namespace J::tree_node;
    namespace leaf_node{
#ifndef __J_leaf_node__
#define __J_leaf_node__
        // _Section_leaf_node inherit from _Section_leaf_node_base 
        // and _Section_tree_node_base
        // _Section_leaf_node_base dont have templated data, while 
        // _Section_leaf_node has
        // The templated data stored in std::pair
        template<typename _Key, typename _Tp>
        class _Section_leaf_node : public _Section_tree_node<_Key, _Tp> {
        public:
            std::pair<_Key, _Tp> _pair;
        public:
            typedef _Section_leaf_node<_Key, _Tp>* _Leaf_link_type;
            typedef _Section_tree_node<_Key, _Tp>* _Tree_link_type;
            //TODO 其实这里val可以改个名
            typedef std::pair<_Key, _Tp> _Pair;
            _Section_leaf_node() noexcept : _pair(std::pair<_Key, _Tp>()) { }
            _Section_leaf_node(_Key __key, _Tp __value) : _Section_tree_node<_Key, _Tp>(__key, __key, __value), _pair(_Pair(__key, __value)){}
            _Pair* _valptr() { return &_pair; }

            const _Pair* _valptr() const { return static_cast<const _Pair*>(&_pair); }

            const _Key& key() const {
                return _pair.first;
            }
            const _Tp& val() const {
                return _pair.second;
            }

            _Pair& pair() {
                return _pair;
            }

            void swap(const _Tree_link_type& __L) {
                _Section_tree_node<_Key, _Tp>::swap(__L);
                //此时还差pair没有变
                _Leaf_link_type tl(static_cast<_Leaf_link_type>(__L));
                const _Pair tp(tl->_pair);
                tl->_pair = _pair;
                
                _pair = tp;
            }

            virtual _Tree_link_type insert_topasa(_Tree_link_type p) {
                if (key() == 8) 
                    std::cout << "key is 8" << std::endl;
                return _Section_tree_node<_Key, _Tp>::insert_topasa(p);
            }
        };
#endif
    }
}

#endif