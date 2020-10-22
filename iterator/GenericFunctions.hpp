/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   GenericFunctions.hpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 14:37:01 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/22 14:39:03 by tbruinem      ########   odam.nl         */
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
}

#endif
