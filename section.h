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
  typedef _Compare key_compare;
  typedef _Alloc allocator_type;

 protected:
  // typedef _Section_node_base* 	    	_Base_ptr;
  // typedef const _Section_node_base*   	_Const_Base_ptr;
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
  _Tree_link_type _get_insert_unique_pos(key_type __Key) {
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
  /**
    * @brief  在B+树插入时，让B+树长高一层，__node会连接在新root
    *         上。
    * @param  __node  inserted new branch connected to new root.
    */
  void _build_higher_root(_Tree_node_ptr __node) {
    //TODO 这里需要关注,
  }
  /**
    *  @brief  更新节点维护信息
    *  @param  __node  需要更新的节点
    */
  void push_up(_Tree_link_type __node) {
    __node->_sum = 0;
  }
  /**
    *  @brief  交换两个叶子节点的信息
    *  @param  __nodeA 需要交换的叶子节点
    *  @param  __nodeB 需要交换的叶子节点
    */
  void swap(_Leaf_link_type& __nodeA, _Leaf_link_type& __nodeB) {
    //先交换两个
    //TODO 需清理
    const auto& pr(__nodeA->pair());
    __nodeA->pair() = __nodeB->pair();
    __nodeB->pair() = pr;
    std::cout << "Leaf link exchanged" << std::endl;
  }
  /**
    *  @brief  交换两个非叶子节点的信息
    *  @param  __nodeA 需要交换的非叶子节点
    *  @param  __nodeB 需要交换的非叶子节点
    */
  void swap(_Tree_link_type& __nodeA, _Tree_link_type& __nodeB) {
    std::cout << "Tree link exchanged" << std::endl;
  }
  /**
    *  @brief  新增一个更高的节点，并返回它
    *  @param  __node  The node who wants a higher node.
    */
  _Tree_node_ptr _build_higher_node(_Tree_node_ptr __node) {
    //TODO
    return _Tree_node_ptr();
  }

 public:
  /**
    *  @brief  插入节点
    *  @param  __value  插入的值
    *  @param  __key  插入的键
    */
  void insert(key_type __key, mapped_type __value) {
    /*TODO 待清理
     * 我的计划是, 当树为空时分类讨论, 直接插入.
     * 这个想法虽然可能欠考虑, 但可以快速看到效果
     */
    //Step 1: 新建插入的`_Section_leaf_node`节点a
    _Leaf_link_type new_leaf_node = new _Leaf_node_type(__key, __value);
    _Leaf_link_type& a(new_leaf_node);
    //Step 1.2 : 如果线段树为空直接搞
    //TODO 修复
    if (_M_header._size == 0 && _M_header._node_count == 0) {
      std::cout << __key << ' ' << __value << std::endl;
      int a{0};
      _Tree_link_type new_tree_node = new _Tree_node_type(__key, __value);

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

      std::cout << (new_tree_node->_left == nullptr) << std::endl;
      return;
    }
    /*FIXME
     * 插入过程: 找到插入位置, 平衡
     * 勿忘: _M_header _node_count可能变化, 插入成功则 _size++
     */
    //Step 2 : 寻找到插入位置
    if (__key == 6) 
      __key = 6;
    _Tree_link_type p(_get_insert_unique_pos(__key));
    std::cout << p->right_key() << std::endl;
    _Leaf_link_type p2(static_cast<_Leaf_link_type>(p->_right));

    _Tree_link_type ac{nullptr};
    for (int level(0);; level++) {
      _Tree_link_type pc{nullptr};
      if (!level) {
        pc = a->insert_topasa(p);
        // std::cout << 23 << std::endl;
      } else {
        // std::cout << 273 << std::endl;

        pc = ac->insert_topasa(p);
        // std::cout << 2739 << std::endl;
      }
      p->push_up();

      if (pc == p) {
        for (auto pc(p); static_cast<_Tree_node_ptr>(pc) != &_M_header; pc = static_cast<_Tree_link_type>(pc->_parent))
          pc->maintence();
        _M_header._node_count++;
        break;
      } else if (p->_parent == static_cast<_Tree_node_ptr>(&_M_header)) {
        _Tree_link_type root = new _Section_tree_node<_Key, _Tp>();

        _M_header._parent = root;
        root->_parent = &_M_header;

        root->_left = p;
        p->_parent = root;

        root->_right = pc;
        pc->_parent = root;

        root->push_up();
        root->_has_mid = true;
        _M_header._node_count += 2;
        break;
      } else {
        p = static_cast<_Tree_link_type>(p->_parent);
        ac = pc;

        ++_M_header._node_count;
      }
    }
    // _Leaf_link_type r1(
    a->_prev = p2;
    a->_next = p2->_next;
    a->_next->_prev = a;
    p2->_next = a;

    //TODO 修改大小
    ++_M_header._size;
  }

 public:
  unsigned long size() const {
    return _M_header._size;
  }
  void dfs(_Tree_link_type __t, std::string __s) const {
    __s += std::to_string(__t->right_key()) + " " + (__t->_has_mid ? "w " : "r ");
    if (__t->_left != nullptr) {
      dfs(static_cast<_Tree_link_type>(__t->_left), __s + "left:  ");
      if (static_cast<_Tree_link_type>(__t->_left->_parent) != __t) {
        std::cout << "Error left" << __t->right_key() << ' ' << 
        static_cast<_Tree_link_type>(__t->_left)->right_key();
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
  void traverse() const {
    for (_Leaf_node_ptr l(_M_header._next); static_cast<_Section_node_header*>(l) != &_M_header; l = l->_next) {
      _Leaf_link_type lc{static_cast<_Leaf_link_type>(l)};
      std::cout << lc->val() << ' ';
    }
    std::cout << std::endl;
    dfs(static_cast<_Tree_link_type>(_M_header._parent), "");
  }

  _Tp get(_Key __key) {
    _Tree_node_ptr t(_M_header._parent);
    for (int i{0}; t->_left != nullptr || t->_right != nullptr; i++) {
      _Tree_link_type tl(static_cast<_Tree_link_type>(t));
      std::cout << "node " << i << " " << (tl->_has_mid) << ' ' << (tl->_right_key) << ' ' << (tl->_left != nullptr) << ' ' << (tl->_right != nullptr);
      if (!tl->_has_mid || __key > static_cast<_Tree_link_type>(tl->_left)->_right_key) {
        t = t->_right;
        std::cout << " turn right" << std::endl;
      } else {
        t = t->_left;
        std::cout << " turn left" << std::endl;
      }
      // std::cout << (t!=nullptr) << (t->_left != nullptr || t->_right != nullptr) << std::endl;
    }
    _Leaf_link_type l(static_cast<_Leaf_link_type>(t));
    std::cout << "xxx " << l->key() << ' ' << l->val() << std::endl;
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
