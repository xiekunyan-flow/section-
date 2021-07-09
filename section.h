#ifndef SECTION_H_INCLUDED
#define SECTION_H_INCLUDED
#include "section_tree_node.h"
#include "section_leaf_node.h"
#include <bits/move.h>
#include <memory>
namespace J
{
    //这里可能有bug,暴漏问题
    using namespace J::tree_node;
    using namespace J::leaf_node;
    template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
              typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
    class section
    {
    private:
    public:
        typedef _Key				    	   key_type;
        typedef _Tp					           mapped_type;
        typedef _Compare	    			   key_compare;
        typedef _Alloc			    	       allocator_type;
    protected:
        // typedef _Section_node_base* 	    	_Base_ptr;
        // typedef const _Section_node_base*   	_Const_Base_ptr;
        typedef _Section_leaf_node_base*        _Leaf_node_ptr;
        typedef const _Section_leaf_node_base*  _Const_leaf_node_ptr;
        typedef _Section_tree_node_base*        _Tree_node_ptr;
        typedef const _Section_tree_node_base*  _Const_Tree_node_ptr;
        typedef _Section_tree_node<key_type,mapped_type>* 		    _Tree_link_type;
        typedef const _Section_tree_node<key_type,mapped_type>*	    _Const_tree_Link_type;
        typedef _Section_tree_node<key_type,mapped_type>            _Tree_node_type;
        typedef const _Section_tree_node<key_type,mapped_type>      _Const_tree_node_type;
        typedef _Section_leaf_node<key_type,mapped_type>*           _Node_link_type;
        typedef const _Section_leaf_node<key_type,mapped_type>*     _Const_node_link_type;
        typedef _Section_leaf_node<key_type,mapped_type>            _Leaf_node_type;
        typedef const _Section_leaf_node<key_type,mapped_type>      _Const_leaf_node_type;
    public:
        _Section_node_header _M_header;
    private:
        std::allocator<_Leaf_node_type> _Leaf_node_allocator;
        std::allocator<_Tree_node_type> _Tree_node_allocator;
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
    public:
        /**
         * @brief  寻找到__Key应该对应的_Tree_node_ptr节点, if we 
         *         want to insert __Key.
         * @param  __Key  key of the node to be inserted.
         */
        _Tree_node_ptr _get_insert_unique_pos(key_type __Key) {
            //TODO
            return _Tree_node_ptr();
        }
        /**
         * @brief  在B+树插入时，让B+树长高一层，__node会连接在新root
         *         上。
         * @param  __node  inserted new branch connected to new root.
         */
        void _build_higher_root(_Tree_node_ptr __node) {
            //TODO
        }
        /**
         *  @brief  更新节点维护信息
         *  @param  __node  需要更新的节点
         */
        void push_up(_Tree_node_ptr __node) {
            //TODO
        }
        /**
         *  @brief  交换两个叶子节点的信息
         *  @param  __nodeA 需要交换的叶子节点
         *  @param  __nodeB 需要交换的叶子节点
         */
        void swap(_Node_link_type __nodeA, _Node_link_type __nodeB) {
            //TODO
        } 
        /**
         *  @brief  交换两个非叶子节点的信息
         *  @param  __nodeA 需要交换的非叶子节点
         *  @param  __nodeB 需要交换的非叶子节点
         */
        void swap(_Tree_link_type __nodeA, _Tree_link_type __nodeB) {
            //TODO
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
         *  @param  __pair  插入的pair类型键值对
         */
        void insert(mapped_type __pair) {
            //TODO: insert 
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
    
}
#endif // SECTION_H_INCLUDED
