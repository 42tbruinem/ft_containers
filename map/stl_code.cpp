enum nodecolor { RED = false, BLACK = true };

  struct _Rb_tree_node_base
  {
	typedef _Rb_tree_node_base* ptr;
	typedef const _Rb_tree_node_base* constant_ptr;

	nodecolor	color;
	ptr		parent;
	ptr		left;
	ptr		right;

	static ptr
	_S_minimum(ptr x) _GLIBCXX_NOEXCEPT
	{
	  while (x->left != 0)
		x = x->left;
	  return x;
	}

	static constant_ptr
	_S_minimum(constant_ptr x) _GLIBCXX_NOEXCEPT
	{
	  while (x->left != 0)
		x = x->left;
	  return x;
	}

	static ptr
	_S_maximum(ptr x) _GLIBCXX_NOEXCEPT
	{
	  while (x->right != 0)
		x = x->right;
	  return x;
	}

	static constant_ptr
	_S_maximum(constant_ptr x) _GLIBCXX_NOEXCEPT
	{
	  while (x->right != 0)
		x = x->right;
	  return x;
	}
  };


  template<typename _Val>
	struct _Rb_tree_node : public _Rb_tree_node_base
	{
	  typedef _Rb_tree_node<_Val>* node_ptr;

	  __gnu_cxx::__aligned_membuf<_Val> _M_storage;

	  _Val*
	  _M_valptr()
	  { return _M_storage._M_ptr(); }

	  const _Val*
	  _M_valptr() const
	  { return _M_storage._M_ptr(); }
	};


template<typename _Tp>
	struct _Rb_tree_iterator
	{
	  typedef _Tp  value_type;
	  typedef _Tp& reference;
	  typedef _Tp* pointer;

	  typedef bidirectional_iterator_tag iterator_category;
	  typedef ptrdiff_t                  difference_type;

	  typedef _Rb_tree_iterator<_Tp>        _Self;
	  typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
	  typedef _Rb_tree_node<_Tp>*           node_ptr;

	  _Rb_tree_iterator() _GLIBCXX_NOEXCEPT
	  : _M_node() { }

	  explicit
	  _Rb_tree_iterator(_Base_ptr __x) _GLIBCXX_NOEXCEPT
	  : _M_node(__x) { }

	  reference
	  operator*() const _GLIBCXX_NOEXCEPT
	  { return *static_cast<node_ptr>(_M_node)->_M_valptr(); }

	  pointer
	  operator->() const _GLIBCXX_NOEXCEPT
	  { return static_cast<node_ptr> (_M_node)->_M_valptr(); }

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

	  bool
	  operator==(const _Self& __x) const _GLIBCXX_NOEXCEPT
	  { return _M_node == __x._M_node; }

	  bool
	  operator!=(const _Self& __x) const _GLIBCXX_NOEXCEPT
	  { return _M_node != __x._M_node; }

	  _Base_ptr _M_node;
  };
