/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   List.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 15:50:30 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/12/02 21:22:44 by tbruinem      ########   odam.nl         */
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
				node() : prev(NULL), next(NULL) {}
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

			list(const Alloc& alloc = Alloc()) : len(0), head(new node()), tail(new node()), alloc(alloc)
			{
				head->next = tail;
				tail->prev = head;
			}
			list(size_t n, const T& val = T(), const Alloc& alloc = Alloc()) : len(0), head(new node()), tail(new node()), alloc(alloc)
			{
				head->next = tail;
				tail->prev = head;
				for (size_t i = 0; i < n; i++)
					newNode(val, i);
			}
			template<class InputIterator>
			list(InputIterator first, InputIterator last,
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::result, InputIterator>::type* = NULL,
				const Alloc& alloc = Alloc()) : len(0), head(new node()), tail(new node()), alloc(alloc)
			{
				head->next = tail;
				tail->prev = head;
				for (; first != last; first++)
					newNode(*first);
			}
			list(const list& other) : len(0), head(new node()), tail(new node()), alloc(other.alloc)
			{
				head->next = tail;
				tail->prev = head;
				for (const_iterator it = other.begin(); it != other.end(); it++)
					newNode(*it);
			}
			~list()
			{
				clear();
				delete this->head;
				delete this->tail;
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
				return (iterator(this->head->next));
			}
			const_iterator begin() const
			{
				return (const_iterator(this->head->next));
			}
			iterator end()
			{
				return (iterator(this->tail));
			}
			const_iterator end() const
			{
				return (const_iterator(this->tail));
			}
			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->tail->prev));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->tail->prev));
			}
			reverse_iterator rend()
			{
				return (reverse_iterator(this->head));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->head));
			}

			//CAPACITY

			bool empty() const
			{
				return !(this->len);
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
				return (this->head->next->element);
			}
			const T& front() const
			{
				return (this->head->next->element);
			}
			T& back()
			{
				return (this->tail->prev->element);
			}
			const T& back() const
			{
				return (this->tail->prev->element);
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
				return (iterator(newNode(val, pos)));
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
				last++;
				for (size_t i = 0; i < length ; i++)
					delNode(pos);
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
				splice(position, x, x.begin(), x.end());
			}
			void splice (iterator position, list& x, iterator i)
			{
				splice(position, x, i, ++i);
			}
			void splice (iterator position, list& x, iterator first, iterator last)
			{
				if (&x == this)
					return ;
				size_t len = ft::distance(first, last);

				connect(--iterator(position), first--);
				connect(first, last--);
				connect(last, position);

				this->len += len;
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
			void	connect(iterator front, iterator back)
			{
				front.ptr->next = back.ptr;
				back.ptr->prev = front.ptr;
			}
			void	delNode(size_t pos = std::numeric_limits<size_t>::max())
			{
				node *ptr = this->head->next;

				if (!this->len)
					return ;
				for (size_t i = 0; i < pos && ptr != NULL && ptr->next != this->tail; i++) //skip to the right position
					ptr = ptr->next;
				if (!ptr || ptr == this->tail)
					return ;
				node *prev = ptr->prev;
				ptr->prev->next = ptr->next;
				ptr->next->prev = prev;
				--this->len;
				delete ptr;
			}
			node	*newNode(const T& value, size_t pos = std::numeric_limits<size_t>::max())
			{
				node *ptr = this->head;

				for (size_t i = 0; i < pos && ptr && ptr->next != this->tail; i++)
					ptr = ptr->next;
				if (!ptr)
					return (NULL);
				ptr->next = new node(value, ptr, ptr->next);
				ptr->next->next->prev = ptr->next;
				this->len++;
				return (ptr->next);
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
