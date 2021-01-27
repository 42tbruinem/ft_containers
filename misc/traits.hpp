/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traits.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/21 10:10:41 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/27 12:08:19 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAITS_HPP
 #define TRAITS_HPP

# include <stdlib.h>

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


//------------------------------------------------------------------

namespace ft
{
	//add category if pointer

	//check if input_iterator

	//see if iterator_category is defined

	template<typename T>
	struct has_category
	{
		private:
			typedef int false_type;
			typedef char true_type;
			template <typename V>
			false_type test(...);
			template <typename V>
			true_type test( typename V::iterator_category* = NULL);
		public:
			static const bool result = sizeof(test<T>(0)) == sizeof(true_type);
	};

	template <typename T, bool>
	struct _is_iterator {};

	template <typename T>
	struct _is_iterator<T, true>
	{
		typedef typename T::iterator_category	iterator_category;
	};

	template <typename T>
	struct get_category : public _is_iterator<T, has_category<T>::result> {};

	template <typename T>
	struct get_category<T*>
	{
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct get_category<const T*>
	{
		typedef ft::random_access_iterator_tag	iterator_category;
	};
}

#endif
