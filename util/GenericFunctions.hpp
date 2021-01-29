/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   GenericFunctions.hpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 14:37:01 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/29 19:59:48 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERIC_FUNCTIONS_HPP
# define GENERIC_FUNCTIONS_HPP

namespace ft
{
	template<typename _Arg1, typename _Arg2, typename _Result>
	struct binary_function
	{
		typedef _Arg1 	first_argument_type; 
		typedef _Arg2 	second_argument_type;
		typedef _Result 	result_type;
	};

	template <typename T>
	void	swap(T& a, T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

// 	template <class T1, class T2>
// 	class pair
// 	{
// 		public:
// 			pair(const T1& first = T1(), const T2& second = T2()) : first(first), second(second) {}
// 			pair(const pair& other) { *this = other; }
// //			template <class U1, class U2>
// //			pair(const pair<U1, U2>& other) : first(other.first), second(other.second) {}
// 			pair& operator = (const pair& other)
// 			{
// 				if (this != &other)
// 				{
// 					this->first = other.first;
// 					this->second = other.second;
// 				}
// 				return (*this);
// 			}
// 			~pair() {}
// 			T1	first;
// 			T2	second;
// 	};

	template <typename InputIt1, typename InputIt2, typename Compare>
	bool	lexicographical_compare(InputIt1 begin1, InputIt2 begin2, InputIt1 end1, InputIt2 end2, Compare comp)
	{
		for (; begin1 != end1 && begin2 != end2; begin1++, begin2++)
		{
			if (comp(*begin1, *begin2))
				return (true);
			if (comp(*begin2, *begin1))
				return (false);
		}
		return (begin2 != end2);
	}

	template <class T>
	class less
	{
		public:
			inline bool operator()(const T &lhs, const T &rhs) const 
			{
				return lhs < rhs;
			}
	};

	template <typename InputIt1, typename InputIt2>
	bool	lexicographical_compare(InputIt1 begin1, InputIt2 begin2, InputIt1 end1, InputIt2 end2)
	{
		for (; begin1 != end1 && begin2 != end2; begin1++, begin2++)
		{
			if (*begin1 < *begin2)
				return (true);
			if (*begin2 < *begin1)
				return (false);
		}
		return (begin2 != end2);
	}

	template <class Iterator1, class Iterator2>
	bool equal(Iterator1 first1, Iterator1 last1, Iterator2 first2)
	{
		for (;first1 != last1; first1++, first2++)
		{
			if (!(*first1 == *first2))
				return false;
		}
		return true;
	}
}

#endif
