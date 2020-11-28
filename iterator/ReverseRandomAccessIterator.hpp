/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ReverseRandomAccessIterator.hpp                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/11 19:52:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/11/26 15:06:58 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_RANDOM_ACCESS_ITERATOR_HPP
# define REVERSE_RANDOM_ACCESS_ITERATOR_HPP

# include <traits.hpp>
# include "RandomAccessIterator.hpp"

namespace ft
{
	template <class PointerType, class ReferenceType, class Category = ft::random_access_iterator_tag>
	class	ReverseRandomAccessIterator : public RandomAccessIterator<PointerType, ReferenceType>
	{
		public:
			typedef RandomAccessIterator<PointerType, ReferenceType>	iterator;
			typedef Category											iterator_category;
			ReverseRandomAccessIterator() : iterator()
			{
			}
			ReverseRandomAccessIterator(PointerType ptr) : iterator(ptr)
			{
			}
			ReverseRandomAccessIterator(const ReverseRandomAccessIterator& iter) : iterator(iter)
			{
			}
			ReverseRandomAccessIterator&	operator = (const ReverseRandomAccessIterator& iter)
			{
				this->ptr = iter.ptr;
				return (*this);
			}
			ReverseRandomAccessIterator&	operator ++ ()
			{
				this->ptr--;
				return (*this);
			}
			ReverseRandomAccessIterator		operator + (int val) const
			{
				ReverseRandomAccessIterator tmp = *this;
				tmp += val;
				return (tmp);
			}
			ReverseRandomAccessIterator		operator += (int val)
			{
				this->ptr -= val;
				return (*this);
			}
			ReverseRandomAccessIterator		operator ++ (int)
			{
				ReverseRandomAccessIterator old = *this;
				++(*this);
				return (old);
			}
			ReverseRandomAccessIterator		operator - (int val) const
			{
				ReverseRandomAccessIterator tmp = *this;
				tmp -= val;
				return (tmp);
			}
			ReverseRandomAccessIterator		operator -= (int val)
			{
				this->ptr += val;
				return (*this);
			}
			ReverseRandomAccessIterator&	operator -- ()
			{
				this->ptr++;
				return (*this);
			}
			ReverseRandomAccessIterator		operator -- (int)
			{
				ReverseRandomAccessIterator old = *this;
				--(*this);
				return (old);
			}
			ReferenceType					operator [] (int index) const
			{
				return *(this->ptr - index);
			}
			PointerType						operator -> () const
			{
				return (this->ptr);
			}
			ReferenceType					operator * () const
			{
				return *(this->ptr);
			}
			bool							operator ==	(const ReverseRandomAccessIterator& iter) const
			{
				return (this->ptr == iter.ptr);
			}
			bool							operator != (const ReverseRandomAccessIterator& iter) const
			{
				return (this->ptr != iter.ptr);
			}
			bool							operator < (const ReverseRandomAccessIterator& iter) const
			{
				return (iter.ptr < this->ptr);
			}
			bool							operator > (const ReverseRandomAccessIterator& iter) const
			{
				return (iter.ptr > this->ptr);
			}
			bool							operator >=	(const ReverseRandomAccessIterator& iter) const
			{
				return (iter.ptr >= this->ptr);
			}
			bool							operator <=	(const ReverseRandomAccessIterator& iter) const
			{
				return (iter.ptr <= this->ptr);
			}
	};
}

#endif
