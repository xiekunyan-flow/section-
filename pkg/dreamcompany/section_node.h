#ifndef SECTION_NODE_H_INCLUDE
#define SECTION_NODE_H_INCLUDE
#include <iostream>

namespace J {
namespace basic {

//删除最基本的base类型
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
// class _Section_node_base {
// public:
//     _Section_node_base* _parent;
//     _Section_node_base() noexcept : _parent(nullptr)  {}
//     _Section_node_base(_Section_node_base* __parent) noexcept : _parent(__parent) {}

//     //
//     // @brief Only used for test.
//     //
//     std::string print();
// };

// There are 5 kinds of nodes used in Section:
// 1. _Section_leaf_node_base
// 2. _Section_tree_node_base
// 3. _Section_node_header : _Section_tree_node_base
// 4. _Section_nonleaf_node : _Section_tree_node_base
// 5. _Section_leaf_node : _Section_leaf_node_base,
//                         _Section_tree_node_base
// Base nodes and node_header(1, 2, 3) are not templated while others(4, 5)
// are templated.
class _Section_leaf_node_base {
 public:
  _Section_leaf_node_base* _next;  // next node
  _Section_leaf_node_base* _prev;  // prev node
  _Section_leaf_node_base() noexcept : _next(nullptr), _prev(nullptr) {}
  _Section_leaf_node_base(_Section_leaf_node_base* __next, _Section_leaf_node_base* __prev) noexcept : _next(__next), _prev(__prev) {}
};

class _Section_tree_node_base {
 public:
  _Section_tree_node_base* _left;    // left child
  _Section_tree_node_base* _right;   // right child
  _Section_tree_node_base* _parent;  // parent
  _Section_tree_node_base* _prev;    // prev
  _Section_tree_node_base* _next;    // next
  _Section_tree_node_base() noexcept : 
  _left(nullptr), _right(nullptr), _parent(nullptr), _prev(nullptr), _next(nullptr) {}
  _Section_tree_node_base(_Section_tree_node_base* __parent, _Section_tree_node_base* __left, _Section_tree_node_base* __right) : _parent(__parent), _left(__left), _right(__right) {}
};

// _Section_node_header inherit from _Section_tree_node_base,
//  so have member _parent, _left , and _right
// Also has member _node_count, keeps track of number of
// nodes in tree.
// Has member _size, keeps track of number of leaf nodes.
class _Section_node_header : public _Section_tree_node_base {
 public:
  std::size_t _node_count;  // Keeps track of number of nodes in tree.
  std::size_t _size;        // Number of leaf nodes.

  _Section_node_header() noexcept : _node_count(0), _size(0) {
    _left = this;
    _right = this;
    _parent = nullptr;
    _next = nullptr;
    _prev = nullptr;
  }
  //FIXME _next and _prev
  _Section_node_header(_Section_node_header&& __x) : _Section_tree_node_base{__x._parent, __x._left, __x._right}, _node_count(__x._node_count), _size(__x._size) {
    if (__x._right == &__x)
      _right = _left = this;
    else {
      _right->_left = _left->_right = this;
      __x._right = __x._left = &__x;
      __x._node_count = 0;
      __x._size = 0;
    }
  }
};
}  // namespace basic
}  // namespace J

#include "section_node.cc"

#endif
