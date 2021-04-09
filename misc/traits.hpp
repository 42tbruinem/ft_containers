/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traits.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/21 10:10:41 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/09 12:42:57 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAITS_HPP
 #define TRAITS_HPP

//# include <stdlib.h>

//tags
namespace ft
{
	struct input_iterator_tag { };

	struct output_iterator_tag { };

	struct forward_iterator_tag : public input_iterator_tag { };

	struct bidirectional_iterator_tag : public forward_iterator_tag { };

	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
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

//-----------------------------------ENABLE_IF---------------------------------------------

namespace ft
{
	template <bool, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T> { typedef T type; };
}

//------------------------------------HAS_ITERATOR_CATEGORY------------------------------------------------

namespace ft
{
	template <class T>
	struct has_iterator_category
	{
		private:
			typedef char		true_type;
			typedef int			false_type;

			template <class U>
				static true_type	test(typename U::iterator_category* = 0);
			template <class U>
				static false_type	test(...);
		public:
			static const bool result = (sizeof(true_type) == sizeof(test<T>(0)));
	};
}

//-------------------------------------ITERATOR_TRAITS-----------------------------------------------

namespace ft
{
	template <typename T>
	struct iterator_traits : public enable_if<has_iterator_category<T>::result, T> {};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag type;
	};
}

#endif
