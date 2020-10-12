/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   IteratorFunctions.hpp                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/11 20:15:39 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/11 20:19:17 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_FUNCTIONS_HPP
# define ITERATOR_FUNCTIONS_HPP

#include <cstddef>

namespace ft
{
	template <class InputIterator>
	size_t	distance(InputIterator first, InputIterator last)
	{
		size_t n = 0;
		while (first != last)
		{
			n++;
			first++;
		}
		return (n);
	}
}

#endif
