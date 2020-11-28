/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   List.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 15:50:30 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/11/28 13:31:50 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <limits>
# include <traits.hpp>
# include "IteratorFunctions.hpp"
# include <list>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class	list
	{
		template <class T>
		class node
		{
			public:
				node	*prev;
				node	*next;
				T		element;
				node(T element, node *prev = NULL, node *next = NULL) : element(element), prev(prev), next(next) {}
		};
		public:
			typedef T*										pointer;
			typedef T&										reference;
			typedef const T*								const_pointer;
			typedef const T& 								const_reference;
			typedef BidirectionalIterator<node, T*, T&>		iterator;

			//CONSTRUCTORS / DESTRUCTOR

			list(const Alloc& alloc = Alloc()) : len(0), begin(NULL), end(NULL), alloc(alloc) {}
			list(size_t n, const T& val = T(), const Alloc& alloc = Alloc())
			{
				for (size_t i = 0; i < n; i++)
					newNode(val, i);
			}
			template<class InputIterator>
			list(InputIterator first, InputIterator last,
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::result, InputIterator>::type* = NULL,
				const Alloc& alloc = Alloc()) : alloc(alloc)
			{
				size_t len = ft::distance(first, last);

				for (; first != last; first++)
					newNode(*first);
			}
			list(const list& other)
			{
				for (list<T>::iterator it = other.begin(); it != other.end(); it++)
					newNode(*it);
			}
			~list()
			{
				clear();
			}
			list& operator = (const list& other)
			{
				clear();
				for (list<T>::iterator it = other.begin(); it != other.end(); it++)
					newNode(*it);
			}

			// ITERATORS

			iterator begin()
			{
				return (iterator(this->begin));
			}
			const_iterator begin() const
			{
				return (const_iterator(this->begin));
			}
			iterator end()
			{
				return (iterator(this->end));
			}
			const_iterator end() const
			{
				return (const_iterator(this->end));
			}

			//CAPACITY

			bool empty() const
			{
				return (this->len);
			}
			size_t size() const
			{
				return (this->len);
			}
			size_t max_size() const
			{
				return (alloc.max_size());
			}

			//ELEMENT ACCESS

			T& front()
			{
				return (this->begin->element);
			}
			const T& front() const
			{
				return (this->begin->element);
			}
			T& back()
			{
				return (this->end->element);
			}
			const T& back() const
			{
				return (this->end->element);
			}

			//MODIFIERS

			template class <InputIterator>
			void assign(InputIterator first, InputIterator last,
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::result, InputIterator>::type* = NULL)
			{
				clear();
				for (; first != last; first++)
					newNode(*first);
			}
			void assign(size_t n, const T& val)
			{
				clear();
				for (size_t i = 0; i < n; i++)
					newNode(val);
			}
			void push_front(const T& val)
			{
				newNode(val, 0);
			}
			void pop_front()
			{
				delNode(0);
			}
			void push_back(const T& val)
			{
				newNode(val);
			}
			void pop_back()
			{
				delNode();
			}
			iterator insert(iterator position, const T& val)
			{
				size_t pos = ft::distance(this->begin(), position);
				node *Node = newNode(val, pos);
				return (iterator(Node));
			}
			void insert(iterator position, size_t n, const T& val)
			{
				size_t pos = ft::distance(this->begin(), position);

				if (pos + n >= std::numeric_limits<size_t>::max()) //protection I guess
					return ;
				for (size_t i = 0; i < n; i++)
					newNode(val, pos + i);
			}
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::result, InputIterator>::type* = NULL)
			{
				size_t pos = ft::distance(this->begin(), position);

				for (; first != last; first++)
					newNode(*first, pos++);
			}
			iterator erase(iterator position)
			{
				size_t pos = ft::distance(this->begin(), position);

				delNode(pos);
			}
			iterator erase(iterator first, iterator last)
			{
				size_t pos = ft::distance(this->begin(), first);

				for (; first != last; first++)
					delNode(pos++);
			}
			void swap(const list& other)
			{
				ft::swap(this->begin, x.begin);
				ft::swap(this->len, x.len);
				ft::swap(this->end, x.end);
			}
			void resize(size_t n, T val = T())
			{
				if (this->len == n)
					return ;
				if (this->len > n)
				{
					for (size_t i = this->len; i < n; i++)
						newNode(val);
				}
				else
				{
					size_t len = this->len;
					for (; n < len; n++)
						delNode();
				}
			}
			void clear()
			{
				size_t len = this->len;

				for (size_t i = 0; i < len; i++)
					delNode();
			}

			//OPERATIONS

			void splice (iterator position, list& x)
			{
				if (&x == this)
					return ;
				node *Node = position.ptr;

				transfer(Node->prev, Node, x.begin, x.end);

				this->len += x.len;
				x.len = 0;
				x.begin = NULL;
				x.end = NULL;
			}
			void splice (iterator position, list& x, iterator i)
			{
				if (&x == this)
					return ;
				node *Node = position.ptr;
				node *otherNode = i.ptr;

				transfer(Node->prev, Node, otherNode, otherNode);

				if (x.len)
					x.len -= 1;
			}
			void splice (iterator position, list& x, iterator first, iterator last)
			{
				if (&x == this)
					return ;
				size_t len = ft::distance(first, last);

				transfer(position.ptr->prev, position.ptr, first.ptr, last.ptr);

				x.len -= (len > x.len) ? x.len : len;
			}
			void remove (const T& val)
			{
				node *iter = this->begin;
				for (size_t i = 0; iter;)
				{
					iter = iter->next;
					if (iter->element == val)
						delNode(i);
					else
						i++;
				}
			}
			template <class Predicate>
			void remove_if (Predicate pred)
			{
				node *iter = this->begin;
				for (size_t i = 0; iter;)
				{
					iter = iter->next;
					if (pred(iter->element))
						delNode(i);
					else
						i++;
				}
			}
			void unique()
			{
				node *iter = this->begin;
				node *prev = NULL;
				for (size_t i = 0; iter;)
				{
					if (prev && prev->element == iter->element)
					{
						iter = iter->next;
						delNode(i);
					}
					else
					{
						prev = iter;
						iter = iter->next;
						i++;
					}
				}
			}
			template <class BinaryPredicate>
			void unique(BinaryPredicate binary_pred)
			{
				node *iter = this->begin;
				node *prev = NULL;
				for (size_t i = 0; iter;)
				{
					if (prev && binary_pred(prev->element, iter->element))
					{
						iter = iter->next;
						delNode(i);
					}
					else
					{
						prev = iter;
						iter = iter->next;
						i++;
					}
				}
			}
			void merge(list& x)
			{
				if (&x == this)
					return ;
				node *iter = this->begin;

				for (size_t i = 0; iter;)
			}
		private:
			void	transfer(node *prev, node *pos, node *otherBegin, node *otherEnd)
			{
				if (prev)
					prev->next = otherBegin;
				if (pos)
					pos->prev = otherEnd;
				if (otherBegin)
				{
					if (otherBegin->prev && otherEnd)
						otherBegin->prev->next = otherEnd->next;
					else if (otherBegin->prev)
						otherBegin->prev->next = NULL;
					otherBegin->prev = prev;
				}
				if (otherEnd)
				{
					if (otherEnd->next && otherBegin)
						otherEnd->next->prev = otherBegin->prev;
					else if (otherEnd->next)
						otherEnd->next->prev = NULL;
					otherEnd->next = pos;
				}
			}
			void	delNode(size_t pos = std::numeric_limits<size_t>::max())
			{
				node *ptr = this->begin;

				if (!ptr)
					return ;
				if (pos == 0)
				{
					ptr = this->begin;
					this->begin = this->begin->next;
					if (this->begin)
						this->begin->prev = NULL;
					if (this->len == 1)
						this->end = this->begin;
					delete ptr;
				}
				else if (pos >= this->len)
				{
					ptr = this->end;
					this->end = this->end->prev;
					if (this->end)
						this->end->next = NULL;
					if (this->len == 1)
						this->begin = this->end;
					delete ptr;
				}
				else
				{
					for (size_t i = 0; i < pos && ptr; i++)
						ptr = ptr->next;
					if (!ptr)
						return ; //should never happen
					ptr->prev->next = ptr->next;
					ptr->next->prev = ptr->prev;
					delete ptr;
				}
				--this->len;
			}
			node	*newNode(T value, size_t pos = std::numeric_limits<size_t>::max())
			{
				node *ptr = this->begin;
				//if push_back()
				if (this->len && pos >= this->len)
				{
					this->len++;
					this->end->next = new node(T, this->end, NULL);
					this->end = this->end->next;
					return (this->end);
				}
				else //index
					for (size_t i = 0; i < pos && ptr != NULL; i++)
						ptr = ptr->next;
				this->len++;
				//if start of the list
				if (!ptr)
				{
					this->begin = new node(T);
					this->end = this->begin;
					return (this->begin);
				}
				//if index 0
				if (ptr == this->begin)
				{
					this->begin = new node(T, NULL, this->begin);
					this->begin->next->prev = this->begin;
					return (this->begin);
				}
				//if any other index
				ptr->prev->next = new node(T, ptr->prev, ptr);
				ptr->prev = ptr->prev->next;
				return (ptr->prev);
			}
			size_t	len;
			node	*begin;
			node	*end;
			Alloc	alloc;
	};

	template <class T, class Alloc>
	void swap (list<T,Alloc>& x, list<T,Alloc>& y)
	{
		return (x.swap(y));
	}

};

#endif
