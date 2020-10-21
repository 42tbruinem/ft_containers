/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traits.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/21 10:10:41 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/21 10:39:06 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAITS_HPP
 #define TRAITS_HPP

//tags
namespace ft
{
	struct input_iterator_tag { };

	struct output_iterator_tag { };

	struct forward_iterator_tag : public input_iterator_tag { };

	struct bidirectional_iterator_tag : public forward_iterator_tag { };

	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
}

//enable_if
namespace ft
{
	template <bool value, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <typename T>
	struct is_iterator
	{
		static const bool result = false;
	};

	template <>
	struct is_iterator<ft::random_access_iterator_tag>
	{
		static const bool result = true;
	};
}

#endif
