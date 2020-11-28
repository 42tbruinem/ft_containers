/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConstConstRandomAccessIterator.hpp                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/11 19:52:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/11/26 15:07:52 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_RANDOM_ACCESS_ITERATOR_HPP
# define CONST_RANDOM_ACCESS_ITERATOR_HPP

# include <traits.hpp>
# include "RandomAccessIterator.hpp"

namespace ft
{
	template <class PointerType, class ReferenceType, class Category = ft::random_access_iterator_tag>
	class	ConstRandomAccessIterator : RandomAccessIterator<PointerType, ReferenceType>
	{
		public:
			typedef RandomAccessIterator<PointerType, ReferenceType>	iterator;
			typedef Category											iterator_category;
			ConstRandomAccessIterator() : iterator()
			{
			}
			ConstRandomAccessIterator(PointerType ptr) : iterator(ptr)
			{
			}
			ConstRandomAccessIterator(const ConstRandomAccessIterator& iter) : iterator(iter)
			{
				*this = iter;
			}
			ConstRandomAccessIterator&	operator = (const ConstRandomAccessIterator& iter)
			{
				this->ptr = iter.ptr;
				return (*this);
			}
			ConstRandomAccessIterator&	operator ++ ()
			{
				ptr++;
				return (*this);
			}
			ConstRandomAccessIterator	operator + (int val) const
			{
				ConstRandomAccessIterator tmp = *this;
				tmp += val;
				return (tmp);
			}
			ConstRandomAccessIterator&	operator += (int val)
			{
				this->ptr += val;
				return (*this);
			}
			ConstRandomAccessIterator	operator ++ (int)
			{
				ConstRandomAccessIterator old = *this;
				++(*this);
				return (old);
			}
			ConstRandomAccessIterator	operator - (int val) const
			{
				ConstRandomAccessIterator tmp = *this;
				tmp -= val;
				return (tmp);
			}
			ConstRandomAccessIterator&	operator -= (int val)
			{
				this->ptr -= val;
				return (*this);
			}
			ConstRandomAccessIterator&	operator -- ()
			{
				ptr--;
				return (*this);
			}
			ConstRandomAccessIterator	operator -- (int)
			{
				ConstRandomAccessIterator old = *this;
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
			bool					operator == (const ConstRandomAccessIterator& iter) const
			{
				return (this->ptr == iter.ptr);
			}
			bool					operator != (const ConstRandomAccessIterator& iter) const
			{
				return (!(*this == iter));
			}
			bool					operator < (const ConstRandomAccessIterator& iter) const
			{
				return (this->ptr < iter.ptr);
			}
			bool					operator > (const ConstRandomAccessIterator& iter) const
			{
				return (this->ptr > iter.ptr);
			}
			bool					operator >= (const ConstRandomAccessIterator& iter) const
			{
				return (this->ptr >= iter.ptr);
			}
			bool					operator <= (const ConstRandomAccessIterator& iter) const
			{
				return (this->ptr <= iter.ptr);
			}
	};
}

#endif
