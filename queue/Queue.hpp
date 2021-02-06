/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Queue.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/30 14:25:56 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/30 14:40:11 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

#include <memory>
#include "traits.hpp"
#include "GenericFunctions.hpp"
#include "List.hpp"

namespace ft
{
	//forard declare queue
	template<class T, class Container>
	class queue;

	//prototype operator overloads
	template <class T, class Container>
	bool	operator == (const queue<T, Container>& lhs, const queue<T, Container>& rhs);
	template <class T, class Container>
	bool	operator < (const queue<T, Container>& lhs, const queue<T, Container>& rhs);

	template <class T, class Container = ft::list<T> >
	class queue
	{
		public:
			//so we can declare them as friend
			friend bool operator < <> (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
			friend bool operator == <> (const queue<T,Container>& lhs, const queue<T,Container>& rhs);

			typedef Container								container_type;
			typedef typename Container::value_type			value_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;
			typedef typename Container::pointer				pointer;

			//CONSTRUCTORS

			queue(const Container& cont = Container()) : c(cont) {}
			queue(const queue& other) : c(other.c) {}
			~queue() {}
			queue& operator = (const queue& other)
			{
				if (this != &other)
					this->c = other.c;
				return (*this);
			}
			
			//ELEMENT ACCESS

			reference	front()
			{
				return (c.front());
			}
			const_reference	front() const
			{
				return (c.front());
			}
			reference	back()
			{
				return (c.back());
			}
			const_reference	back() const
			{
				return (c.back());
			}

			//CAPACITY

			bool	empty() const
			{
				return (c.empty());
			}
			size_t	size() const
			{
				return (c.size());
			}

			//MODIFIERS

			void	push(const value_type& val)
			{
				c.push_back(val);
			}
			void	pop()
			{
				c.pop_front();
			}
			void	swap(queue& other)
			{
				using ft::swap;
				swap(this->c, other.c);
			}
		protected:
			Container c;
	};

	template <class T, class Container>
	void	swap(queue<T,Container>& x, queue<T,Container>& y)
	{
		x.swap(y);
	}

	//needs to be friend to access the 'c' that's declared protected in queue
	template <class T, class Container>
	bool	operator == (const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool	operator != (const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return !(lhs == rhs);
	}

	//needs to be friend to access the 'c' that's declared protected in queue
	template <class T, class Container>
	bool	operator < (const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool	operator > (const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool	operator >= (const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Container>
	bool	operator <= (const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{
		return !(rhs < lhs);
	}
}

#endif
