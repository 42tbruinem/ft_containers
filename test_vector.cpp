/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_vector.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 19:16:57 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/01 11:55:34 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <IteratorFunctions.hpp>
#include <test_header.hpp>

#include <vector>

int	main(void)
{
	print_version();

	container_header("VECTOR");

	//Constructors
	subject_title("CONSTRUCTORS");

	vector<int>	vec_default;
	vector<int> vec_fill(100, 5);
	vector<int> vec_range(vec_fill.begin(), vec_fill.begin() + 5);
	vector<int> vec_copy(vec_fill);
	iter_print_container<vector<int> >(vec_default, "vec_default");
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	iter_print_container<vector<int> >(vec_range, "vec_range");
	iter_print_container<vector<int> >(vec_copy, "vec_copy");

	//Modifiers
	subject_title("MODIFIERS");

	vec_default.push_back(5);
	vec_default.pop_back();
//	capacity_information<vector<int> >(vec_fill, "vec_fill");
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	vec_fill.assign(5, 10);
//	capacity_information<vector<int> >(vec_fill, "vec_fill");
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	vec_fill.assign(vec_copy.begin(), vec_copy.end());
//	double myints[] = {178.25,234.13,25.435234};
	vector<double> vec_double(5, 29.9995949494949);
//	vector<std::string> vec_double(5, "abc");
	vec_fill.assign(vec_double.begin(), vec_double.end());
	iter_print_container<vector<int> >(vec_fill, "vec_fill from doubles");
//	capacity_information<vector<int> >(vec_fill, "vec_fill");
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	vec_fill.insert(vec_fill.begin(), 99);
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	vec_fill.insert(vec_fill.begin() + 2, 1);
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	vec_fill.insert(vec_fill.end(), -10);
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	vec_fill.insert(vec_fill.end(), 5, 100);
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	vec_fill.insert(vec_fill.begin(), 5, 0);
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	vector<int> vec_for_insert(3, -20);
	vec_fill.insert(vec_fill.begin(), vec_for_insert.begin(), vec_for_insert.end());
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	vec_fill.insert(vec_fill.begin() + 5, vec_for_insert.begin(), vec_for_insert.end());
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	vec_fill.insert(vec_fill.end(), vec_for_insert.begin(), vec_for_insert.end());
	iter_print_container<vector<int> >(vec_fill, "vec_fill");

	vector<int>::iterator vec_copy_begin = vec_copy.begin();
	vector<int>::iterator vec_fill_begin = vec_fill.begin();
	iter_print_container<vector<int> >(vec_fill, "vec_fill");
	iter_print_container<vector<int> >(vec_copy, "vec_copy");
	vec_fill.swap(vec_copy);
	std::cout << "SWAPPED 'vec_copy' AND 'vec_fill'" << std::endl;
	std::cout << "vec_copy begin: " << *vec_copy_begin << std::endl;
	std::cout << "vec_fill begin: " << *vec_fill_begin << std::endl;
	iter_print_container<vector<int> >(vec_copy, "vec_copy");
	iter_print_container<vector<int> >(vec_copy, "vec_copy");
	vec_copy.erase(vec_copy.begin());
	iter_print_container<vector<int> >(vec_copy, "vec_copy");
	vec_copy.erase(vec_copy.end() - 5, vec_copy.end());
	iter_print_container<vector<int> >(vec_copy, "vec_copy");
	vector<int> vec_fill_big(1000000, 10);
	capacity_information<vector<int> >(vec_fill_big, "vec_fill_big");
	vec_fill_big.clear();
	capacity_information<vector<int> >(vec_fill_big, "vec_fill_big");
	vec_fill_big.resize(1000000, 10);

	//Capacity
	subject_title("CAPACITY");

	std::cout << "Max Size of " << "vector" << " is " << vec_default.max_size() << std::endl;

	std::cout << "vec_default" << " is empty? " << (vec_default.empty() ? "TRUE" : "FALSE") << std::endl;
	vec_default.push_back(5);
	std::cout << "vec_default" << " is empty? " << (vec_default.empty() ? "TRUE" : "FALSE") << std::endl;
	vec_default.pop_back();
	vec_default.push_back(1);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.reserve(0);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.reserve(1);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.reserve(5);
	capacity_information<vector<int> >(vec_default, "vec_default");

	std::cout << std::endl;

	capacity_information<vector<int> >(vec_fill_big, "vec_fill_big");
	vec_fill_big.reserve(5000000);
	capacity_information<vector<int> >(vec_fill_big, "vec_fill_big");
	vec_fill_big.resize(5000000);
	capacity_information<vector<int> >(vec_fill_big, "vec_fill_big");
	vec_fill_big.push_back(5);
	capacity_information<vector<int> >(vec_fill_big, "vec_fill_big");

	//Iterators
	subject_title("ITERATORS");

	for (vector<int>::iterator it = vec_range.begin(); it != vec_range.end(); it++)
		*it = ft::distance(vec_range.begin(), it);

	iter_print_container<vector<int> >(vec_range, "vec_range");
	reverse_iter_print_container<vector<int> >(vec_range, "vec_range");

	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.resize(3);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.resize(0);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.push_back(5);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.push_back(5);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.push_back(5);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.push_back(5);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.push_back(5);
	capacity_information<vector<int> >(vec_default, "vec_default");
	vec_default.push_back(5);
	vec_default.push_back(5);
	vec_default.push_back(5);
	vec_default.push_back(5);
	vec_default.push_back(5);
	vec_default.push_back(5);
	vec_default.push_back(5);
	vec_default.push_back(5);
	capacity_information<vector<int> >(vec_default, "vec_default");

	vector<int> vec_size(100);
	capacity_information<vector<int> >(vec_size, "vec_size");
	capacity_information<vector<int> >(vec_fill, "vec_fill");
	vec_fill.pop_back();
	capacity_information<vector<int> >(vec_fill, "vec_fill");

	vec_default.resize(20);
	capacity_information<vector<int> >(vec_default, "vec_default");
	iter_print_container<vector<int> >(vec_default, "vec_default");

	//Element Access
	vector<int> const vec_const(5, 10);
	subject_title("ELEMENT ACCESS");

	operator_print_container<vector<int> >(vec_default, "vec_default");
	const_operator_print_container<vector<int> >(vec_const, "vec_const");

	iter_print_container<vector<int> >(vec_copy, "vec_copy");
	iter_print_container<vector<int> >(vec_default, "vec_default");
	const_iter_print_container<vector<int> >(vec_copy, "vec_copy");
	const_iter_print_container<vector<int> >(vec_default, "vec_default");
	reverse_iter_print_container<vector<int> >(vec_copy, "vec_copy");
	reverse_iter_print_container<vector<int> >(vec_copy, "vec_default");
	const_reverse_iter_print_container<vector<int> >(vec_copy, "vec_copy");
	const_reverse_iter_print_container<vector<int> >(vec_copy, "vec_default");
	subject_title("SWAP");

	swap(vec_copy, vec_default);
	iter_print_container<vector<int> >(vec_copy, "vec_copy");
	iter_print_container<vector<int> >(vec_default, "vec_default");

	subject_title("OPERATOR OVERLOAD");

	comparison_operator_container<vector<int> >(vec_copy, vec_default, "vec_copy", "vec_default");
	comparison_operator_container<vector<int>::iterator>(vec_copy.begin() + vec_copy.size(), vec_copy.end(), "vec_copy::begin + size()", "vec_copy::end"); 

	return (0);
}
