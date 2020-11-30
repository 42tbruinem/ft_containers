/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   List.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 15:50:30 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/11/30 23:03:27 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <limits>
# include <traits.hpp>
# include "IteratorFunctions.hpp"
# include <BidirectionalIterator.hpp>
# include <ReverseBidirectionalIterator.hpp>
# include <GenericFunctions.hpp>
# include <list>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class	list
	{
		class node
		{
			public:
				T		element;
				node	*prev;
				node	*next;
				node(const T& element, node *prev = NULL, node *next = NULL) : element(element), prev(prev), next(next) {}
//				bool operator == (const node& other) { return (prev == other.prev && next == other.next); }
//				bool operator != (const node& other) { return !(*this == other); }
		};
		public:
			typedef T*														pointer;
			typedef T&														reference;
			typedef const T*												const_pointer;
			typedef const T& 												const_reference;
			typedef BidirectionalIterator<node, T*, T&>						iterator;
			typedef BidirectionalIterator<node, const T*, const T&>			const_iterator;
			typedef ReverseBidirectionalIterator<node, T&, const T&>		reverse_iterator;
			typedef ReverseBidirectionalIterator<node, const T*, const T&>	const_reverse_iterator;

			//CONSTRUCTORS / DESTRUCTOR

			list(const Alloc& alloc = Alloc()) : len(0), head(NULL), tail(NULL), alloc(alloc) {}
			list(size_t n, const T& val = T(), const Alloc& alloc = Alloc()) : len(0), head(NULL), tail(NULL), alloc(alloc)
			{
				for (size_t i = 0; i < n; i++)
					newNode(val, i);
			}
			template<class InputIterator>
			list(InputIterator first, InputIterator last,
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::result, InputIterator>::type* = NULL,
				const Alloc& alloc = Alloc()) : len(0), head(NULL), tail(NULL), alloc(alloc)
			{
				for (; first != last; first++)
					newNode(*first);
			}
			list(const list& other) : len(0), head(NULL), tail(NULL), alloc(other.alloc)
			{
				for (typename list<T>::const_iterator it = other.begin(); it != other.end(); it++)
					newNode(*it);
			}
			~list()
			{
				clear();
			}
			list& operator = (const list& other)
			{
				clear();
				for (typename list<T>::const_iterator it = other.begin(); it != other.end(); it++)
					newNode(*it);
				return (*this);
			}

			// ITERATORS

			iterator begin()
			{
				return (iterator(this->head));
			}
			const_iterator begin() const
			{
				return (const_iterator(this->head));
			}
			iterator end()
			{
				return (iterator(NULL));
			}
			const_iterator end() const
			{
				return (const_iterator(NULL));
			}
			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->tail));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->tail));
			}
			reverse_iterator rend()
			{
				return (reverse_iterator(NULL));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(NULL));
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
				return (this->head->element);
			}
			const T& front() const
			{
				return (this->head->element);
			}
			T& back()
			{
				return (this->tail->element);
			}
			const T& back() const
			{
				return (this->tail->element);
			}

			//MODIFIERS

			template <class InputIterator>
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

				position++;
				delNode(pos);
				return (position);
			}
			iterator erase(iterator first, iterator last)
			{
				size_t pos = ft::distance(this->begin(), first);
				size_t length = ft::distance(first, last);
				for (size_t i = 0; i < length ; i++)
					delNode(pos);
				last++;
				return (last);
			}
			void swap(list& x)
			{
				ft::swap(this->head, x.head);
				ft::swap<size_t>(this->len, x.len);
				ft::swap(this->tail, x.tail);
			}
			void resize(size_t n, T val = T())
			{
				size_t len = this->len;
				if (this->len == n)
					return ;
				if (this->len > n)
				{
					for (size_t i = 0 ; i < (len - n); i++)
						delNode();
				}
				else
				{
					for (; len < n; len++)
						newNode(val);
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
				transfer((Node) ? Node->prev : this->tail, Node, x.head, x.tail);

				this->len += x.len;
				x.len = 0;
				x.head = NULL;
				x.tail = NULL;
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
				node *iter = this->head;
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
				node *iter = this->head;
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
				node *iter = this->head;
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
				node *iter = this->head;
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
		private:
			void	transfer(node *prev, node *pos, node *otherBegin, node *otherEnd)
			{
				//NULL->prev->otherBegin->...->otherEnd->pos
				if (prev)
					prev->next = otherBegin;
				//NULL->otherBegin->...->otherEnd->pos
				else
					this->head = otherBegin;
				//NULL->otherBegin->...->otherEnd->pos->NULL
				if (pos)
					pos->prev = otherEnd;
				//NULL->otherBegin->...->otherEnd->NULL
				else
					this->tail = otherEnd;
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
				node *ptr = this->head;

				if (!ptr)
					return ;
				//if start of list
				if (pos == 0)
				{
					ptr = this->head;
					this->head = this->head->next;
					if (this->head)
						this->head->prev = NULL;
					if (this->len <= 1)
						this->tail = this->head;
					delete ptr;
				}
				//if end of list
				else if (pos >= this->len)
				{
					ptr = this->tail;
					this->tail = this->tail->prev;
					if (this->tail)
						this->tail->next = NULL;
					if (this->len == 1)
						this->head = this->tail;
					delete ptr;
				}
				//if any other index
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
//				dprintf(2, "head: %p\n", (void *)this->head);
//				dprintf(2, "tail: %p\n", (void *)this->tail);
//				dprintf(2, "size: %ld\n", this->len);
			}
			node	*newNode(const T& value, size_t pos = std::numeric_limits<size_t>::max())
			{
				node *ptr = this->head;
				//if push_back()
				if (this->len && pos >= this->len)
				{
					this->len++;
					this->tail->next = new node(value, this->tail, NULL);
					this->tail = this->tail->next;
					return (this->tail);
				}
				else //index
					for (size_t i = 0; i < pos && ptr != NULL; i++)
						ptr = ptr->next;
				this->len++;
				//if start of the list
				if (!ptr)
				{
					this->head = new node(value);
					this->tail = this->head;
					return (this->head);
				}
				//if index 0
				if (ptr == this->head)
				{
					this->head = new node(value, NULL, this->head);
					if (this->head->next)
						this->head->next->prev = this->head;
					return (this->head);
				}
				//if any other index
				ptr->prev->next = new node(value, ptr->prev, ptr);
				ptr->prev = ptr->prev->next;
				return (ptr->prev);
			}
			size_t	len;
			node	*head;
			node	*tail;
			Alloc	alloc;
	};

	template <class T, class Alloc>
	void swap (list<T,Alloc>& x, list<T,Alloc>& y)
	{
		return (x.swap(y));
	}

}

#endif
