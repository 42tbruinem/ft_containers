/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/16 15:13:49 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/18 17:09:08 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "GenericFunctions.hpp"
# include <stdio.h>
# include <iostream>
# include <memory>
# include <limits>
# include <utility>
# include <unistd.h>

namespace ft
{
	class nodebase
	{
		public:
			nodebase(nodebase *parent = NULL, nodebase *left = NULL, nodebase *right = NULL) : parent(parent), left(left), right(right) {}
			nodebase(const nodebase& other) : parent(other.parent), left(other.left), right(other.right) {}
			nodebase& operator = (const nodebase& other)
			{
				if (this != &other)
				{
					this->parent = other.parent;
					this->left = other.left;
					this->right = other.right;
				}
				return (*this);
			}
			~nodebase() {}
			nodebase	*next()
			{
				nodebase *iter = this;
				if (iter->right)
				{
					iter = iter->right;
					while (iter->left)
						iter = iter->left;
				}
				else
				{
					while (iter->parent->right == iter)
						iter = iter->parent;
					iter = iter->parent;
				}
				return (iter);
			}
			nodebase	*prev()
			{
				nodebase *iter = this;
				if (iter->left)
				{
					iter = iter->left;
					while (iter->right)
						iter = iter->right;
				}
				else
				{
					while (iter->parent->left == iter)
						iter = iter->parent;
					iter = iter->parent;
				}
				return (iter);
			}
		public:
			nodebase	*parent;
			nodebase	*left;
			nodebase	*right;
	};

	template <class Key, class T>
	class node : public nodebase
	{
		typedef std::pair<Key, T>	Value;
		public:
			typedef nodebase			base;
			node(const Key& key, const T& mapped = T(), nodebase *parent = NULL, nodebase *left = NULL, nodebase *right = NULL) : value(key, mapped), nodebase(parent, left, right) {}
			node(const node& other) : value(other.value), nodebase(other.parent, other.left, other.right) {}
			node& operator = (const node& other)
			{
				if (this != &other)
				{
					this->key = other.key;
					this->value = other.value;
					this->parent = other.parent;
					this->left = other.left;
					this->right = other.right;
				}
				return (*this);
			}
			Value&	getval()
			{
//				std::cout << "Key: " << this->value.first << " | " << "Val: " << this->value.second << std::endl;
//				sleep(1);
				return (this->value);
			}
			~node() {}
		private:
			Value	value;
	};
}

namespace ft
{
	template <class Node, class Value>
	class Iterator
	{
		public:
			Iterator(typename Node::base *ptr = NULL) : ptr(ptr) {}
			Iterator(const Iterator& other) : ptr(other.ptr) {}
			Iterator&	operator = (const Iterator& other)
			{
				if (this != &other)
				{
					this->ptr = other.ptr;
				}
				return (*this);
			}
			~Iterator() {}
			bool	operator == (const Iterator& other)
			{
				return (this->ptr == other.ptr);
			}
			bool	operator != (const Iterator& other)
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
			Value*	operator -> ()
			{
				return (&static_cast<Node *>(this->ptr)->getval());
			}
			Value&	operator * ()
			{
				return (static_cast<Node *>(this->ptr)->getval());
			}
		private:
			typename Node::base *ptr;
	};
}

namespace ft
{
	template <class Node, class Value>
	class ReverseIterator : public Iterator<Node, Value>
	{
		public:
			ReverseIterator() : Iterator<Node, Value>() {}
			ReverseIterator(const ReverseIterator& other) : Iterator<Node, Value>(other) {}
			ReverseIterator& operator = (const ReverseIterator& other) { return(Iterator<Node, Value>::operator=(other)); }
			~ReverseIterator() {}
			ReverseIterator&	operator ++ () { return (Iterator<Node, Value>::operator--()); }
			ReverseIterator		operator ++ (int) { return (Iterator<Node, Value>::operator--(1)); }
			ReverseIterator&	operator -- () { return (Iterator<Node, Value>::operator++()); }
			ReverseIterator		operator -- (int) { return (Iterator<Node, Value>::operator++(1)); }
	};
}

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<Key, T> > >
	class map
	{
		public:
			typedef std::pair<Key, T>															value_type;
			typedef Key																			key_type;
			typedef Compare																		key_compare;
			typedef T																			mapped_type;
			typedef value_type&																	reference;
			typedef value_type*																	pointer;
			typedef node<Key, T>																mapnode;
			typedef nodebase																	mapnodebase;

		public:
			typedef Iterator<mapnode, value_type>												iterator;
			typedef Iterator<mapnode, const value_type>											const_iterator;
			typedef ReverseIterator<mapnode, value_type>										reverse_iterator;
			typedef ReverseIterator<mapnode, const value_type>									const_reverse_iterator;

			//CONSTRUCTORS

			explicit map(const Compare& compare = Compare(), const Alloc& alloc = Alloc()) : root(NULL), first(nodebase(&this->last)), last(nodebase(&this->first)), len(0), compare(compare), allocator(alloc) {}
			map(const map& other) : root(NULL), first(nodebase(&this->last)), last(nodebase(&this->first)), len(other.len), compare(other.compare), allocator(other.allocator) {}

			// template <class InputIterator>
			// map(InputIterator first, InputIterator last, const Compare& comp = Compare(), this->first(nodebase(&this->last)), last(nodebase(&this->first)), const Alloc& alloc = Alloc())
			// {
			// 	//construct tree from first<->last
			// }

			map& operator = (const map& other)
			{
				if (this != &other)
				{
					
				}
				return (*this);
			}

			~map()
			{
				//delete entire container
			}

			//ITERATORS

			iterator	begin()
			{
				return (iterator(this->first.parent));
			}

			const_iterator begin() const
			{
				return (const_iterator(this->first.parent));
			}

			iterator	end()
			{
				return (iterator(&this->last));
			}

			const_iterator end() const
			{
				return (const_iterator(&this->last));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->last.parent));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->last.parent));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(&this->first));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(&this->first));
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

			T&	operator [] (const Key& key)
			{
				iterator it = find(key);
				if (it == this->end())
					it = insert(value_type(key, T())).first;
				return (it->second);
			}

			//MODIFIERS

			void	clear()
			{
//				for (iterator it = this->begin(); it != this->end(); it++)
					
			}

			std::pair<iterator,bool> insert (const value_type& value)
			{
				iterator it = find(value.first);
//				std::cout << "found == end() ? " << ((it == this->end()) ? "True" : "False") << std::endl;
				if (it != this->end())
					return (std::pair<iterator, bool>(it, false));
				//move down the tree binary-search style and when an empty node is encountered, add a new node there
				typename mapnode::base **iter = &this->root;
				typename mapnode::base *parent = NULL;

				while (*iter && *iter != &this->first && *iter != &this->last)
				{
//					std::cout << "here?" << std::endl;
					parent = (*iter);
					if (value.first > static_cast<mapnode *>((*iter))->getval().first)
						iter = &(*iter)->right;
					else if (value.first < static_cast<mapnode *>((*iter))->getval().first)
						iter = &(*iter)->left;
				}
//				std::cout << "not stuck here" << std::endl;
				*iter = new mapnode(value.first, value.second, parent, NULL, NULL);
				if (this->last.parent == &this->first || static_cast<mapnode *>(this->last.parent)->getval().first < value.first)
				{
	//				std::cout << "updated highest key is " << key << std::endl;
					(*iter)->right = &this->last;
					this->last.parent = (*iter);
				}
				if (this->first.parent == &this->last || static_cast<mapnode *>(this->first.parent)->getval().first > value.first)
				{
	//				std::cout << "updated lowest key is " << key << std::endl;
					(*iter)->left = &this->first;
					this->first.parent = (*iter);
				}
//				std::cout << "Key: " << value.first << " | Val: " << value.second << " | left: " << (void *)(*iter)->left << " | right: " << (void *)(*iter)->right << " | parent: " << (void *)(*iter)->parent << std::endl;
	//			std::cout << key << " : " << val << " : " << (void *)(*iter) << std::endl;
				return (std::pair<iterator, bool>(iterator(*iter), true));
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

			//OBSERVERS

			key_compare key_comp() const
			{
				return (compare);
			}

			// value_compare value_comp() const
			// {
			// 	//HOOFDPIJN
			// }

			//OPERATIONS

			iterator find (const key_type& k)
			{
				if (!this->root)
					return (this->end());
				typename mapnode::base *iter = this->root;
				iterator it = iterator(this->root);
				while (iter && iter != &this->first && iter != &this->last)
				{
					if (static_cast<mapnode *>(iter)->getval().first > k)
						iter = iter->left;
					else if (static_cast<mapnode *>(iter)->getval().first < k)
						iter = iter->right;
					else
						return (iterator(iter));
				}
				return (this->end());
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
			mapnodebase	*root;
			mapnodebase	first;
			mapnodebase	last;
			size_t	len;
			Compare	compare;
			Alloc	allocator;
	};
};

#endif
