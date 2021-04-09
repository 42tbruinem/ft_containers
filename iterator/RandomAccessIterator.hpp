/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RandomAccessIterator.hpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/11 19:52:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/09 19:12:47 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <traits.hpp>
# include <cstdlib>

namespace ft
{
	template <class PointerType, class ReferenceType, class Category = ft::random_access_iterator_tag>
	class	RandomAccessIterator
	{
		protected:
			PointerType	ptr;
		public:
			typedef Category					iterator_category;
			RandomAccessIterator() : ptr(NULL)
			{
			}
			RandomAccessIterator(PointerType ptr) : ptr(ptr)
			{
			}
			~RandomAccessIterator()
			{
			}
			RandomAccessIterator(const RandomAccessIterator& iter)
			{
				*this = iter;
			}
			RandomAccessIterator&	operator = (const RandomAccessIterator& iter)
			{
				this->ptr = iter.ptr;
				return (*this);
			}
			RandomAccessIterator&	operator ++ ()
			{
				ptr++;
				return (*this);
			}
			RandomAccessIterator	operator + (int val) const
			{
				RandomAccessIterator tmp = *this;
				tmp += val;
				return (tmp);
			}
			RandomAccessIterator&	operator += (int val)
			{
				this->ptr += val;
				return (*this);
			}
			RandomAccessIterator	operator ++ (int)
			{
				RandomAccessIterator old = *this;
				++(*this);
				return (old);
			}
			RandomAccessIterator	operator - (int val) const
			{
				RandomAccessIterator tmp = *this;
				tmp -= val;
				return (tmp);
			}
			RandomAccessIterator&	operator -= (int val)
			{
				this->ptr -= val;
				return (*this);
			}
			RandomAccessIterator&	operator -- ()
			{
				ptr--;
				return (*this);
			}
			RandomAccessIterator	operator -- (int)
			{
				RandomAccessIterator old = *this;
				--(*this);
				return (old);
			}
			ReferenceType			operator [] (int index) const
			{
				return *(this->ptr + index);
			}
			PointerType				operator -> () const
			{
				return (this->ptr);
			}
			ReferenceType			operator*() const
			{
				return *(this->ptr);
			}
			bool					operator == (const RandomAccessIterator& iter) const
			{
				return (this->ptr == iter.ptr);
			}
			bool					operator != (const RandomAccessIterator& iter) const
			{
				return (!(*this == iter));
			}
			bool					operator < (const RandomAccessIterator& iter) const
			{
				return (this->ptr < iter.ptr);
			}
			bool					operator > (const RandomAccessIterator& iter) const
			{
				return (this->ptr > iter.ptr);
			}
			bool					operator >= (const RandomAccessIterator& iter) const
			{
				return (this->ptr >= iter.ptr);
			}
			bool					operator <= (const RandomAccessIterator& iter) const
			{
				return (this->ptr <= iter.ptr);
			}
	};
}

#endif
