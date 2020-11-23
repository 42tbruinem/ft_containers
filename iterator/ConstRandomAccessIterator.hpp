/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConstRandomAccessIterator.hpp                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 13:11:49 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/11/23 13:11:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <traits.hpp>

namespace ft
{
	template <class T, class Category = ft::random_access_iterator_tag>
	class	ConstRandomaccessIterator
	{
		private:
			T*	ptr;
		public:
			typedef Category					iterator_category;
			ConstRandomaccessIterator() : ptr(NULL)
			{
			}
			ConstRandomaccessIterator(T* ptr) : ptr(ptr)
			{
			}
			~ConstRandomaccessIterator()
			{
			}
			ConstRandomaccessIterator&	operator = (const ConstRandomaccessIterator& iter)
			{
				this->ptr = iter.ptr;
				return (*this);
			}
			ConstRandomaccessIterator(const ConstRandomaccessIterator& iter)
			{
				*this = iter;
			}
			ConstRandomaccessIterator&	operator++()
			{
				ptr++;
				return (*this);
			}
			ConstRandomaccessIterator	operator+(int val)
			{
				ConstRandomaccessIterator tmp = *this;
				tmp += val;
				return (tmp);
			}
			ConstRandomaccessIterator&	operator+=(int val)
			{
				this->ptr += val;
				return (*this);
			}
			ConstRandomaccessIterator	operator++(int)
			{
				ConstRandomaccessIterator old = *this;
				++(*this);
				return (old);
			}
			ConstRandomaccessIterator	operator-(int val)
			{
				ConstRandomaccessIterator tmp = *this;
				tmp -= val;
				return (tmp);
			}
			ConstRandomaccessIterator&	operator-=(int val)
			{
				this->ptr -= val;
				return (*this);
			}
			ConstRandomaccessIterator&	operator--()
			{
				ptr--;
				return (*this);
			}
			ConstRandomaccessIterator	operator--(int)
			{
				ConstRandomaccessIterator old = *this;
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
			bool	operator==(const ConstRandomaccessIterator& iter)
			{
				return (this->ptr == iter.ptr);
			}
			bool	operator!=(const ConstRandomaccessIterator& iter)
			{
				return (!(*this == iter));
			}
			bool	operator<(const ConstRandomaccessIterator& iter)
			{
				return (this->ptr < iter.ptr);
			}
			bool	operator>(const ConstRandomaccessIterator& iter)
			{
				return (this->ptr > iter.ptr);
			}
			bool	operator>=(const ConstRandomaccessIterator& iter)
			{
				return (this->ptr >= iter.ptr);
			}
			bool	operator<=(const ConstRandomaccessIterator& iter)
			{
				return (this->ptr <= iter.ptr);
			}
	};
}

#endif
