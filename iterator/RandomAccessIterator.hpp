/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   IRandomAccess.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/11 19:52:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/11 20:59:37 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

namespace ft
{
	template <class T>
	class	RandomAccessIterator
	{
		private:
			T*	ptr;
			RandomAccessIterator() {}
		public:
			RandomAccessIterator(T* ptr) : ptr(ptr) {}
			~RandomAccessIterator() {}
			RandomAccessIterator&	operator = (const RandomAccessIterator& iter)
			{
				this->ptr = iter.ptr;
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
			RandomAccessIterator	operator++(int)
			{
				RandomAccessIterator old = *this;
				++(*this);
				return (old);
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
};

#endif
