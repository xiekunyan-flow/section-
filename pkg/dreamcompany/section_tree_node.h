#ifndef SECTION_TREE_NODE_H_INCLUDE
#define SECTION_TREE_NODE_H_INCLUDE
#include "section_node.h"
namespace J {
namespace tree_node {
template <typename _Key, typename _Tp>
class _Section_tree_node : public _Section_tree_node_base {
 public:
  typedef std::pair<const _Key, _Tp> value_type;
  typedef _Tp mapped_type;
  //typedef bool _Is_leaf;

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
 public:
  _Key _left_key;
  _Key _right_key;
  bool _has_mid;
  bool _Is_leaf;
  _Tp _sum;        //当前版本只能求和
  unsigned _size;  //该节点下有多少个叶子结点
  _Tp _add;        //该节点下的所有叶子节点增加的值
 public:
  _Section_tree_node<_Key, _Tp>() noexcept : _left_key(_Key()), _right_key(_Key()), _has_mid(false), _Is_leaf(false), _sum(_Tp()), _add(_Tp()), _size(1) {}

  _Section_tree_node<_Key, _Tp>(_Key __left_key, _Key __right_key, _Tp __sum) noexcept : _left_key(__left_key), _right_key(__right_key), _has_mid(false), _Is_leaf(false), _sum(__sum), _add(_Tp()), _size(1) {}

  //和家福说的 push_up 很类似
  void maintence() {
    auto r(static_cast<_Section_tree_node<_Key, _Tp>*>(_right));
    _sum = r->_sum;
    _right_key = r->_right_key;
    _left_key = r->left_key();
    _size = r->_size;

    if (_left != nullptr) {
      auto l(static_cast<_Section_tree_node<_Key, _Tp>*>(_left));
      _sum += l->_sum;
      _left_key = l->left_key();
      _size += l->_size;
    }
  }
  virtual void push_down(_Tp __d_add) {
    _add += __d_add;
    _sum += __d_add * _size;
  }
  const _Key& right_key() {
    return _right_key;
  }

  const _Key& left_key() {
    return _left_key;
  }

  virtual void swap(const _Tree_link_type& __L) {
    if (_left != nullptr) _left->_parent = __L;
    if (__L->_left != nullptr) __L->_left->_parent = this;
    auto p(__L->_left);
    __L->_left = _left;
    _left = p;

    if (_right != nullptr) _right->_parent = __L;
    if (__L->_right != nullptr) __L->_right->_parent = this;
    p = __L->_right;
    __L->_right = _right;
    _right = p;

    _has_mid ^= __L->_has_mid ^= _has_mid ^= __L->_has_mid;
    _Is_leaf ^= __L->_Is_leaf ^= _Is_leaf ^= __L->_Is_leaf;

    auto s(__L->_sum);
    __L->_sum = _sum;
    _sum = s;

    auto k(__L->_right_key);
    __L->_right_key = _right_key;
    _right_key = k;

    k = __L->left_key();
    __L->_left_key = _left_key;
    _left_key = k;

    unsigned sz{__L->_size};
    __L->_size = _size;
    _size = sz;
  }
  /**
    * @brief 
    * 
    * @param p 
    * @return _Tree_link_type 若返回结果恰好为p, 则需要遍历修复 p 及上面的所有节点
    */
  virtual _Tree_link_type insert_topasa(_Tree_link_type p) {
    const _Tree_link_type& a(this);
    _Tree_link_type p2(static_cast<_Tree_link_type>(p->_right));
    auto __key(a->right_key());
    if (!p->_has_mid) {  //p只有一个孩子
      if (__key == p2->right_key())
        return nullptr;
      else if (__key < p2->right_key()) {
        swap(p2);
      }
      p->_left = p2;
      p->_right = a;
      a->_parent = p;
      p->_has_mid = true;

      a->_prev = p2;
      a->_next = p2->_next;
      if (a->_next != nullptr)
        a->_next->_prev = a;
      p2->_next = a;

      return p;
    }
    //p 有两个孩子
    _Tree_link_type p1(static_cast<_Tree_link_type>(p->_left));

    _Key mid_key{p1->right_key()};
    if (__key < mid_key) {
      swap(p1);
      swap(p2);
    } else if (__key < p2->right_key()) {
      swap(p2);
    }

    a->_prev = p2;
    a->_next = p2->_next;
    if (a->_next != nullptr)
      a->_next->_prev = a;
    p2->_next = a;

    if (p->_next != nullptr && p->_next->_left == nullptr) {
      static_cast<_Tree_link_type>(p->_next)->_has_mid = true;

      a->_parent = p->_next;
      p->_next->_left = a;
      return static_cast<_Tree_link_type>(p->_next);
    }
    //这里其实可以用复制构造函数, 或者一个其他函数?
    _Tree_link_type pp = new _Section_tree_node<_Key, _Tp>(left_key(), right_key(), _sum);
    a->_parent = pp;
    pp->_right = a;
    pp->_size = a->_size;

    return pp;
  }

  /**
   * @brief 更新数值信息: 和
   * 
   */
  void push_up() {
    _sum = static_cast<_Tree_link_type>(_left)->_sum + static_cast<_Tree_link_type>(_right)->_sum;
    _right_key = static_cast<_Tree_link_type>(_right)->_right_key;
    _left_key = static_cast<_Tree_link_type>(_right)->_left_key;
    _size = static_cast<_Tree_link_type>(_right)->_size;

    if (_left != nullptr)
      _left_key = static_cast<_Tree_link_type>(_left)->_left_key;
    _size += static_cast<_Tree_link_type>(_left)->_size;
  }
  virtual inline void push_up(_Tp __d_add, unsigned __size) {
    _sum += __d_add * __size;
  }
};

}  // namespace tree_node
}  // namespace J
#endif