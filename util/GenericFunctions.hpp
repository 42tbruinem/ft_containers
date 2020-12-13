/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   GenericFunctions.hpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 14:37:01 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/12/13 21:32:53 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERIC_FUNCTIONS_HPP
# define GENERIC_FUNCTIONS_HPP

namespace ft
{
	template <typename T>
	void	swap(T& a, T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	template <typename InputIterator>
	bool	lexicographical_compare(InputIterator begin1, InputIterator begin2, InputIterator end1, InputIterator end2)
	{
		for (; begin1 != end1 && begin2 != end2; begin1++, begin2++)
		{
			if (*begin2 < *begin1)
				return (false);
			else if (*begin1 < *begin2)
				return (true);
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
