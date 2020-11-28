/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_list.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 14:16:22 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/11/28 15:47:35 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <test_header.hpp>
#include <IteratorFunctions.hpp>
#include <List.hpp>

int main(void)
{
	print_version();

	subject_title("CONSTRUCTORS");

	list<int> list_default;
	list<int> list_fill(10, 5);
	list<int> list_range(list_fill.begin(), list_fill.end());
	list<int> list_copy(list_range);

	iter_print_container(list_default, "list_default");
	iter_print_container(list_fill, "list_fill");
	iter_print_container(list_range, "list_range");
	list_copy.pop_back();
	list_copy.pop_back();
	list_copy.pop_back();
	list_copy.push_front(10);
	iter_print_container(list_copy, "list_copy");
	list_copy.pop_front();
	iter_print_container(list_copy, "list_copy");
	list_copy.clear();
	iter_print_container(list_copy, "list_copy");
	return (0);
}
