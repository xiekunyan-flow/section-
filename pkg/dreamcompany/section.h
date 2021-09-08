#ifndef SECTION_H_INCLUDED
#define SECTION_H_INCLUDED
#include <bits/move.h>

#include <iostream>
#include <memory>
#include <string>

#include "section_leaf_node.h"
#include "section_tree_node.h"
namespace J {
using namespace J::tree_node;
using namespace J::leaf_node;
template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
          typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
class section {
 private:
 public:
  typedef _Key key_type;
  typedef _Tp mapped_type;
  typedef std::pair<_Key, _Tp> _Pair;
  typedef _Compare key_compare;
  typedef _Alloc allocator_type;

 protected:
  typedef _Section_leaf_node_base* _Leaf_node_ptr;
  typedef const _Section_leaf_node_base* _Const_leaf_node_ptr;
  typedef _Section_tree_node_base* _Tree_node_ptr;
  typedef const _Section_tree_node_base* _Const_Tree_node_ptr;
  typedef _Section_tree_node<key_type, mapped_type>* _Tree_link_type;
  typedef const _Section_tree_node<key_type, mapped_type>* _Const_tree_Link_type;
  typedef _Section_tree_node<key_type, mapped_type> _Tree_node_type;
  typedef const _Section_tree_node<key_type, mapped_type> _Const_tree_node_type;
  typedef _Section_leaf_node<key_type, mapped_type>* _Leaf_link_type;
  typedef const _Section_leaf_node<key_type, mapped_type>* _Const_leaf_link_type;
  typedef _Section_leaf_node<key_type, mapped_type> _Leaf_node_type;
  typedef const _Section_leaf_node<key_type, mapped_type> _Const_leaf_node_type;

 public:
  _Section_node_header _M_header;

 private:
  std::allocator<_Leaf_node_type> _Leaf_node_allocator;
  std::allocator<_Tree_node_type> _Tree_node_allocator;
  //TO-DO 清理这里的注释代码
  // 基础分配器
  // struct _Alloc_tree_node
  // {
  //     _Alloc_tree_node(section& __t)
  //         : _M_t(__t) { }

  //     template<typename _Type ,typename _Arg>   //构造新节点并返回,移动构造函数
  //     _Type* operator()(_Arg&& __arg) const
  //     {
  //         return _M_t._M_create_node<_Type>(_GLIBCXX_FORWARD(_Arg, __arg));//std::forward<_Args>(__args)
  //     }

  // private:
  //     section& _M_t;
  // };
 protected:
  //这里没有采取萃取机技术，而是简单的使用allocator
  // template<typename _Type>
  // _Type* _M_get_node()
  // {
  //     if(typeid(_Type) == typeid(_Leaf_node_type)) return _Leaf_node_allocator.allocate(1);
  //     if(typeid(_Type) == typeid(_Tree_node_type)) return _Tree_node_allocator.allocate(1);
  // }
  //在这里我改成单参数的形式
  // template<typename _Type,typename _Arg>
  // _Type* _M_create_node(_Arg&& __arg)
  // {
  //     _Type* __tmp = _M_get_node();
  //     _M_construct_node(__tmp, _GLIBCXX_FORWARD(_Arg, __arg));
  //     return __tmp;
  // }
 public:
  //调用内部insert_unique
  //条件判断，当_Pair可以成功构造时value_type，该语句的值为pair<iterator, bool>
  // template<typename _Pair>
  // __enable_if_t<is_constructible<value_type, _Pair>::value,
  //       pair<iterator, bool>>
  // std::insert(_Pair&& _x){
  //     typedef pair<_Base_ptr, _Base_ptr> _Res;

  // }
 private:
  /**
    * @brief  寻找到__Key应该对应的_Tree_node_ptr节点, if we 
    *         want to insert __Key.
    * @param  __Key  key of the node to be inserted.
    */
  _Tree_link_type _get_insert_unique_pos(key_type __Key) const {
    //确保这里树不为空了已经了
    _Tree_node_ptr tl(_M_header._parent);
    for (; tl->_left != nullptr || tl->_right != nullptr;) {
      _Tree_link_type tlc(static_cast<_Tree_link_type>(tl));
      if (!tlc->_has_mid || __Key > static_cast<_Tree_link_type>(tlc->_left)->right_key())
        tl = tl->_right;
      else
        tl = tl->_left;
    }
    return static_cast<_Tree_link_type>(tl->_parent);
  }

 public:
  /**
    *  @brief  插入节点
    *  @param  __value  插入的值
    *  @param  __key  插入的键
    */
  void insert(key_type __key, mapped_type __value) {
    //Step 1: 新建插入的`_Section_leaf_node`节点a
    _Leaf_link_type new_leaf_node = new _Leaf_node_type(__key, __value);
    _Leaf_link_type a(new_leaf_node);
    //Step 1.2 : 如果线段树为空直接搞
    if (_M_header._size == 0 && _M_header._node_count == 0) {
      _Tree_link_type new_tree_node = new _Tree_node_type(__key, __key, __value);

      new_tree_node->_right = new_leaf_node;
      new_leaf_node->_parent = new_tree_node;

      _M_header._parent = new_tree_node;
      new_tree_node->_parent = &_M_header;

      _M_header._prev = new_leaf_node;
      new_leaf_node->_next = &_M_header;

      _M_header._next = new_leaf_node;
      new_leaf_node->_prev = &_M_header;

      _M_header._node_count = 2;
      _M_header._size = 1;

      return;
    }
    //Step 2 : 寻找到插入位置
    if (__key == 6)
      __key = 6;
    _Tree_link_type p(_get_insert_unique_pos(__key));
    std::cout << p->right_key() << std::endl;
    _Leaf_link_type p2(static_cast<_Leaf_link_type>(p->_right));

    _Tree_link_type ac{a};
    for (int level(0);; level++) {
      //Step 3: 尝试插入
      _Tree_link_type pc{ac->insert_topasa(p)};

      //Step 3.1: 修复父节点
      p->push_up();

      if (pc == p) {
        //Step 4.1: 情况一, p 只有一个孩子, 所以直接插入
        for (auto pc(p); static_cast<_Tree_node_ptr>(pc) != &_M_header; pc = static_cast<_Tree_link_type>(pc->_parent))
          pc->push_up();
        _M_header._node_count++;
        break;
      } else if (pc == static_cast<_Tree_link_type>(p->_next)) {
        for (auto pc(p); static_cast<_Tree_node_ptr>(pc) != &_M_header; pc = static_cast<_Tree_link_type>(pc->_parent))
          pc->push_up();
        for (auto px(pc); static_cast<_Tree_node_ptr>(px) != &_M_header; px = static_cast<_Tree_link_type>(px->_parent))
          px->push_up();
        _M_header._node_count++;
        traverse();
        break;
      } else if (p->_parent == static_cast<_Tree_node_ptr>(&_M_header)) {
        //Step 4.2: 情况二, p 有两个孩子且是根节点, 新建一个根节点
        _Tree_link_type root = new _Section_tree_node<_Key, _Tp>();

        _M_header._parent = root;
        root->_parent = &_M_header;

        root->_left = p;
        p->_parent = root;

        root->_right = pc;
        pc->_parent = root;

        root->push_up();
        root->_has_mid = true;

        p->_next = pc;
        pc->_prev = p;

        _M_header._node_count += 2;
        break;
      } else {
        //Step 4.3: 情况三, p 有两个孩子且不是根节点
        p = static_cast<_Tree_link_type>(p->_parent);
        ac = pc;

        ++_M_header._node_count;
      }

      //Step 5: 重复Step 3 至 4
    }

    //TODO 现在默认可以插入成功, 因而标记_size++
    ++_M_header._size;
  }

 private:
  _Pair get_min_pair() const {
    return static_cast<_Leaf_link_type>(_M_header._next)->pair();
  }

  /**
   * @brief 得到 __t 中 key 位于 [__l, __r) 之间的叶子结点的 value 和. O(log n)
   * 
   * @param __t 非叶子节点
   * @param __l 最小值(含)
   * @param __r 最大值(不含)
   * @return mapped_type 和
   */
  mapped_type get_sum(_Tree_link_type __t, key_type __l, key_type __r) const {
    if (__t == nullptr) return mapped_type();
    key_type mr(__t->right_key());
    key_type ml(__t->left_key());
    if (mr < __l || ml >= __r) return mapped_type();
    if (ml >= __l && mr < __r) return __t->_sum;
    _Tree_link_type l{static_cast<_Tree_link_type>(__t->_left)};
    _Tree_link_type r{static_cast<_Tree_link_type>(__t->_right)};
    if (l != nullptr) l->push_down(__t->_add);
    r->push_down(__t->_add);
    __t->_add = _Tp();
    return get_sum(l, __l, __r) + get_sum(r, __l, __r);
  }

 public:
  /**
   * @brief 求指定[__l, __r) 范围内的和
   * 
   * @param __l 最小值(含)
   * @param __r 最大值(不含)
   * @return mapped_type 和
   */
  mapped_type query(key_type __l, key_type __r) const {
    if (__l >= __r) return mapped_type();
    return get_sum(static_cast<_Tree_link_type>(_M_header._parent), __l, __r);
  }

 private:
  /**
    * @brief 对 __t 下, key 处于 [__l, __r) 之间的所有叶子节点增加 __d_add
    * 
    * @param __t 非叶子节点
    * @param __l 最小值(含)
    * @param __r 最大值(不含)
    * @param __d_add 增加值
    */
  void add_range(_Tree_link_type __t, key_type __l, key_type __r, mapped_type __d_add) {
    if (__t == nullptr) return;
    key_type mr(__t->right_key());
    key_type ml(__t->left_key());
    if (mr < __l || ml >= __r) return;
    if (ml >= __l && mr < __r) {
      __t->_add += __d_add;
      for (_Tree_link_type pc(__t); static_cast<_Tree_node_ptr>(pc) != &_M_header; pc = static_cast<_Tree_link_type>(pc->_parent))
        pc->push_up(__d_add, __t->_size);
      return;
    }
    add_range(static_cast<_Tree_link_type>(__t->_left), __l, __r, __d_add);
    add_range(static_cast<_Tree_link_type>(__t->_right), __l, __r, __d_add);
  }

 public:
  /**
    * @brief 对 key 处于 [__l, __r) 之间的所有叶子节点增加 __d_add
    * 
    * @param __l 最小值(含)
    * @param __r 最大值(不含)
    * @param __d_add 增加值
    */
  void add_range(key_type __l, key_type __r, mapped_type __d_add) {
    if (__l >= __r) return;
    add_range(static_cast<_Tree_link_type>(_M_header._parent), __l, __r, __d_add);
  }

 public:
  unsigned long size() const {
    return _M_header._size;
  }

 private:
  // for traverse
  void dfs(_Tree_link_type __t, std::string __s) const {
    __s += std::to_string(__t->right_key()) + " " + (__t->_has_mid ? "w " : "r ");
    if (__t->_left != nullptr) {
      dfs(static_cast<_Tree_link_type>(__t->_left), __s + "left:  ");
      if (static_cast<_Tree_link_type>(__t->_left->_parent) != __t) {
        std::cout << "Error left" << __t->right_key() << ' ' << static_cast<_Tree_link_type>(__t->_left)->right_key();
        for (auto i(static_cast<_Tree_node_ptr>(__t)); i != nullptr; i = i->_right)
          std::cout << ' ' << 0;
        std::cout << std::endl;
      }
    }
    if (__t->_right != nullptr) {
      dfs(static_cast<_Tree_link_type>(__t->_right), __s + "right: ");
      if (static_cast<_Tree_link_type>(__t->_right->_parent) != __t) {
        std::cout << "Error right" << __t->right_key();
        for (auto i(static_cast<_Tree_node_ptr>(__t)); i != nullptr; i = i->_right)
          std::cout << ' ' << 0;
        std::cout << std::endl;
      }
    }
    if (__t->_left == nullptr && __t->_right == nullptr) {
      std::cout << __s << std::endl;
    }
  }
 public:
  /**
   * @brief 这是一个测试函数, 用来得到整个树的结构. 通过两种方式得到树的结构, 
   *        1. 得到每一条从根到叶子的路径
   *        2. 层次遍历
   * 
   */
  void traverse() const {
    dfs(static_cast<_Tree_link_type>(_M_header._parent), "");
    int i{0};
    for (_Tree_node_ptr t(_M_header._parent); t != nullptr; i++) {
      std::cout << "level " << i << std::endl;
      _Key k(static_cast<_Tree_link_type>(t)->right_key());
      for (_Tree_node_ptr t0(t); t0 != nullptr && t0 != &_M_header; t0 = t0->_next) {
        _Tree_link_type l(static_cast<_Tree_link_type>(t0));
        std::cout << "(" << l->left_key() << ", " << l->right_key() << ", " << l->_size << ", " << l->_sum << ") ";
        if (k > l->right_key())
          std::cout << "Wrong" << std::endl;
        k = l->right_key();
      }
      std::cout << std::endl;
      if (t->_left != nullptr)
        t = t->_left;
      else
        t = t->_right;
    }
  }

  _Tp get(_Key __key) const {
    _Tree_node_ptr t(_M_header._parent);
    for (int i{0}; t->_left != nullptr || t->_right != nullptr; i++) {
      _Tree_link_type tl(static_cast<_Tree_link_type>(t));

      _Tree_link_type l{static_cast<_Tree_link_type>(tl->_left)};
      _Tree_link_type r{static_cast<_Tree_link_type>(tl->_right)};
      if (l != nullptr) l->push_down(tl->_add);
      r->push_down(tl->_add);
      tl->_add = _Tp();

      if (!tl->_has_mid || __key > static_cast<_Tree_link_type>(tl->_left)->right_key()) {
        t = t->_right;
        std::cout << " turn right" << std::endl;
      } else {
        t = t->_left;
        std::cout << " turn left" << std::endl;
      }
    }
    _Leaf_link_type l(static_cast<_Leaf_link_type>(t));
    std::cout << "xxx " << l->key() << ' ' << l->val() << ' ' << l->_sum << std::endl;
    return l->val();
  }
};

//name implied
// template<typename _Key, typename _Val,
//    typename _Compare, typename _Alloc>
// template<typename... _Args>
//   pair<typename _Rb_tree<_Key, _Val,_Compare, _Alloc>::iterator, bool>
//   _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
//   _M_get_insert_unique_pos(const Key_type& k)
//   {
//       typedef pair<_Tree_node_ptr,_Tree_node_ptr> _Res;
//       _Tree_node_type __x = _M_root();
//       //_Tree_node_type __y = _M_end();
//       while(!__x._IS_node_()){
//           __x
//       }
//   }

// template<typename _Key, typename _Val,
//    typename _Compare, typename _Alloc>
// template<typename... _Args>
//   pair<typename _Rb_tree<_Key, _Val,_Compare, _Alloc>::iterator, bool>
//   _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::
//   _M_emplace_unique(_Args&&... __args)
//   {
// _Link_type __z = _M_create_node(std::forward<_Args>(__args)...);

// __try
//   {
//     typedef pair<iterator, bool> _Res;
//     auto __res = _M_get_insert_unique_pos(_S_key(__z));
//     if (__res.second)
//       return _Res(_M_insert_node(__res.first, __res.second, __z), true);

//     _M_drop_node(__z);
//     return _Res(iterator(__res.first), false);
//   }
// __catch(...)
//   {
//     _M_drop_node(__z);
//     __throw_exception_again;
//   }
//   }
}  // namespace J

#endif  // SECTION_H_INCLUDED
