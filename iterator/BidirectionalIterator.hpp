/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BidirectionalIterator.hpp                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/11 19:52:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/11/30 16:48:17 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include <traits.hpp>
# include <stdio.h>

namespace ft
{
	template <class Node, class PointerType, class ReferenceType, class Category = ft::bidirectional_iterator_tag>
	class	BidirectionalIterator
	{
		public:
			Node	*ptr;
		public:
			typedef Category					iterator_category;
			BidirectionalIterator() : ptr(NULL)
			{
			}
			BidirectionalIterator(Node *ptr) : ptr(ptr)
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
//				dprintf(2, "ptr: %p\n", (void *)this->ptr);
				if (this->ptr)
				{
//					dprintf(2, "next: %p\n", (void *)this->ptr->next);
//					dprintf(2, "prev: %p\n", (void *)this->ptr->prev);
					this->ptr = this->ptr->next;
				}
				return (*this);
			}
			BidirectionalIterator	operator ++ (int)
			{
				BidirectionalIterator old(*this);
				++(*this);
				return (old);
			}
			BidirectionalIterator&	operator -- ()
			{
				if (this->ptr)
					this->ptr = this->ptr->prev;
				return (*this);
			}
			BidirectionalIterator	operator -- (int)
			{
				BidirectionalIterator old(*this);
				--(*this);
				return (old);
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
	};
}

#endif
