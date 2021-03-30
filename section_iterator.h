#ifndef SECTION_ITERATOR_H_INCLUDED
#define SECTION_ITERATOR_H_INCLUDED
namespace J
{
namespace section_iterator
{
    template<typename _Tp>
    struct _Section_iterator
    {
      typedef _Tp  value_type;
      typedef _Tp& reference;
      typedef _Tp* pointer;

      typedef bidirectional_iterator_tag iterator_category;
      typedef ptrdiff_t			 difference_type;

      typedef _Rb_tree_iterator<_Tp>		_Self;
      typedef _Rb_tree_node_base::_Base_ptr	_Base_ptr;
      typedef _Rb_tree_node<_Tp>*		_Link_type;

      _Rb_tree_iterator() _GLIBCXX_NOEXCEPT
      : _M_node() { }

      explicit
      _Rb_tree_iterator(_Base_ptr __x) _GLIBCXX_NOEXCEPT
      : _M_node(__x) { }

      reference
      operator*() const _GLIBCXX_NOEXCEPT
      { return *static_cast<_Link_type>(_M_node)->_M_valptr(); }

      pointer
      operator->() const _GLIBCXX_NOEXCEPT
      { return static_cast<_Link_type> (_M_node)->_M_valptr(); }

      _Self&
      operator++() _GLIBCXX_NOEXCEPT
      {
	_M_node = _Rb_tree_increment(_M_node);
	return *this;
      }

      _Self
      operator++(int) _GLIBCXX_NOEXCEPT
      {
	_Self __tmp = *this;
	_M_node = _Rb_tree_increment(_M_node);
	return __tmp;
      }

      _Self&
      operator--() _GLIBCXX_NOEXCEPT
      {
	_M_node = _Rb_tree_decrement(_M_node);
	return *this;
      }

      _Self
      operator--(int) _GLIBCXX_NOEXCEPT
      {
	_Self __tmp = *this;
	_M_node = _Rb_tree_decrement(_M_node);
	return __tmp;
      }

      friend bool
      operator==(const _Self& __x, const _Self& __y) _GLIBCXX_NOEXCEPT
      { return __x._M_node == __y._M_node; }

#if ! __cpp_lib_three_way_comparison
      friend bool
      operator!=(const _Self& __x, const _Self& __y) _GLIBCXX_NOEXCEPT
      { return __x._M_node != __y._M_node; }
#endif

      _Base_ptr _M_node;
  };
}
}

#endif // SECTION_ITERATOR_H_INCLUDED
