/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/06 19:28:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/09 18:33:19 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "RandomAccessIterator.hpp"
# include "ReverseRandomAccessIterator.hpp"
# include "GenericFunctions.hpp"
# include "IteratorFunctions.hpp"
# include "traits.hpp"

# include <cmath>
# include <cstddef>
# include <stdexcept>
# include <memory>

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class	vector
	{
		public:
			typedef	T												value_type;
			typedef Alloc											allocator_type;
			typedef	T&												reference;
			typedef const T&										const_reference;
			typedef T*												pointer;
			typedef const T*										const_pointer;
			typedef RandomAccessIterator<T*, T&>					iterator;
			typedef RandomAccessIterator<const T*, const T&>		const_iterator;
			typedef ReverseRandomAccessIterator<T*, T&>				reverse_iterator;
			typedef ReverseRandomAccessIterator<const T*, const T&>	const_reverse_iterator;
			typedef ptrdiff_t										difference_type;
			typedef size_t											size_type;

//-------------------------------------------------------CONSTRUCTOR-----------------------------------------------------

			//DEFAULT
			vector(const Alloc& alloc = Alloc()) : data(NULL), cap(0), len(0), alloc(alloc) {}
			//FILL
			vector(size_t n, const T& val = T(), const Alloc& alloc = Alloc()) : data(NULL), cap(0), len(0), alloc(alloc)
			{
				if (!n)
					return ;
				this->assign(n, val);
			}
			//RANGE
			template <typename InputIterator>
			vector(InputIterator first, InputIterator last,
				typename ft::iterator_traits<InputIterator>::type* = NULL,
				const Alloc& alloc = Alloc()) : data(NULL), cap(0), len(0), alloc(alloc)
			{
				size_t	n;

				n = ft::distance(first, last);
				if (!n)
					return ;
				this->assign(first, last);
			}
			//COPY
			vector(const vector& other) : data(NULL), cap(0), len(0), alloc(other.alloc)
			{
				*this = other;
			}

//-------------------------------------------------------OPERATOR-----------------------------------------------------

			vector& operator = (const vector& other)
			{
				if (this != &other)
					this->assign(other.begin(), other.end());
				return (*this);
			}

//-------------------------------------------------------DECONSTRUCTOR-----------------------------------------------------

			~vector()
			{
				this->clear();
			}

//-------------------------------------------------------ITERATORS-----------------------------------------------------

			iterator	begin()
			{
				return (iterator(this->data));
			}
			const_iterator	begin() const
			{
				return (const_iterator(this->data));
			}

			iterator	end()
			{
				return (iterator(this->data + this->len));
			}
			const_iterator	end() const
			{
				return (const_iterator(this->data + this->len));
			}

			reverse_iterator	rbegin()
			{
				return (reverse_iterator(this->data + this->len - 1));
			}
			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(this->data + this->len - 1));
			}

			reverse_iterator	rend()
			{
				return (reverse_iterator(this->data - 1));
			}
			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(this->data - 1));
			}

//-------------------------------------------------------CAPACITY-----------------------------------------------------

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
				if (n == this->len)
					return ;
				if (n < this->len)
					this->erase(this->end() - (this->len - n), this->end());
				else
					this->insert(this->end(), n - this->len, val);
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
				if (this->cap >= n)
					return ;
				T*			data;
				size_type	capacity;

				capacity = this->cap;
				data = this->data;

				this->cap = calc_capacity(n);
				this->data = alloc.allocate(this->cap);
				for (size_t i = 0; i < this->len; i++)
				{
					alloc.construct(&this->data[i], data[i]);
					alloc.destroy(&data[i]);
				}
				alloc.deallocate(data, capacity);
			}

//-------------------------------------------------------ELEMENT ACCESS-----------------------------------------------------

			T& operator [] (size_t index)
			{
				return (this->data[index]);
			}
			const T& operator [] (size_t index) const
			{
				return (this->data[index]);
			}

			T&	at(size_t n)
			{
				if (n >= this->len)
					throw std::out_of_range("Error: requested index is out of range");
				return (this->data[n]);
			}
			const T&	at(size_t n) const
			{
				if (n >= this->len)
					throw std::out_of_range("Error: requested index is out of range");
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

//-------------------------------------------------------MODIFIERS-----------------------------------------------------

			//RANGE
			template <typename InputIterator>
			void	assign(InputIterator first, InputIterator last,
				typename ft::iterator_traits<InputIterator>::type* = NULL)
			{
				size_t	dist = ft::distance(first, last);
				this->clear();
				this->reserve(dist);
				this->insert(this->begin(), first, last);
			}
			//FILL
			void	assign(size_t n, const T& val)
			{
				this->clear();
				this->reserve(n);
				this->insert(this->begin(), n, val);
			}
			void	push_back(const T& val)
			{
				if (this->len >= this->cap)
					this->reserve((this->cap * 2) + !this->cap);
				alloc.construct(&data[this->len], val);
				this->len++;
			}
			void	pop_back()
			{
				if (!this->len)
					return ;
				alloc.destroy(&this->data[this->len - 1]);
				this->len--;
			}
			//SINGLE ELEMENT
			iterator	insert(iterator position, const T& val)
			{
				this->insert(position, 1, val);
				return (position);
			}
			//FILL
			void	insert(iterator position, size_t n, const T& val)
			{
				if (!n)
					return ;
				size_t	dist = ft::distance(this->begin(), position);
				while (this->len + n >= this->cap)
					this->reserve((this->cap * 2) + !this->cap);

				size_t i;
				for (i = this->len + n; i >= dist + n; i--)
				{
					alloc.construct(&this->data[i], this->data[i - n]);
					alloc.destroy(&this->data[i - n]);
				}
				for (size_t i = 0; i < n; i++)
				{
					alloc.construct(&this->data[dist + i], val);
				}
				this->len += n;
			}
			//RANGE
			template <typename InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last,
				typename ft::iterator_traits<InputIterator>::type* = NULL)
			{
				size_t	n = ft::distance(first, last);
				if (!n)
					return ;
				size_t	dist = ft::distance(this->begin(), position);
				while (this->len + n >= this->cap)
					this->reserve((this->cap * 2) + !this->cap);

				size_t i;
				for (i = this->len + n; i >= dist + n; i--)
				{
					alloc.construct(&this->data[i], this->data[i - n]);
					alloc.destroy(&this->data[i - n]);
				}
				for (size_t i = 0; i < n && first != last; i++, first++)
					alloc.construct(&this->data[dist + i], *first);
				this->len += n;
			}

			//SINGLE ELEMENT
			iterator	erase(iterator position)
			{
				return (this->erase(position, position + 1));
			}
			//RANGE
			iterator	erase(iterator first, iterator last)
			{
				size_t	pos = ft::distance(begin(), first);
				size_t	dist = ft::distance(first, last);
				if (pos > this->len || pos + dist > this->len)
					throw std::out_of_range("Error: supplied vector iterators are out of range");
				for (size_t i = 0; i < dist; i++)
					alloc.destroy(&this->data[pos + i]);
				for (size_t i = 0; i + pos < this->len; i++)
				{
					alloc.construct(&this->data[pos + i], this->data[pos + i + dist]);
					alloc.destroy(&this->data[pos + i + dist]);
				}
				this->len -= dist;
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
				for (size_t i = 0; i < this->len; i++)
					alloc.destroy(&this->data[i]);
				this->len = 0;
				alloc.deallocate(this->data, this->cap);
				this->cap = 0;
				this->data = NULL;
			}

		private:
			T		*data;
			size_t	cap;
			size_t	len;
			Alloc	alloc;

//-------------------------------------------------------PRIVATE FUNCTIONS-----------------------------------------------------

			size_type calc_capacity(size_type size)
			{
				return((size_type)pow(2, ceil(log2(size))));
			}
	};

//-------------------------------------------------------RELATIONAL OPERATORS-----------------------------------------------------

	template<class T>
	bool	operator == (vector<T>& src, vector<T>& other)
	{
		if (src.size() != other.size())
			return (false);
		return (ft::equal(src.begin(), src.end(), other.begin()));
	}
	template<class T>
	bool	operator != (vector<T>& src, vector<T>& other)
	{
		return !(src == other);
	}
	template<class T>
	bool	operator < (vector<T>& src, vector<T>& other)
	{
		return (ft::lexicographical_compare(src.begin(), other.begin(), src.end(), other.end()));
	}
	template<class T>
	bool	operator > (vector<T>& src, vector<T>& other)
	{
		return (other < src);
	}
	template<class T>
	bool	operator >= (vector<T>& src, vector<T>& other)
	{
		return !(src < other);
	}
	template<class T>
	bool	operator <= (vector<T>& src, vector<T>& other)
	{
		return !(other < src);
	}

	template <class T>
	void	swap(vector<T>& x, vector<T>& y)
	{
		return (x.swap(y));
	}

}

#endif
