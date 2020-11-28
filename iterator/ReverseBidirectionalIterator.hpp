/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ReverseReverseBidirectionalIterator.hpp                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/11 19:52:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/11/28 14:46:01 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_BIDIRECTIONAL_ITERATOR_HPP
# define REVERSE_BIDIRECTIONAL_ITERATOR_HPP

# include <BidirectionalIterator.hpp>
# include <traits.hpp>

namespace ft
{
	template <class Node, class PointerType, class ReferenceType, class Category = ft::bidirectional_iterator_tag>
	class	ReverseBidirectionalIterator : BidirectionalIterator<Node, PointerType, ReferenceType>
	{
		protected:
			Node	ptr;
		public:
			typedef BidirectionalIterator<Node, PointerType, ReferenceType>	iterator;
			typedef Category												iterator_category;
			ReverseBidirectionalIterator() : iterator(NULL)
			{
			}
			ReverseBidirectionalIterator(Node ptr) : iterator(ptr)
			{
			}
			~ReverseBidirectionalIterator()
			{
			}
			ReverseBidirectionalIterator(const ReverseBidirectionalIterator& iter) : iterator(iter)
			{
			}
			ReverseBidirectionalIterator&	operator = (const ReverseBidirectionalIterator& iter)
			{
				this->ptr = iter.ptr;
				return (*this);
			}
			ReverseBidirectionalIterator&	operator ++ ()
			{
				return (iterator::operator++);
			}
			ReverseBidirectionalIterator	operator ++ (int)
			{
				ReverseBidirectionalIterator old = *this;
				++(*this);
				return (old);
			}
			ReverseBidirectionalIterator&	operator -- ()
			{
				if (this->ptr)
					this->ptr = this->ptr->prev;
				return (*this);
			}
			ReverseBidirectionalIterator	operator -- (int)
			{
				ReverseBidirectionalIterator old(*this);
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
			bool					operator == (const ReverseBidirectionalIterator& iter) const
			{
				return (this->ptr == iter.ptr);
			}
			bool					operator != (const ReverseBidirectionalIterator& iter) const
			{
				return (!(*this == iter));
			}
	};
}

#endif
