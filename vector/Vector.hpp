/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/06 19:28:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/21 21:38:45 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <RandomAccessIterator.hpp>
# include <ReverseRandomAccessIterator.hpp>
# include <IteratorFunctions.hpp>
# include <cstddef>
# include <stdexcept>
# include <traits.hpp>
# include <iostream>
# include <memory>

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class	vector
	{
		private:
			T *data;
			size_t	cap;
			size_t	len;
			Alloc	alloc;
			void	reallocate(size_t new_cap)
			{
				T* newData;

				newData = new T[new_cap];
				for (size_t i = 0; i < new_cap && i < this->len; i++)
					newData[i] = this->data[i];
				delete [] this->data;
				this->data = newData;
				this->cap = new_cap;
				this->len = (this->len > new_cap) ? new_cap : this->len;
			}
		public:
			typedef RandomAccessIterator<T>			iterator;
			typedef ReverseRandomAccessIterator<T>	reverse_iterator;
			vector(const Alloc& alloc = Alloc()) : alloc(alloc)
			{
				this->cap = 4;
				this->data = new T[this->cap];
				this->len = 0;
			}
			template <typename InputIterator>
			vector(InputIterator first, InputIterator last,
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::result, InputIterator>::type* = NULL,
				const Alloc& alloc = Alloc()) : alloc(alloc)
			{
				this->cap = ft::distance(first, last);
				this->data = new T[this->cap];
				for (size_t i = 0;first != last; first++,i++)
					this->data[i] = *first;
				this->len = this->cap;
			}
			vector(size_t size, const T& val = T(), const Alloc& alloc = Alloc()) : alloc(alloc)
			{
				this->cap = size + (size % 4);
				this->data = new T[this->cap];
				for (size_t i = 0; i < size; i++)
					this->data[i] = val;
				this->len = size;
			}
			vector(const vector& orig) : alloc(orig.alloc)
			{
				this->data = NULL;
				this->len = 0;
				*this = orig;
			}
			vector& operator = (const vector& orig)
			{
				if (this != &orig)
				{
					this->reallocate(orig.cap);
					for (size_t i = 0; i < orig.len; i++)
						this->data[i] = orig.data[i];
					this->len = orig.len;
				}
				return (*this);
			}
			~vector()
			{
				delete [] data;
				this->cap = 0;
				this->len = 0;
			}
			void	push_back(T add)
			{
//				std::cout << "FT" << std::endl; //<-- used to show that the ft::vector is actually being used
				if (this->len + 1 >= this->cap)
				{
					if (this->cap >= 2)
						this->reallocate(this->cap * 1.5);
					else
						this->reallocate(this->cap + 1);
				}
				this->data[this->len] = add;
				this->len++;
			}
			void	pop_back()
			{
				if (this->len)
					this->len--;
			}
			void	resize(size_t n, T val = T())
			{
				this->reallocate(n);
				for (;this->len < n; this->len++)
					this->data[this->len] = val;
			}
			void	reserve(size_t n)
			{
				if (n > this->cap)
					this->reallocate(n);
			}
			T& operator [] (size_t index)
			{
				return (this->data[index]);
			}
			const T& operator [] (size_t index) const
			{
//				std::cout << "CONST" << std::endl; //<--check if the const overload is actually being used
				return (this->data[index]);
			}
			T&	at(size_t n)
			{
				if (index >= this->len)
					throw std::out_of_range("requested index is out of range");
				return (this->data[index]);
			}
			const T&	at(size_t n) const
			{
				if (index >= this->len)
					throw std::out_of_range("requested index is out of range");
				return (this->data[index]);
			}
			T&	front()
			{
				return (this->data[i]);
			}
			const T&	front() const
			{
				return (this->data[i]);
			}
			T&	back()
			{
				return (this->data[this->size() - 1]);
			}
			const T&	back() const
			{
				return (this->data[this->size() - 1]);
			}
			iterator	begin()
			{
				return (iterator(this->data));
			}
			iterator	end()
			{
				return (iterator(this->data + this->len));
			}
			reverse_iterator	rbegin()
			{
				return (reverse_iterator(this->data + this->len - 1));
			}
			reverse_iterator	rend()
			{
				return (reverse_iterator(this->data - 1));
			}
			size_t size() const
			{
				return (this->len);
			}
			size_t max_size() const
			{
				return (alloc.max_size());
			}
			bool	empty() const
			{
				return (!this->len);
			}
			size_t capacity() const
			{
				return (this->cap);
			}
	};
}

#endif
