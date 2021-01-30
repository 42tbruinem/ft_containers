/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Stack.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/30 12:48:03 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/30 14:10:04 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include <memory>
#include "GenericFunctions.hpp"
#include "IteratorFunctions.hpp"
#include "traits.hpp"
#include "List.hpp"

namespace ft
{
	template<class T, class Container>
	class stack;

	template <class T, class Container>
	bool	operator == (const stack<T, Container>& lhs, const stack<T, Container>& rhs);
	template <class T, class Container>
	bool	operator < (const stack<T, Container>& lhs, const stack<T, Container>& rhs);

	template <class T, class Container = ft::list<T> >
	class stack
	{
		public:
			friend bool operator < <> (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			friend bool operator == <> (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

			typedef	Container								container_type;
			typedef typename Container::value_type			value_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;

			explicit stack(const Container& cont = Container()) : c(cont) {}
			stack(const stack& other) : c(other.c) {}
			~stack() {}
			stack&	operator = (const stack& other)
			{
				if (this != &other)
				{
					this->c = other.c;
				}
				return (*this);
			}

			//ELEMENT ACCESS

			reference	top()
			{
				return (c.back());
			}
			const_reference	top() const
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
				c.pop_back();
			}
			void	swap(stack& other)
			{
				using ft::swap;
				swap(this->c, other.c);
			}
		protected:
			Container	c;
	};

	template <class T, class Container>
	void	swap(stack<T,Container>& x, stack<T,Container>& y)
	{
		x.swap(y);
	}

	template <class T, class Container>
	bool	operator == (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool	operator != (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool	operator < (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool	operator > (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool	operator >= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Container>
	bool	operator <= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return !(rhs < lhs);
	}
}

#endif
