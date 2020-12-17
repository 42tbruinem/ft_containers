/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/16 15:13:49 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/12/16 16:41:23 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "GenericFunctions.hpp"
# include <stdio.h>
# include <iostream>
# include <memory>
# include <limits>
# include <BidirectionalIterator.hpp>

namespace ft
{
	template <class Key, class Value, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<Key, Value> > >
	class map
	{
		class node
		{
			public:
				node(node *parent = NULL, node *left = NULL, node *right = NULL, const T& value = T()) : parent(parent), left(left), right(right), content(value) {}
				node(const node& other) : parent(other.parent), left(other.left), right(other.right), content(other.content) {}
				node& operator = (const node& other)
				{
					if (this != &other)
					{
						this->parent = other.parent;
						this->left = other.left;
						this->right = other.right;
						this->content = other.content;
					}
					return (*this);
				}
				~node() {}
				node	*parent;
				node	*left;
				node	*right;
				T		content;
		};
		public:
			typedef std::pair<Key, Value>														value_type;
			typedef BidirectionalIterator<node, value_type*, value_type&>						iterator;
			typedef BidirectionalIterator<node, const value_type*, const value_type&>			const_iterator;
			typedef ReverseBidirectionalIterator<node, value_type*, value_type&>				reverse_iterator;
			typedef ReverseBidirectionalIterator<node, const value_type*, const value_type&>	const_reverse_iterator;

			//CONSTRUCTORS

			explicit map(const Compare& compare = Compare(), const Alloc& alloc = Alloc()) : root(new node()), tail(new node()), len(0), compare(compare), allocator(alloc) {}
			map(const map& other) : root(new node(other.root)), tail(new node(other.tail)), len(other.len), compare(other.compare), allocator(other.allocator)
			{
				//copy construct
			}
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Alloc& alloc = Alloc())
			{
				//construct tree from first<->last
			}
			map& operator = (const map& other)
			{
				if (this != &other)
				{
					//deepcopy the entire container
				}
				return (*this);
			}
			~map()
			{
				//delete entire container
				delete this->root;
				delete this->tail;
			}

			//ITERATORS

			iterator	begin()
			{
				return (iterator(root));
			}
			const_iterator begin() const
			{
				return (const_iterator(root));
			}
			iterator	end()
			{
				return (iterator(tail));
			}
			const_iterator end() const
			{
				return (const_iterator(tail));
			}
			reverse_iterator rbegin()
			{
				return (reverse_iterator(tail));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(tail));
			}
			reverse_iterator rend()
			{
				return (reverse_iterator(root));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(root));
			}

			//CAPACITY

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

			//ELEMENT ACCESS

			Value&	operator [] (const Key& key)
			{
				//return Value at Key
			}

			//MODIFIERS

			std::pair<iterator,bool> insert (const value_type& keyval)
			{
				//insert the given keyval.second at keyval.first in the map

				//return true if it was inserted else false
				//return iterator to the newly inserted element else the element that was already there
			}
			iterator insert (iterator position, const value_type& val)
			{
				//insert in list, with position as hint
				//return iterator to the newly inserted element else the element that was already there
			}
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				//insert first<->last into map
			}
			void	erase(iterator position)
			{
				//delete element at position from map
			}
			size_t	erase(const Key& key)
			{
				//delete element at 'key' from map
				//return how many are deleted (0 or 1);
			}
			void	erase(iterator first, iterator last)
			{
				//delete all the elements from first to last (not deleting last))
			}

			void	swap(map& other)
			{
				ft::swap(this->allocator, other.allocator);
				ft::swap(this->root, other.root);
				ft::swap(this->tail, other.tail);
				ft::swap(this->len, other.len);
				ft::swap(this->compare, other.compare);
			}

			void	clear()
			{
				//delete all the elements in the map
			}

			//OBSERVERS

			key_compare key_comp() const
			{
				return (compare);
			}

			value_compare value_comp() const
			{
				//HOOFDPIJN
			}

			//OPERATIONS

			iterator find (const key_type& k)
			{
				//return iterator to element matching key k
			}
			const_iterator find (const key_type& k) const
			{
				//same dealio, but return a const iterator
			}

			size_t count (const key_type& k) const
			{
				//return how many elements match the key k (0 or 1);
			}

			iterator lower_bound (const key_type& k)
			{
				//return iterator to first element that would be lower than k
			}
			const_iterator lower_bound (const key_type& k) const
			{
				//#same
			}

			iterator upper_bound (const key_type& k)
			{
				//return iterator to first element that would be lower than k
			}
			const_iterator upper_bound (const key_type& k) const
			{
				//#same
			}

			std::pair<iterator,iterator> equal_range (const key_type& k)
			{
				//useless function
				//only returns an iterator to k and one past
			}
			std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				//same bullshit
			}

		private:
			node	*root;
			node	*tail;
			size_t	len;
			Compare	compare;
			Alloc	allocator;
	};
};

#endif
