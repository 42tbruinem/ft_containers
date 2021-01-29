/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Map.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/16 15:13:49 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/29 13:56:21 by tbruinem      ########   odam.nl         */
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
# include <traits.hpp>
# include <iterator>

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
			nodebase	**link_to_parent()
			{
				nodebase *parent = this->parent;
				if (!parent) //only happens if the node is root
					return (NULL);
				if (parent->left == this)
					return (&parent->left);
				if (parent->right == this)
					return (&parent->right);
				return (NULL);
			}
		public:
			nodebase	*parent;
			nodebase	*left;
			nodebase	*right;
	};

	template <class Value>
	class node : public nodebase
	{
		public:
			typedef nodebase			base;
			node(const Value& value, nodebase *parent = NULL, nodebase *left = NULL, nodebase *right = NULL) : nodebase(parent, left, right), value(value) {}
			node(const node& other) : nodebase(other.parent, other.left, other.right), value(other.value) {}
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
				return (this->value);
			}
			~node() {}
		private:
			Value	value;
	};
}

namespace ft
{
	template <class Value, class Category = ft::bidirectional_iterator_tag>
	class Iterator
	{
		private:
			typedef ft::nodebase				nodebase;
			typedef ft::node<Value>				node;
		public:
			typedef Category					iterator_category;
			typedef Value&						reference;
			typedef Value*						pointer;

			Iterator(const nodebase *ptr = NULL) : ptr(const_cast<nodebase *>(ptr)) {}
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
			Value*	operator -> ()
			{
				return (&static_cast<node *>(this->ptr)->getval());
			}
			Value&	operator * ()
			{
				return (static_cast<node *>(this->ptr)->getval());
			}
			nodebase *getptr() { return this->ptr; }
		private:
			nodebase *ptr;
	};
}

namespace ft
{
	template <class Value>
	class ConstIterator : public Iterator<Value>
	{
		private:
			typedef Iterator<Value>								iterator;
		public:
			typedef typename iterator::iterator_category		iterator_category;
			typedef const Value&								reference;
			typedef const Value*								pointer;

			ConstIterator(const ft::nodebase *ptr = NULL) : iterator(ptr) {}
			ConstIterator(const iterator& other) : iterator(other) {}
			const Value& operator * () { return iterator::operator*(); }
			const Value* operator -> () { return iterator::operator->(); }
	};
}

namespace ft
{
	template <class Iterator>
	class ReverseIterator
	{
		Iterator	iterator;
		public:
			typedef typename Iterator::iterator_category			iterator_category;
			typedef typename Iterator::reference					reference;
			typedef typename Iterator::pointer						pointer;

			ReverseIterator(ft::nodebase *ptr) : iterator(ptr) {}
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
				return (*iterator);
			}
			pointer				operator->()
			{
				return (&(operator*));
			}
	};
}

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<Key, T> > >
	class map
	{
		public:
			typedef std::pair<const Key, T>									value_type;
			typedef Key														key_type;
			typedef Compare													key_compare;
			typedef T														mapped_type;
			typedef value_type&												reference;
			typedef value_type*												pointer;
			typedef ft::node<value_type>									mapnode;
			typedef ft::nodebase											mapnodebase;
			typedef Iterator<value_type>									iterator;
			typedef ConstIterator<value_type>								const_iterator;
			typedef ReverseIterator<iterator>								reverse_iterator;
			typedef ReverseIterator<const_iterator>							const_reverse_iterator;

			class value_compare : ft::binary_function<value_type,value_type,bool>
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

			//CONSTRUCTORS

			explicit map(const Compare& compare = Compare(), const Alloc& alloc = Alloc()) : root(NULL), first(new nodebase()), last(new nodebase()), len(0), compare(compare), allocator(alloc)
			{
				this->first->parent = this->last;
				this->last->parent = this->first;
			}
			map(const map& other) : root(NULL), first(new nodebase()), last(new nodebase()), len(0), compare(other.compare), allocator(other.allocator)
			{
				this->first->parent = this->last;
				this->last->parent = this->first;
				*this = other;
			}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const Compare& compare = Compare(), const Alloc& alloc = Alloc(),
			typename enable_if<is_iterator<typename InputIterator::iterator_category>::result, InputIterator>::type* = NULL) :
				root(NULL), first(new nodebase()), last(new nodebase()), len(0), compare(compare), allocator(alloc)
			{
				this->first->parent = this->last;
				this->last->parent = this->first;
				this->insert(first, last);
			}

			map& operator = (const map& other)
			{
				if (this != &other)
				{
					this->clear();
					this->insert(other.begin(), other.end());
				}
				return (*this);
			}

			void	info()
			{
				std::cout << "---------------------" << "INFO" << "------------------------" << std::endl;
				std::cout << "----Root" << std::endl;
				print_node_info(root);
				std::cout << "----First" << std::endl;
				print_node_info(this->first);
				std::cout << "----Last" << std::endl;
				print_node_info(this->last);
				std::cout << "-------------------------------------------------" << std::endl;
			}

			~map()
			{
				this->clear();
				delete this->first;
				delete this->last;
			}

			//ITERATORS

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
				return (const_iterator(const_cast<mapnodebase*>(this->last)));
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
				mapnodebase **iter = &this->root;
				mapnodebase *parent = NULL;
				while (*iter && *iter != this->first && *iter != this->last)
				{
					parent = (*iter);
					if (value.first > static_cast<mapnode *>(*iter)->getval().first)
						iter = &(*iter)->right;
					else if (value.first < static_cast<mapnode *>(*iter)->getval().first)
						iter = &(*iter)->left;
				}
				*iter = new mapnode(value, parent, NULL, NULL);
//				std::cout << "new! " << (void *)*iter << " | Key: " << value.first << " | Value: " << value.second << std::endl;
				if (this->last->parent == this->first || static_cast<mapnode *>(this->last->parent)->getval().first < value.first)
					connect_parent_child(*iter, &(*iter)->right, this->last);
				if (this->first->parent == this->last || static_cast<mapnode *>(this->first->parent)->getval().first > value.first)
					connect_parent_child(*iter, &(*iter)->left, this->first);
				this->len++;
				return (std::pair<iterator, bool>(iterator(*iter), true));
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				for (;first != last; first++)
					insert(*first);
			}
			void	erase(iterator it)
			{
				mapnodebase *node = it.getptr();
				if (!node)
					return ;

//				std::cout << "Before: " << std::endl;
//				print_node_info(node);
				//deal with first/last
				mapnodebase *lowest = NULL;
				mapnodebase *highest = NULL;
				if (node->left == this->first)
				{
					lowest = node->next();
					connect_parent_child(lowest, &lowest->left, this->first);
				}
				if (node->right == this->last)
				{
					highest = node->prev();
					connect_parent_child(highest, &highest->right, this->last);
				}
				if (lowest)
					node->left = NULL;
				if (highest)
					node->right = NULL;

				//get replacement if needed
				mapnodebase *replacement = NULL;
				if (node->right && node->left)
				{
					replacement = node->left;
					while (replacement->right)
						replacement = replacement->right;
					if (replacement != node->left)
					{
						replacement->parent->right = replacement->left;
						if (replacement->left && replacement->left != this->first)
						{
							replacement->left->parent = replacement->parent;
							replacement->left = NULL;
						}
					}
				}
				else if (node->right)
					replacement = node->right;
				else if (node->left)
					replacement = node->left;

				//replace the old parent's corresponding left/right child with replacement
				mapnodebase **replacementparent_link = (replacement) ? replacement->link_to_parent() : NULL;
				if (node->parent && node->parent->left == node) //is not root and is left child
					node->parent->left = replacement;
				else if (node->parent && node->parent->right == node) //is not root and is right child
					node->parent->right = replacement;
				else if (!node->parent)//is root
					this->root = replacement;
				if (replacement) //connect the replacement
				{
					if (replacementparent_link)
						*replacementparent_link = NULL;
					if (!replacement->left) //dont override existing link to child
						connect_parent_child(replacement, &replacement->left, node->left);
					if (!replacement->right) //dont override existing link to child
						connect_parent_child(replacement, &replacement->right, node->right);
					replacement->parent = node->parent;
				}
//				std::cout << "After: " << std::endl;
//				print_node_info(replacement);
				delete static_cast<mapnode *>(node);
				this->len--;
			}

			size_t	erase(const Key& key)
			{
				iterator it = find(key);
				if (it == this->end())
					return (0);
//				std::cout << "not stuck in find" << std::endl;
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

			//OBSERVERS

			key_compare key_comp() const
			{
				return (compare);
			}

			value_compare value_comp() const
			{
				return (value_compare(this->compare));
			}

			//OPERATIONS

			iterator find (const key_type& k)
			{
				if (!this->root)
					return (this->end());
				typename mapnode::base *iter = this->root;
				iterator it = iterator(this->root);
				while (iter && iter != this->first && iter != this->last)
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
//				std::cout << "CONST FIND" << std::endl;
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
				{
					it = this->begin();
					while (1)
					{
						iterator next = ++(iterator(it));
						if (it == this->end() || it->first >= k)
							break ;
						++it;
					}
				}
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
				{
					while (1)
					{
						iterator prev = --(iterator(it));
						if (it == this->begin() || it->first <= k)
							break ;
						--it;
					}
				}
				else
					++it;
				return (it);
			}

			const_iterator upper_bound (const key_type& k) const
			{
				return (const_iterator(const_cast<map *>(this)->upper_bound(k)));
			}

			std::pair<iterator,iterator> equal_range (const key_type& k)
			{
				iterator first = this->lower_bound(k);
				iterator last = this->upper_bound(k);

				if (first != this->end())
					++first;
				return (std::pair<iterator, iterator>(first, last));
			}

			std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				std::pair<iterator, iterator>	nonconst = const_cast<map *>(this)->equal_range(k);
				return (std::pair<const_iterator, const_iterator>(const_iterator(nonconst.first), const_iterator(nonconst.second)));
			}

		private:
			//oldnode = node, newnode = replacement
			void	connect(mapnodebase *oldnode, mapnodebase* newnode)
			{
				//CONNECT TO PARENT
				if (this->root == oldnode) //this is the root
				{
					this->root = newnode;
					this->root->parent = NULL;
				}
				else if (oldnode->parent->left == oldnode)
				{
					oldnode->parent->left = newnode;
					if (newnode->parent)
						newnode->parent->left = NULL;
					newnode->parent = oldnode->parent;
				}
				else if (oldnode->parent->right == oldnode)
				{
					oldnode->parent->right = newnode;
					if (newnode->parent)
						newnode->parent->right = NULL;
					newnode->parent = oldnode->parent;
				}

				//if there are left and/or right children
				if (oldnode->left && oldnode->left != newnode)
				{
//					std::cout << "Connecting oldnode->left to newnode and vice versa" << std::endl;
					newnode->left = oldnode->left;
					newnode->left->parent = newnode;
				}
				if (oldnode->right && oldnode->right != newnode)
				{
//					std::cout << "Connecting oldnode->right to newnode and vice versa" << std::endl;
					newnode->right = oldnode->right;
					newnode->right->parent = newnode;
				}
			}
			void		print_keyval(const std::string& title, mapnodebase *node, bool parent)
			{
				std::cout << "---- " << title << " ----" << std::endl;
				if (!node)
					std::cout << ((parent) ? "Root" : "NULL(EMPTY)") << std::endl;
				else if (node == this->first)
					std::cout << "First" << std::endl;
				else if (node == this->last)
					std::cout << "Last" << std::endl;
				else
				{
					value_type keyval = static_cast<mapnode*>(node)->getval();
					std::cout << "Key: " << keyval.first << " : Val: " << keyval.second << std::endl;
				}
			}
			void		connect_parent_child(mapnodebase *parent, mapnodebase **parent_childptr, mapnodebase *child)
			{
				if (child)
					child->parent = parent;
				if ((child == this->first || child == this->last) && (parent == this->first || parent == this->last))
					return ;
				if (parent_childptr)
					*parent_childptr = child;
			}
			void		print_node_info(mapnodebase *node)
			{
				std::cout << "-------------------" << std::endl;
				print_keyval("Node", node, false);
				if (!node)
					return ;
				print_keyval("Parent", node->parent, true);
				print_keyval("Left", node->left, false);
				print_keyval("Right", node->right, false);
				std::cout << "-------------------" << std::endl;
			}
			mapnodebase	*root;
			mapnodebase	*first;
			mapnodebase	*last;
			size_t	len;
			Compare	compare;
			Alloc	allocator;
	};
}

#endif
