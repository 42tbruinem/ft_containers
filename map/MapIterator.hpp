/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MapIterator.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 20:57:33 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/12/17 21:07:24 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "traits.hpp"

namespace ft
{
	template <class Node, class ReferenceType, class PointerType, class Category = ft::bidirectional_iterator_tag>
	class MapIterator
	{
		public:
			MapIterator() : ptr(NULL) {}
			MapIterator(const MapIterator& other) : ptr(other.ptr) {}
			MapIterator& operator = (const MapIterator& other)
			{
				if (this != &other)
				{
					this->ptr = other.ptr;
				}
				return (*this);
			}
			~MapIterator() {}
			MapIterator& operator ++ ()
			{
				//increment iterator
				return (*this);
			}
			MapIterator& operator ++ (int)
			{
				MapIterator	other(*this);
				//increment iterator
				return (other);
			}
			MapIterator& operator -- ()
			{
				//increment iterator
				return (*this);
			}
			MapIterator& operator -- (int)
			{
				MapIterator	other(*this);
				//increment iterator
				return (other);
			}
			PointerType	operator -> ()
			{
				return (&(this->ptr->element));
			}
			ReferenceType operator * ()
			{
				return (this->ptr->element);
			}
			bool	operator == (const MapIterator& other)
			{
				return (this->ptr == other.ptr);
			}
			bool	operator != (const MapIterator& other)
			{
				return !(*this == other);
			}
		private:
			Node *ptr;
	};
}

#endif
