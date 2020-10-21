/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ReverseRandomAccessIterator.hpp                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/11 19:52:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/21 17:19:33 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_RANDOM_ACCESS_ITERATOR_HPP
# define REVERSE_RANDOM_ACCESS_ITERATOR_HPP

# include <traits.hpp>

namespace ft
{
	template <class T, class Category = ft::random_access_iterator_tag>
	class	ReverseRandomAccessIterator
	{
		private:
			T*	ptr;
		public:
			typedef Category								iterator_category;
			ReverseRandomAccessIterator() : ptr(NULL)
			{
			}
			ReverseRandomAccessIterator(T* ptr) : ptr(ptr)
			{
			}
			~ReverseRandomAccessIterator()
			{
			}
			ReverseRandomAccessIterator&	operator = (const ReverseRandomAccessIterator& iter)
			{
				this->ptr = iter.ptr;
				return (*this);
			}
			ReverseRandomAccessIterator(const ReverseRandomAccessIterator& iter)
			{
				*this = iter;
			}
			ReverseRandomAccessIterator&	operator++()
			{
				ptr--;
				return (*this);
			}
			ReverseRandomAccessIterator	operator+(int val)
			{
				ReverseRandomAccessIterator tmp = *this;
				tmp += val;
				return (tmp);
			}
			ReverseRandomAccessIterator	operator+=(int val)
			{
				this->ptr -= val;
				return (*this);
			}
			ReverseRandomAccessIterator	operator++(int)
			{
				ReverseRandomAccessIterator old = *this;
				++(*this);
				return (old);
			}
			ReverseRandomAccessIterator	operator-(int val)
			{
				ReverseRandomAccessIterator tmp = *this;
				tmp -= val;
				return (tmp);
			}
			ReverseRandomAccessIterator	operator-=(int val)
			{
				this->ptr += val;
				return (*this);
			}
			ReverseRandomAccessIterator&	operator--()
			{
				ptr++;
				return (*this);
			}
			ReverseRandomAccessIterator	operator--(int)
			{
				ReverseRandomAccessIterator old = *this;
				--(*this);
				return (old);
			}
			T&	operator[](int index)
			{
				return *(this->ptr - index);
			}
			T*	operator->()
			{
				return (this->ptr);
			}
			T&	operator*()
			{
				return *(this->ptr);
			}
			bool	operator==(const ReverseRandomAccessIterator& iter)
			{
				return (this->ptr == iter.ptr);
			}
			bool	operator!=(const ReverseRandomAccessIterator& iter)
			{
				return (this->ptr != iter.ptr);
			}
			bool	operator<(const ReverseRandomAccessIterator& iter)
			{
				return (iter.ptr < this->ptr);
			}
			bool	operator>(const ReverseRandomAccessIterator& iter)
			{
				return (iter.ptr > this->ptr);
			}
			bool	operator>=(const ReverseRandomAccessIterator& iter)
			{
				return (iter.ptr >= this->ptr);
			}
			bool	operator<=(const ReverseRandomAccessIterator& iter)
			{
				return (iter.ptr <= this->ptr);
			}
	};
}

#endif
