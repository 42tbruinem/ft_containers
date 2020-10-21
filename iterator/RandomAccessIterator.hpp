/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RandomAccessIterator.hpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/11 19:52:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/21 16:45:14 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <traits.hpp>

namespace ft
{
	template <class T, class Category = ft::random_access_iterator_tag>
	class	RandomAccessIterator
	{
		private:
			T*	ptr;
		public:
			typedef Category					iterator_category;
			RandomAccessIterator() : ptr(NULL)
			{
			}
			RandomAccessIterator(T* ptr) : ptr(ptr)
			{
			}
			~RandomAccessIterator()
			{
			}
			RandomAccessIterator&	operator = (const RandomAccessIterator& iter)
			{
				this->ptr = iter.ptr;
				return (*this);
			}
			RandomAccessIterator(const RandomAccessIterator& iter)
			{
				*this = iter;
			}
			RandomAccessIterator&	operator++()
			{
				ptr++;
				return (*this);
			}
			RandomAccessIterator	operator+(int val)
			{
				RandomAccessIterator tmp = *this;
				tmp += val;
				return (tmp);
			}
			RandomAccessIterator&	operator+=(int val)
			{
				this->ptr += val;
				return (*this);
			}
			RandomAccessIterator	operator++(int)
			{
				RandomAccessIterator old = *this;
				++(*this);
				return (old);
			}
			RandomAccessIterator	operator-(int val)
			{
				RandomAccessIterator tmp = *this;
				tmp -= val;
				return (tmp);
			}
			RandomAccessIterator&	operator-=(int val)
			{
				this->ptr -= val;
				return (*this);
			}
			RandomAccessIterator&	operator--()
			{
				ptr--;
				return (*this);
			}
			RandomAccessIterator	operator--(int)
			{
				RandomAccessIterator old = *this;
				--(*this);
				return (old);
			}
			T&	operator[](int index)
			{
				return *(this->ptr + index);
			}
			T*	operator->()
			{
				return (this->ptr);
			}
			T&	operator*()
			{
				return *(this->ptr);
			}
			bool	operator==(const RandomAccessIterator& iter)
			{
				return (this->ptr == iter.ptr);
			}
			bool	operator!=(const RandomAccessIterator& iter)
			{
				return (!(*this == iter));
			}
			bool	operator<(const RandomAccessIterator& iter)
			{
				return (this->ptr < iter.ptr);
			}
			bool	operator>(const RandomAccessIterator& iter)
			{
				return (this->ptr > iter.ptr);
			}
			bool	operator>=(const RandomAccessIterator& iter)
			{
				return (this->ptr >= iter.ptr);
			}
			bool	operator<=(const RandomAccessIterator& iter)
			{
				return (this->ptr <= iter.ptr);
			}
	};
}

#endif
