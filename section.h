#ifndef SECTION_H_INCLUDED
#define SECTION_H_INCLUDED
#include "section_tree_node.h"
#incldue "section_leaf_node.h"
#include <bits/move.h>
#include <memory>
#include <exception_defines.h>
#include <section_iterator.h>

namespace J
{
namespace section
{
    template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
              typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
    class section
    {
    public:
        typedef _Key				    	   key_type;
        typedef _Tp					           mapped_type;
        typedef _Compare	    			   key_compare;
        typedef _Alloc			    	       allocator_type;
    protected:
        typedef _Section_node_base* 	    	_Base_ptr;
        typedef const _Section_node_base*   	_Const_Base_ptr;
        typedef _Section_leaf_node_base*        _Leaf_node_ptr;
        typedef const _Section_leaf_node_base*  _Const_leaf_node_ptr;
        typedef _Section_tree_node_base*        _Tree_node_ptr;
        typedef const _Section_tree_node_base*  _Const_Tree_node_ptr;
  //      typedef type * _Link_type;
        typedef _Section_tree_node<key_type,mapped_type>* 		    _Tree_link_type;
        typedef const _Section_tree_node<key_type,mapped_type>*	    _Const_tree_link_type;
        typedef _Section_tree_node<key_type,mapped_type>            _Tree_node_type;
        typedef const _Section_tree_node<key_type,mapped_type>      _Const_tree_node_type;
        typedef _Section_leaf_node<key_type,mapped_type>*           _Node_link_type;
        typedef const _Section_leaf_node<key_type,mapped_type>*     _Const_node_link_type;
        typedef _Section_leaf_node<key_type,mapped_type>            _Leaf_node_type;
        typedef const _Section_leaf_node<key_type,mapped_type>      _Const_leaf_node_type;
    private:
        _Section_node_header _M_header_;
        std::allocator<_Leaf_node_type> _Leaf_node_allocator;
        std::allocator<_Tree_node_type> _Tree_node_allocator;
        // 基础分配器
    protected:
    #define _Link_type _Type*
    #define _Const_link_type const _Type*
        struct _Alloc_tree_node
        {
            _Alloc_tree_node(section& __t)
                : _M_t(__t) { }

            template<typename _Type ,typename _Arg>   //构造新节点并返回,移动构造函数
            _Link_type operator()(_Arg&& __arg) const
            {
                return _M_t._M_create_node<_Type>(_GLIBCXX_FORWARD(_Arg, __arg));//std::forward<_Args>(__args)
            }

        private:
            section& _M_t;
        };
        // 分配器这一部分没有采取traits技术，而是简单的枚举allocator来进行分配和构造
        //先不考虑非标准指针的参数
        //stl_tree在get_allocator()未采用引用传参是否会导致复制开销？
        template<typename _Type)
        allocator<_Type>&
        get_allocator(){
            if(typeid(_Type) == typeid(_Leaf_node_type)) return _Leaf_node_allocator;
            if(typeid(_Type) == typeid(_Tree_node_type)) return _Tree_ndoe_allocator;
        }
        
        template<typename _Type>
        _Link_type _M_get_node()
        {
            return get_allcoator<_Type>().allocate(1);
        }
        
        template<typename _Type>
        void _M_put_node(_Link_type __p) noexpect
        {
            get_allcoator<_Type>().allocate(__p,1);
        }
        
        template<typename _Type>
        void _M_construct_node(_Link_type __node, const value_type& __x)
        {
            __try
            {
                get_allcoator<_Type>().construct(__node->_M_valptr(), __x); 
            }
            __catch(...)
            {
                _M_put_node(__node);
                __throw_exception_again;
            }
        }
        
        template<typename _Type>
        _Link_type _M_create_node(const value_type& __x)
        {
            _Link_type __tmp = _M_get_node();
            _M_construct_node(__tmp, __x);
            return __tmp;
        }
        
        template<typename _Type>
        void _M_destory_node(_Link_type __p) noexcept
        {
            get_allocator().destory(__p);
        }
        
        template<typename _Type>
        void _M_drop_node(_Link_type __p) noexcept
        {
            _M_destory_node(__p);
            _M_put_node(__p);
        }
        
        //need to modifiy
        template<typename _Type,typename _NodeGen>
        _Link_type _M_clone_node(const _Link_type __x, _NodeGen& __node_gen)
        {
        _Link_type __tmp = __node_gen(*__x->_M_valptr());
        __tmp->_left = NULL;
        __tmp->_right = NULL;
        return __tmp;
        }
        
        template<typename _Type>
        static const key_type&
        _S_key(_Const_Link_type __x)
        {
            return __x->
        }
    #undef _Link_type
    #undef _Const_link_type

    public:
        //调用内部insert_unique
        //条件判断，当_Pair可以成功构造时value_type，该语句的值为pair<iterator, bool>
        template<typename _Pair>
        __enable_if_t<is_constructible<value_type, _Pair>::value,
		      pair<iterator, bool>>
        std::insert(_Pair&& _x){
            return _M_emplace_unique(std::forward<_Pair>(__x));
        }
    private:
        //将标记下沉
        void _M_push_down(__Tree_node_type __x){
            if(__x->_left != NULL){__x->_left._M_change_mark(__x->_M_marked);}
            if(__x->_right!= NULL){__x->right._M_change_mark(__x->_M_marked);}
            __x->_M_clear_mark();
        }
    public:
      typedef _Section_iterator<value_type>       iterator;
      typedef _Section_const_iterator<value_type> const_iterator;

      typedef std::reverse_iterator<iterator>       reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    private:
        template<typename _Args>
        pair<iterator, bool>
        _M_emplace_unique(_Args&& __args);
    }

    //name implied
    template<typename _Key, typename _Val,
	   typename _Compare, typename _Alloc>
    template<typename... _Args>
      typename section<_Key, _Val,_Compare, _Alloc>::_Tree_node_type
      section<_Key, _Val, _Compare, _Alloc>::
      _M_get_insert_unique_pos(const Key_type& k)
      {

          _Tree_node_type __x = _M_root();
          //
         
          while(!__x._M_is_leaf_()){
              _M_push_down(_x);
              __x = _M_key_compare(__k, _S_key(__x)) ?
              _S_left(__x) : __S_right(__x);
          }
          return __x;
      }
    //
    template<typename _Key, typename _Val,
	   typename _Compare, typename _Alloc>
    template<typename _Args>
      pair<typename section<_Key, _Val,_Compare, _Alloc>::iterator, bool>
      section<_Key, _Val, _Compare, _Alloc>::
      _M_emplace_unique(_Args&& __args)
      {
	_Link_type __z = _M_create_node(std::forward<_Args>(__args));

	__try
	  {
	    typedef pair<iterator, bool> _Res;
	    auto __res = _M_get_insert_unique_pos(_S_key(__z));
	    if (__res.second)
	      return _Res(_M_insert_node(__res.first, __res.second, __z), true);
	
	    _M_drop_node(__z);
	    return _Res(iterator(__res.first), false);
	  }
	__catch(...)
	  {
	    _M_drop_node(__z);
	    __throw_exception_again;
	  }
      }
}
}
#endif // SECTION_H_INCLUDED
