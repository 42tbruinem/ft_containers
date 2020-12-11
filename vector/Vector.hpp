/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/06 19:28:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/12/09 17:51:08 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <RandomAccessIterator.hpp>
# include <ReverseRandomAccessIterator.hpp>
# include <GenericFunctions.hpp>
# include <IteratorFunctions.hpp>
# include <cstddef>
# include <stdexcept>
# include <traits.hpp>
//# include <iostream>
# include <memory>

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class	vector
	{
		public:
			typedef RandomAccessIterator<T*, T&>					iterator;
			typedef ReverseRandomAccessIterator<T*, T&>				reverse_iterator;
			typedef RandomAccessIterator<const T*, const T&>		const_iterator;
			typedef ReverseRandomAccessIterator<const T*, const T&>	const_reverse_iterator;

//			CONSTRUCTORS//DESTRUCTOR//OPERATOR=

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
				for (size_t i = 0; first != last; first++, i++)
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

//			ITERATORS

			iterator	begin()
			{
				return (iterator(this->data));
			}
			iterator	end()
			{
				return (iterator(this->data + this->len));
			}
			const_iterator	begin() const
			{
				return (const_iterator(this->data));
			}
			const_iterator	end() const
			{
				return (const_iterator(this->data + this->len));
			}
			reverse_iterator	rbegin()
			{
				return (reverse_iterator(this->data + this->len - 1));
			}
			reverse_iterator	rend()
			{
				return (reverse_iterator(this->data - 1));
			}
			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(this->data + this->len - 1));
			}
			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(this->data - 1));
			}

//			CAPACITY

			size_t size() const
			{
				return (this->len);
			}
			size_t max_size() const
			{
				return (alloc.max_size());
			}
			void	resize(size_t n, T val = T())
			{
				this->reallocate(n);
				for (;this->len < n; this->len++)
					this->data[this->len] = val;
			}
			size_t capacity() const
			{
				return (this->cap);
			}
			bool	empty() const
			{
				return (!this->len);
			}
			void	reserve(size_t n)
			{
				if (n > this->cap)
					this->reallocate(n);
			}

//			ELEMENT ACCESS

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
				if (n >= this->len)
					throw std::out_of_range("requested index is out of range");
				return (this->data[n]);
			}
			const T&	at(size_t n) const
			{
				if (n >= this->len)
					throw std::out_of_range("requested index is out of range");
				return (this->data[n]);
			}
			T&	front()
			{
				return (this->data[0]);
			}
			const T&	front() const
			{
				return (this->data[0]);
			}
			T&	back()
			{
				return (this->data[this->size() - 1]);
			}
			const T&	back() const
			{
				return (this->data[this->size() - 1]);
			}

//			MODIFIERS

			template <typename InputIterator>
			void	assign(InputIterator first, InputIterator last,
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::result, InputIterator>::type* = NULL)
			{
				size_t	dist = ft::distance(first, last);
				this->reallocate(dist, 0);
				for (size_t i = 0; first != last; first++, i++)
					this->data[i] = *first;
				this->len = dist;
			}
			void	assign(size_t n, const T& val)
			{
				this->reallocate(n);
				for (size_t i = 0; i < n; i++)
					this->data[i] = val;
				this->len = n;
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
			iterator	insert(iterator position, const T& val)
			{
				T& tmp = *position;
				size_t pos = (&tmp - this->data);
//				std::cout << "POS: " << pos << std::endl;
				reallocate(this->len + 1, pos, 1);
				this->data[pos] = val;
				this->len++;
				return (iterator(this->data + pos));
			}
			void	insert(iterator position, size_t n, const T& val)
			{
				T& tmp = *position;
				size_t pos = (&tmp - this->data);
				reallocate(this->len + n, pos, n);
				for (size_t i = pos; i < pos + n; i++)
					this->data[i] = val;
				this->len += n;
			}
			template <typename InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last,
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::result, InputIterator>::type* = NULL)
			{
				size_t n = ft::distance(first, last);

				T& tmp = *position;
				size_t pos = (&tmp - this->data);
				reallocate(this->len + n, pos, n);
				for (;first != last; first++, pos++)
					this->data[pos] = *first;
				this->len += n;
			}
			iterator	erase(iterator position)
			{
				size_t pos = ft::distance(this->begin(), position);
				if (pos > this->len)
					throw (std::out_of_range("supplied iterator was out of range"));
				reallocate(this->len - 1, pos, 1, true);
				return (begin() + pos);
			}
			iterator	erase(iterator first, iterator last)
			{
				size_t	pos = ft::distance(begin(), first);
				size_t	dist = ft::distance(first, last);
				if (dist > this->len)
					dist = this->len;
				size_t	new_size = this->len - dist;
				reallocate(new_size, pos, dist, true);
				return (begin() + pos);
			}
			void	swap(vector<T>& x)
			{
				ft::swap(this->data, x.data);
				ft::swap(this->len, x.len);
				ft::swap(this->cap, x.cap);
			}
			void	clear()
			{
				reallocate(0);
			}

//			OPERATORS

			bool	operator == (vector<T>& other)
			{
				if (this->len != other.len)
					return (false);
				typename vector<T>::iterator this_it = this->begin();
				typename vector<T>::iterator other_it = other.begin();
				for (; this_it != this->end(); this_it++, other_it++)
					if (*this_it != *other_it)
						return (false);
				return (true);
			}
			bool	operator != (vector<T>& other)
			{
				return !(*this == other);
			}
			bool	operator < (vector<T>& other)
			{
				bool	same_length = (this->len == other.len);

				typename vector<T>::iterator this_it = this->begin();
				typename vector<T>::iterator other_it = other.begin();
				for (; this_it != this->end() && other_it != other.end(); this_it++, other_it++)
				{
					if (*other_it < *this_it)
						return (false);
					else if (*this_it < *other_it)
						return (true);
				}
				return (same_length);
			}
			bool	operator > (vector<T>& other)
			{
				return (other < *this);
			}
			bool	operator >= (vector<T>& other)
			{
				return !(*this < other);
			}
			bool	operator <= (vector<T>& other)
			{
				return !(other < *this);
			}

		private:
			T *data;
			size_t	cap;
			size_t	len;
			Alloc	alloc;

//reallocate(this->len + 1, pos, 1);
			void	reallocate(size_t new_cap, size_t pos = std::string::npos, size_t gap = 0, bool erase = false)
			{
				T* newData;

				if (pos > this->len)
					pos = this->len;
				newData = new T[new_cap];
				//copy everything preceding pos
				size_t i = 0;
				for (; i < new_cap && i < pos; i++)
					newData[i] = this->data[i];
				size_t j = i;
				//skip over the gap
				if (!erase)
					for (; j < new_cap && j < i + gap && j < this->len; j++) {}
				else
					for (; i < this->len && i < j + gap; i++) {}
				//copy over the remainder
				for (; j < new_cap && i < this->len; i++, j++)
					newData[j] = this->data[i];
				delete [] this->data;
				this->data = newData;
				this->cap = new_cap;
				if (this->len > new_cap)
					this->len = new_cap;
			}
	};

	template <class T>
	void	swap(vector<T>& x, vector<T>& y)
	{
		return (x.swap(y));
	}

}

#endif
