#ifndef SECTION_TREE_NODE_H_INCLUDE
#define SECTION_TREE_NODE_H_INCLUDE
#include "section_node.h"
namespace J {
namespace tree_node {
template <typename _Key, typename _Tp>
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
  _Tp _sum;  //当前版本只能求和
 public:
  _Section_tree_node<_Key, _Tp>() noexcept : _right_key(_Key()), _has_mid(false), _Is_leaf(false), _sum(_Tp()) {}

  _Section_tree_node<_Key, _Tp>(_Key __right_key, _Tp __sum) noexcept : _right_key(__right_key), _has_mid(false), _Is_leaf(false), _sum(__sum) {}

  void maintence() {
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
      p2->_parent->_left = p2;
      p2->_parent->_right = a;
      a->_parent = p;

      return p;
    }
    //p 有两个孩子
    _Tree_link_type p1(static_cast<_Tree_link_type>(p->_left));

    _Key mid_key{p1->right_key()};
    if (__key < mid_key) {
      swap(p1);
      swap(p2);
    }
    else if (__key < p2->right_key()) {
        swap(p2);
    }

    //这里其实可以用复制构造函数, 或者一个其他函数?
    _Tree_link_type pp = new _Section_tree_node<_Key, _Tp>(right_key(), _sum);
    a->_parent = pp;
    pp->_right = a;
    return pp;
  }

  /**
   * @brief 更新数值信息: 和
   * 
   */
  void push_up() {
      _sum = static_cast<_Tree_link_type>(_left)->_sum + static_cast<_Tree_link_type>(_right)->_sum;
  }
};

}  // namespace tree_node
}  // namespace J
#endif