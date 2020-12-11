/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traits.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/21 10:10:41 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/12/11 21:42:23 by tbruinem      ########   odam.nl         */
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
}

//are_same
namespace ft
{
	template <typename, typename>
	struct are_same
	{
		static const bool result = false;
	};

	template <typename T>
	struct are_same<T, T>
	{
		static const bool result = true;
	};
}

//is_iterator
namespace ft
{
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

	template <>
	struct is_iterator<ft::bidirectional_iterator_tag>
	{
		static const bool result = true;
	};
}

#endif
