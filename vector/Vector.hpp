/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/06 19:28:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/11 21:26:30 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <RandomAccessIterator.hpp>
# include <cstddef>
# include <stdexcept>
//# include <memory>

namespace ft
{
	template <typename T>
	class	vector
	{
		private:
			T *data;
			size_t	capacity;
			size_t	len;
			void	reallocate(size_t new_cap, T val = T())
			{
				T* newData;

				newData = new T[new_cap];
				for (size_t i = 0; i < new_cap && this->len; i++)
					newData[i] = this->data[i];
				delete [] this->data;
				if (new_cap < this->len)
				{
					for (size_t i = new_cap; i < this->len; i++)
						this->data[i] = val;
				}
				this->data = newData;
				this->capacity = new_cap;
				this->len = (this->len > new_cap) ? new_cap : this->len;
			}
		public:
			typedef RandomAccessIterator<T>	iterator;
			vector()
			{
				this->capacity = 4;
				this->data = new T[this->capacity];
				this->len = 0;
			}
			// template <classname InputIterator>
			// vector(InputIterator first, InputIterator last)
			// {
			// 	this->capacity = ft::distance(first, last);
			// 	this->data = new T[this->capacity];
			// 	for (size_t i = 0;first != last; first++,i++)
			// 		this->data[i] = *first;
			// 	this->len = this->capacity;
			// }
			vector(size_t size, T val = T())
			{
				this->capacity = size + (size % 4);
				this->data = new T[this->capacity];
				for (size_t i = 0; i < size; i++)
					this->data[i] = val;
				this->len = size;
			}
			vector(const vector& orig)
			{
				this->data = NULL;
				this->len = 0;
				*this = orig;
			}
			vector& operator = (const vector& orig)
			{
				if (this != &orig)
				{
					this->reallocate(orig.capacity);
					for (size_t i = 0; i < orig.len; i++)
						this->data[i] = orig.data[i];
				}
				return (*this);
			}
			~vector()
			{
				delete [] data;
				this->capacity = 0;
				this->len = 0;
			}
			void	push_back(T add)
			{
				if (this->len + 1 >= this->capacity)
					this->reallocate(this->capacity * 1.5);
				this->data[this->len++] = add;
			}
			void	resize(size_t n, T val = T())
			{
				this->reallocate(n, val);
			}
			T& operator [] (size_t index)
			{
				if (index >= this->len)
					throw std::out_of_range("requested index is out of range");
				return (this->data[index]);
			}
			iterator	begin()
			{
				return (iterator(this->data));
			}
			iterator	end()
			{
				return (iterator(this->data + this->len));
			}
			size_t size() const
			{
				return (this->len);
			}
	};
}

#endif
