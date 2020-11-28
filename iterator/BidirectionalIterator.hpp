/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BidirectionalIterator.hpp                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/11 19:52:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/11/27 15:36:20 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include <traits.hpp>

namespace ft
{
	template <class Node, class PointerType, class ReferenceType, class Category = ft::bidirectional_iterator_tag>
	class	BidirectionalIterator
	{
		protected:
			Node	ptr;
		public:
			typedef Category					iterator_category;
			BidirectionalIterator() : ptr(NULL)
			{
			}
			BidirectionalIterator(Node ptr) : ptr(ptr)
			{
			}
			~BidirectionalIterator()
			{
			}
			BidirectionalIterator(const BidirectionalIterator& iter)
			{
				*this = iter;
			}
			BidirectionalIterator&	operator = (const BidirectionalIterator& iter)
			{
				this->ptr = iter.ptr;
				return (*this);
			}
			BidirectionalIterator&	operator ++ ()
			{
				if (this->ptr)
					this->ptr = this->ptr->next;
				return (*this);
			}
			BidirectionalIterator	operator + (int val) const
			{
				BidirectionalIterator tmp(*this);
				tmp += val;
				return (tmp);
			}
			BidirectionalIterator&	operator += (int val)
			{
				for (size_t i = 0; i < val && ptr; i++)
					++ptr;
				return (*this);
			}
			BidirectionalIterator	operator ++ (int)
			{
				BidirectionalIterator old = *this;
				++(*this);
				return (old);
			}
			BidirectionalIterator	operator - (int val) const
			{
				BidirectionalIterator tmp = *this;
				tmp -= val;
				return (tmp);
			}
			BidirectionalIterator&	operator -= (int val)
			{
				for (size_t i = 0; i < val && ptr; i++)
					--ptr;
				return (*this);
			}
			BidirectionalIterator&	operator -- ()
			{
				if (ptr)
					ptr = prev->next;
				return (*this);
			}
			BidirectionalIterator	operator -- (int)
			{
				BidirectionalIterator old(*this);
				--(*this);
				return (old);
			}
			ReferenceType			operator [] (int index) const
			{
				BidirectionalIterator old(*this);
				if (index >= 0)
					this += index;
				else
					this -= (index * -1);
				return (*old);
			}
			PointerType				operator -> () const
			{
				return (&(this->ptr->element));
			}
			ReferenceType			operator*() const
			{
				return (this->ptr->element);
			}
			bool					operator == (const BidirectionalIterator& iter) const
			{
				return (this->ptr == iter.ptr);
			}
			bool					operator != (const BidirectionalIterator& iter) const
			{
				return (!(*this == iter));
			}
			bool					operator < (const BidirectionalIterator& iter) const
			{
				return (this->ptr < iter.ptr);
			}
			bool					operator > (const BidirectionalIterator& iter) const
			{
				return (this->ptr > iter.ptr);
			}
			bool					operator >= (const BidirectionalIterator& iter) const
			{
				return (this->ptr >= iter.ptr);
			}
			bool					operator <= (const BidirectionalIterator& iter) const
			{
				return (this->ptr <= iter.ptr);
			}
	};
}

#endif
