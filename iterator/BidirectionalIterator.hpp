/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BidirectionalIterator.hpp                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/11 19:52:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/12/16 16:08:00 by tbruinem      ########   odam.nl         */
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
			BidirectionalIterator() : ptr(NULL) {}
			BidirectionalIterator(Node *ptr) : ptr(ptr) {}
			~BidirectionalIterator() {}
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
				if (this->ptr->next)
					this->ptr = this->ptr->next;
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
				if (this->ptr->prev)
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
