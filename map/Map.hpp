/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/16 15:13:49 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/09 21:19:09 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "GenericFunctions.hpp"
# include <memory>
# include <traits.hpp>
# include <cstdlib>

//TODO write insert with "hint"

namespace ft
{
	template <class KeyVal>
	struct node
	{
		node(const KeyVal& keyval, node *parent = NULL, node *left = NULL, node *right = NULL) :
		parent(parent),
		left(left),
		right(right),
		keyval(keyval) {}

		node(const node& other) :
		parent(other.parent),
		left(other.left),
		right(other.right),
		keyval(other.keyval) {}

		node& operator = (const node& other)
		{
			if (this != &other)
			{
				this->key = other.key;
				this->keyval = other.keyval;
				this->parent = other.parent;
				this->left = other.left;
				this->right = other.right;
			}
			return (*this);
		}
		~node() {}

//------------------------------------------VARIABLES------------------------------------------

		node	*parent;
		node	*left;
		node	*right;
		KeyVal	keyval;
	};
}

namespace ft
{
	template <class Value, class Reference, class Pointer, class Category = ft::bidirectional_iterator_tag>
	class Iterator
	{
		private:
			typedef typename ft::node<Value>	node;
			node*								ptr;
		public:
			typedef Category					iterator_category;
			typedef Reference					reference;
			typedef Pointer						pointer;
			typedef Value						keyvalue;

			Iterator(node* ptr = NULL) : ptr(ptr) {}
			Iterator(const Iterator<keyvalue, keyvalue&, keyvalue*>& other) : ptr(other.ptr) {}
			Iterator&	operator = (const Iterator& other)
			{
				if (this != &other)
				{
					this->ptr = other.ptr;
				}
				return (*this);
			}
			~Iterator() {}
			bool	operator == (const Iterator& other) const
			{
				return (this->ptr == other.ptr);
			}
			bool	operator != (const Iterator& other) const
			{
				return !(*this == other);
			}
			Iterator	operator ++ (int)
			{
				Iterator old(*this);

				this->ptr = this->ptr->next();
				return (old);
			}
			Iterator&	operator ++ ()
			{
				this->ptr = this->ptr->next();
				return (*this);
			}
			Iterator	operator -- (int)
			{
				Iterator old(*this);

				this->ptr = this->ptr->prev();
				return (old);
			}
			Iterator&	operator -- ()
			{
				this->ptr = this->ptr->prev();
				return (*this);
			}
			Pointer	operator -> ()
			{
				return (&this->ptr->keyval);
			}
			Reference	operator * ()
			{
				return (this->ptr);
			}
	};
}

namespace ft
{
	//ReverseIterator serves as a wrapper for Iterator
	template <class Iterator>
	class ReverseIterator
	{
		public:
			typedef typename Iterator::iterator_category			iterator_category;
			typedef typename Iterator::reference					reference;
			typedef typename Iterator::pointer						pointer;
			typedef typename Iterator::keyvalue						keyvalue;
		private:
			typedef typename ft::node<keyvalue>						node;
			Iterator	iterator;
		public:
			ReverseIterator(node* ptr) : iterator(ptr) {}
			ReverseIterator(const Iterator& other) : iterator(other) {}
			ReverseIterator(const ReverseIterator& other) : iterator(other.iterator) {}
			ReverseIterator& operator = (const ReverseIterator& other)
			{
				this->iterator = other.iterator;
				return (*this);
			}
			ReverseIterator& operator = (const Iterator& other)
			{
				this->iterator = other;
				return (*this);
			}
			~ReverseIterator() {}
			bool				operator == (const ReverseIterator& other) const { return this->iterator == other.iterator; }
			bool				operator != (const ReverseIterator& other) const { return !(*this == other); }
			ReverseIterator&	operator ++ ()
			{
				this->iterator--;
				return (*this);
			}
			ReverseIterator		operator ++ (int)
			{
				ReverseIterator	old(*this);
				++(*this);
				return (old);
			}
			ReverseIterator&	operator -- ()
			{
				this->iterator++;
				return (*this);
			}
			ReverseIterator		operator -- (int)
			{
				ReverseIterator old(*this);
				--(*this);
				return (old);
			}
			reference			operator*()
			{
				return (Iterator::operator*());
			}
			pointer				operator->()
			{
				return (Iterator::operator->());
			}
	};
}

namespace ft
{
	template <class Key, class Val, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, Val> > >
	class map
	{
		private:
			typedef ft::pair<const Key, Val>										keyval_type;
			typedef typename ft::node<keyval_type>									node;
		public:
			typedef Key																key_type;
			typedef Val																mapped_type;
			typedef ft::pair<const Key, Val>										value_type;
			typedef Compare															key_compare;
			typedef Alloc															allocator_type;
			typedef value_type&														reference;
			typedef const Val&														const_reference;
			typedef value_type*														pointer;
			typedef const Val*														const_pointer;
			typedef Iterator<value_type, value_type&, value_type*>					iterator;
			typedef Iterator<value_type, const value_type&, const value_type*>		const_iterator;
			typedef ReverseIterator<iterator>										reverse_iterator;
			typedef ReverseIterator<const_iterator>									const_reverse_iterator;
			typedef ptrdiff_t														difference_type;
			typedef size_t															size_type;

			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				protected:
					Compare comp;
				public:
					value_compare (Compare c) : comp(c) {}
					typedef bool											result_type;
					typedef value_type										first_argument_type;
					typedef value_type										second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

//-------------------------------------------------------CONSTRUCTORS-----------------------------------------------------

			//DEFAULT
			explicit map(const Compare& compare = Compare(), const Alloc& alloc = Alloc()) : root(NULL), first(new node()), last(new node()), len(0), compare(compare), allocator(alloc)
			{
				this->first->parent = this->last;
				this->last->parent = this->first;
			}

			//COPY
			map(const map& other) : root(NULL), first(new node()), last(new node()), len(0), compare(other.compare), allocator(other.allocator)
			{
				this->first->parent = this->last;
				this->last->parent = this->first;
				*this = other;
			}

			//RANGE
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const Compare& compare = Compare(), const Alloc& alloc = Alloc(),
			typename enable_if<is_iterator<typename InputIterator::iterator_category>::result, InputIterator>::type* = NULL) :
				root(NULL), first(new node()), last(new node()), len(0), compare(compare), allocator(alloc)
			{
				this->first->parent = this->last;
				this->last->parent = this->first;
				this->insert(first, last);
			}

//-------------------------------------------------------ASSIGNMENT OPERATOR-----------------------------------------------------

			map& operator = (const map& other)
			{
				if (this != &other)
				{
					this->clear();
					this->insert(other.begin(), other.end());
				}
				return (*this);
			}

//-------------------------------------------------------DESTRUCTOR-----------------------------------------------------

			~map()
			{
				this->clear();
				delete this->first;
				delete this->last;
			}

//-------------------------------------------------------ITERATORS-----------------------------------------------------

			iterator	begin()
			{
				return (iterator(this->first->parent));
			}
			const_iterator begin() const
			{
				return (const_iterator(this->first->parent));
			}

			iterator	end()
			{
				return (iterator(this->last));
			}
			const_iterator end() const
			{
				return (const_iterator(const_cast<node*>(this->last)));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->last->parent));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->last->parent));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->first));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->first));
			}

//-------------------------------------------------------CAPACITY-----------------------------------------------------

			bool	empty() const
			{
				return (!this->len);
			}

			size_t	size() const
			{
				return (this->len);
			}

			size_t max_size() const
			{
				return (this->allocator.max_size());
			}

//-------------------------------------------------------ELEMENT ACCESS-----------------------------------------------------

			Val&	operator [] (const Key& key)
			{
				iterator it = find(key);
				if (it == this->end())
					it = insert(value_type(key, Val())).first;
				return (it->second);
			}

//-------------------------------------------------------MODIFIERS-----------------------------------------------------

			void	clear()
			{
				erase(this->begin(), this->end());
			}

			ft::pair<iterator, bool> insert (const value_type& value)
			{
				iterator it = find(value.first);
				if (it != this->end())
					return (ft::pair<iterator, bool>(it, false));
				node **iter = &this->root;
				node *parent = NULL;
				while (*iter && *iter != this->first && *iter != this->last)
				{
					parent = (*iter);
					if (this->value_comp()((*iter)->keyval, value))
						iter = &(*iter)->right;
					else if (this->value_comp()((*iter)->keyval))
						iter = &(*iter)->left;
				}
				*iter = new node(value, parent, NULL, NULL);
				if (this->last->parent == this->first || this->value_comp()(this->last->parent.keyval, value))
					connect_parent_child(*iter, &(*iter)->right, this->last);
				if (this->first->parent == this->last || this->value_comp()(value, this->first->parent.keyval))
					connect_parent_child(*iter, &(*iter)->left, this->first);
				this->len++;
				return (ft::pair<iterator, bool>(iterator(*iter), true));
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last,
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::result, InputIterator>::type* = NULL)
			{
				for (;first != last; first++)
					insert(*first);
			}

			void	erase(iterator it)
			{
				node *iter = it.getptr();
				if (!iter)
					return ;

				node*	lowest = NULL;
				node*	highest = NULL;
				if (iter->left == this->first)
				{
					lowest = iter->next();
					connect_parent_child(lowest, &lowest->left, this->first);
				}
				if (iter->right == this->last)
				{
					highest = iter->prev();
					connect_parent_child(highest, &highest->right, this->last);
				}
				if (lowest)
					iter->left = NULL;
				if (highest)
					iter->right = NULL;

				node*	replacement = NULL;
				if (iter->right && iter->left)
				{
					replacement = iter->left;
					while (replacement->right)
						replacement = replacement->right;
					if (replacement != iter->left)
					{
						replacement->parent->right = replacement->left;
						if (replacement->left && replacement->left != this->first)
						{
							replacement->left->parent = replacement->parent;
							replacement->left = NULL;
						}
					}
				}
				else if (iter->right)
					replacement = iter->right;
				else if (iter->left)
					replacement = iter->left;

				node**	replacementparent_link = (replacement) ? replacement->link_to_parent() : NULL;
				if (iter->parent && iter->parent->left == iter)
					iter->parent->left = replacement;
				else if (iter->parent && iter->parent->right == iter)
					iter->parent->right = replacement;
				else if (!iter->parent)
					this->root = replacement;
				if (replacement)
				{
					if (replacementparent_link)
						*replacementparent_link = NULL;
					if (!replacement->left)
						connect_parent_child(replacement, &replacement->left, iter->left);
					if (!replacement->right)
						connect_parent_child(replacement, &replacement->right, iter->right);
					replacement->parent = iter->parent;
				}
				delete iter;
				this->len--;
			}

			size_t	erase(const Key& key)
			{
				iterator it = find(key);
				if (it == this->end())
					return (0);
				erase(it);
				return (1);
			}

			void	erase(iterator first, iterator last)
			{
				for (;first != last;)
					erase(first++);
			}

			void	swap(map& other)
			{
				ft::swap(this->allocator, other.allocator);
				ft::swap(this->first, other.first);
				ft::swap(this->last, other.last);
				ft::swap(this->root, other.root);
				ft::swap(this->len, other.len);
				ft::swap(this->compare, other.compare);
			}

//-------------------------------------------------------OBVSERVERS-----------------------------------------------------

			key_compare key_comp() const
			{
				return (compare);
			}

			value_compare value_comp() const
			{
				return (value_compare(this->compare));
			}

//-------------------------------------------------------OPERATIONS-----------------------------------------------------

			iterator find (const key_type& k)
			{
				if (!this->root)
					return (this->end());
				node *iter = this->root;
				iterator it = iterator(this->root);
				while (iter && iter != this->first && iter != this->last)
				{
					if (this->key_comp()(k, iter->keyval))
						iter = iter->left;
					else if (this->key_comp()(iter->keyval))
						iter = iter->right;
					else
						return (iterator(iter));
				}
				return (this->end());
			}

			const_iterator find (const key_type& k) const
			{
				return (const_iterator(const_cast<map *>(this)->find(k)));
			}

			size_t count (const key_type& k) const
			{
				if (this->find(k) == this->end())
					return (0);
				return (1);
			}

			iterator lower_bound (const key_type& k)
			{
				iterator it = this->find(k);
				if (it == this->end())
					for (it = this->begin(); it != this->end() && this->key_comp()(it->first,k); it++) {}
				else
					--it;
				return (it);
			}

			const_iterator lower_bound (const key_type& k) const
			{
				return (const_iterator(const_cast<map *>(this)->lower_bound(k)));
			}

			iterator upper_bound (const key_type& k)
			{
				iterator it = this->find(k);
				if (it == this->end())
					for (; it != this->begin() && this->key_comp()(k,it->first); it--) {}
				else
					++it;
				return (it);
			}

			const_iterator upper_bound (const key_type& k) const
			{
				return (const_iterator(const_cast<map *>(this)->upper_bound(k)));
			}

			ft::pair<iterator,iterator> equal_range (const key_type& k)
			{
				iterator first = this->lower_bound(k);
				iterator last = this->upper_bound(k);

				if (first != this->end())
					++first;
				return (ft::pair<iterator, iterator>(first, last));
			}

			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				ft::pair<iterator, iterator>	nonconst = const_cast<map *>(this)->equal_range(k);
				return (ft::pair<const_iterator, const_iterator>(const_iterator(nonconst.first), const_iterator(nonconst.second)));
			}

		private:
			void		connect_parent_child(node *parent, node **parent_childptr, node *child)
			{
				if (child)
					child->parent = parent;
				if ((child == this->first || child == this->last) && (parent == this->first || parent == this->last))
					return ;
				if (parent_childptr)
					*parent_childptr = child;
			}
			node	*root;
			node	*first;
			node	*last;
			size_t	len;
			Compare	compare;
			Alloc	allocator;
	};

//-------------------------------------------------------RELATION OPERATORS-----------------------------------------------------

	template<class Key, class Val, class Compare, class Alloc>
	bool operator == (const map<Key,Val,Compare,Alloc>& lhs, const map<Key,Val,Compare,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename map<Key,Val,Compare,Alloc>::value_compare comp = lhs.value_comp();
		typename map<Key,Val,Compare,Alloc>::const_iterator it1 = lhs.begin();
		typename map<Key,Val,Compare,Alloc>::const_iterator it2 = rhs.begin();
		for (; it1 != lhs.end(); it1++, it2++)
		{
			if (comp(*it1, *it2) || comp(*it2, *it1))
				return (false);
		}
		return (true);
	}

	template<class Key, class Val, class Compare, class Alloc>
	bool operator != (const map<Key,Val,Compare,Alloc>& lhs, const map<Key,Val,Compare,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template<class Key, class Val, class Compare, class Alloc>
	bool operator < (const map<Key,Val,Compare,Alloc>& lhs, const map<Key,Val,Compare,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), rhs.begin(), lhs.end(), rhs.end(), lhs.value_comp()));
	}

	template<class Key, class Val, class Compare, class Alloc>
	bool operator > (const map<Key,Val,Compare,Alloc>& lhs, const map<Key,Val,Compare,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template<class Key, class Val, class Compare, class Alloc>
	bool operator >= (const map<Key,Val,Compare,Alloc>& lhs, const map<Key,Val,Compare,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template<class Key, class Val, class Compare, class Alloc>
	bool operator <= (const map<Key,Val,Compare,Alloc>& lhs, const map<Key,Val,Compare,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class Val, class Compare, class Alloc>
	void	swap(map<Key,Val,Compare,Alloc>& x, map<Key,Val,Compare,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
