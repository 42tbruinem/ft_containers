/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/16 15:13:49 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/22 20:24:09 by tbruinem      ########   odam.nl         */
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
					while (iter->parent && iter->parent->right == iter) //might be fucked??
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
					while (iter->parent && iter->parent->left == iter) //might be fucked?
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

void	print_node_info(ft::nodebase *node, ft::nodebase *root)
{
	std::cout << "Root ? " << ((root == node) ? "True" : "False") << std::endl;
	std::cout << "Parent ? " << ((node->parent) ? "True " : "False ");
	if (node->parent)
		std::cout << (void *)node->parent;
	std::cout << std::endl;
	std::cout << "Left ? " << ((node->left) ? "True " : "False ");
	if (node->left)
		std::cout << (void *)node->left;
	std::cout << std::endl;
	std::cout << "Right ? " << ((node->right) ? "True " : "False ");
	if (node->right)
		std::cout << (void *)node->right;
	std::cout << std::endl;
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
			typename Node::base *getptr() { return this->ptr; }
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
			ReverseIterator(typename Node::base *ptr) : Iterator<Node, Value>(ptr) {}
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

			void	info(void)
			{
				std::cout << "Root: " << this->root << std::endl;
				std::cout << "Len: " << this->len << std::endl;
				std::cout << "First:" << std::endl;
				print_node_info(&this->first, this->root);
				std::cout << "Last:" << std::endl;
				print_node_info(&this->last, this->root);
			}

			explicit map(const Compare& compare = Compare(), const Alloc& alloc = Alloc()) : root(NULL), first(nodebase(&this->last)), last(nodebase(&this->first)), len(0), compare(compare), allocator(alloc)
			{
				std::cout << "Address of first: " << (void *)&this->first << std::endl;
				std::cout << "Address of last: " << (void *)&this->last << std::endl;
			}
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
				this->clear();
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
				erase(this->begin(), this->end());
			}

			std::pair<iterator,bool> insert (const value_type& value)
			{
				iterator it = find(value.first);
				if (it != this->end())
					return (std::pair<iterator, bool>(it, false));
				typename mapnode::base **iter = &this->root;
				typename mapnode::base *parent = NULL;
				while (*iter && *iter != &this->first && *iter != &this->last)
				{
					parent = (*iter);
					if (value.first > static_cast<mapnode *>((*iter))->getval().first)
						iter = &(*iter)->right;
					else if (value.first < static_cast<mapnode *>((*iter))->getval().first)
						iter = &(*iter)->left;
				}
				*iter = new mapnode(value.first, value.second, parent, NULL, NULL);
				std::cout << "new! " << (void *)*iter << " | Key: " << value.first << " | Value: " << value.second << std::endl;
				if (this->last.parent == &this->first || static_cast<mapnode *>(this->last.parent)->getval().first < value.first)
				{
					(*iter)->right = &this->last;
					this->last.parent = (*iter);
				}
				if (this->first.parent == &this->last || static_cast<mapnode *>(this->first.parent)->getval().first > value.first)
				{
					(*iter)->left = &this->first;
					this->first.parent = (*iter);
				}
				this->len++;
				return (std::pair<iterator, bool>(iterator(*iter), true));
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				for (;first != last; first++)
					insert(*first);
			}

			void	erase(iterator position)
			{
				//fix up first/last
				if (position.getptr()->right == &this->last) //highest element
				{
					this->last.parent = this->last.parent->prev();
					if (!this->last.parent)
						this->last.parent = &this->first;
					position.getptr()->right = NULL;
				}
				if (position.getptr()->left == &this->first) //lowest element
				{
					this->first.parent = this->first.parent->next();
					if (!this->first.parent)
						this->first.parent = &this->last;
					position.getptr()->left = NULL;
				}

				std::cout << "in erase - " << position->first << " : " << position->second << std::endl;
				print_node_info(position.getptr(), this->root);
				mapnodebase *node = position.getptr();
				if (node->left && node->right) //two children
				{
					mapnodebase *replacement = node->left;
					while (replacement->right)
						replacement = replacement->right;
					connect(node, replacement);
				}
				else if (node->left) //one child
					connect(node, node->left);
				else if (node->right) //one child
					connect(node, node->right);
				else if (node->parent && node->parent->right == node) //no children
					node->parent->right = NULL;
				else if (node->parent && node->parent->left == node) //no children
					node->parent->left = NULL;
				delete static_cast<mapnode *>(node);
				this->len--; //what if an invalid iterator is given??
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
				{
					erase(first++);
				}
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
			void	connect(mapnodebase *oldnode, mapnodebase* newnode)
			{
				bool	left_child = (oldnode->parent && oldnode->parent->left == oldnode);

				//set the parent of old to new
				if (!oldnode->parent)
					this->root = newnode;
				else if (left_child)
					oldnode->parent->left = newnode;
				else
					oldnode->parent->right = newnode;

				//turn the spot of new to NULL
				if (newnode->parent && newnode->parent->left == newnode)
					newnode->parent->left = NULL;
				if (newnode->parent && newnode->parent->right == newnode)
					newnode->parent->right = NULL;

				//set new's parent to old's parent
				newnode->parent = oldnode->parent;

				//if there are left and/or right children
				if (oldnode->left && oldnode->left != newnode)
				{
					newnode->left = oldnode->left;
					newnode->left->parent = newnode;
				}
				if (oldnode->right && oldnode->right != newnode)
				{
					newnode->right = oldnode->right;
					newnode->right->parent = newnode;
				}
			}
			mapnodebase	*root;
			mapnodebase	first;
			mapnodebase	last;
			size_t	len;
			Compare	compare;
			Alloc	allocator;
	};
};

#endif
