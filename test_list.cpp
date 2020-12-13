/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_list.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 14:16:22 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/12/13 22:30:10 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <test_header.hpp>
#include <IteratorFunctions.hpp>
#include <List.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class verbose
{
	private:
		int val;
	public:
		verbose() : val(0) { std::cout << "DEFAULT CONSTRUCT" << std::endl; }
		verbose(int val) : val(val) { std::cout << "VALUE CONSTRUCT" << std::endl; }
		verbose(const verbose& other) : val(other.val) { std::cout << "COPY CONSTRUCT" << std::endl; }
		verbose& operator = (const verbose& other) { val = other.val; std::cout << "ASSIGNMENT" << std::endl; return (*this); }
		~verbose() { std::cout << "DESTRUCT" << std::endl; }
		int get() const { return this->val; }
};

std::ostream& operator << (std::ostream& stream, const verbose& object) { stream << object.get(); return (stream); }

bool	int_is_2(const int& number) { return (number == 2); }

template <class T>
void	bidirectional_iterator_comparison(T a, T b, std::string a_title, std::string b_title)
{
	std::cout << a_title << " operator == " << b_title << " = " << ((a == b) ? "True" : "False") << std::endl;
	std::cout << a_title << " operator != " << b_title << " = " << ((a != b) ? "True" : "False") << std::endl;
	std::cout << "---" << std::endl;
	std::cout << b_title << " operator == " << a_title << " = " << ((b == a) ? "True" : "False") << std::endl;
	std::cout << b_title << " operator != " << a_title << " = " << ((b != a) ? "True" : "False") << std::endl;
}

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
	const list<int> list_const(list_range);
	const_iter_print_container(list_const, "list_const");

	list_copy = list_range;
	iter_print_container(list_copy, "list_copy");

	subject_title("ITERATORS");

	iter_print_container(list_copy, "list_copy");
	reverse_iter_print_container(list_copy, "list_copy");

	const_iter_print_container(list_const, "list_const");
	const_reverse_iter_print_container(list_const, "list_const");

	subject_title("CAPACITY");

	iter_print_container(list_copy, "list_copy");
	std::cout << "list_copy" << " is empty? " << (list_copy.empty() ? "TRUE" : "FALSE") << std::endl;
	std::cout << "list_copy" << " size is: " << list_copy.size() << std::endl;
	list_copy.clear();
	std::cout << "list_copy" << " is empty? " << (list_copy.empty() ? "TRUE" : "FALSE") << std::endl;
	std::cout << "list_copy" << " size is: " << list_copy.size() << std::endl;
	std::cout << "list" << " max size: " << list_copy.max_size() << std::endl;
	list_copy.push_back(10);
	list_copy.push_front(0);
	iter_print_container(list_copy, "list_copy");

	subject_title("ELEMENT ACCESS");

	std::cout << "list_copy" << " front: " << list_copy.front() << std::endl;
	std::cout << "list_copy" << " back: " << list_copy.back() << std::endl;
	list_copy.pop_front();
	list_copy.pop_back();
	iter_print_container(list_copy, "list_copy");
	//list_copy.pop_back(); //this segfaults on STL list
	//list_copy.pop_front(); //this segfaults on STL list

	subject_title("MODIFIERS");

	iter_print_container(list_range, "list_range");
	list_copy.assign(list_range.begin(), list_range.end());
	iter_print_container(list_copy, "list_copy");
	list_copy.assign(3, 42);
	iter_print_container(list_copy, "list_copy");
	list<int>::iterator it = list_copy.begin();
	for (size_t i = 0; i < 2; i++) {it++; }
	list_copy.insert(it, 5);
	iter_print_container(list_copy, "list_copy");
	list_copy.insert(it, 0);
	iter_print_container(list_copy, "list_copy");
	list_copy.insert(it, 5, 1);
	iter_print_container(list_copy, "list_copy");
	list_fill = list<int>(10, 2);
	iter_print_container(list_fill, "list_fill");
	list_copy.insert(it, list_fill.begin(), list_fill.end());
	iter_print_container(list_copy, "list_copy");
	list_copy.erase(list_copy.begin(), it);
	iter_print_container(list_copy, "list_copy");
	it = list_copy.erase(it);
	std::cout << "list<int>::iterator 'it'" << " is equal to end(): " << (it == list_copy.end() ? "TRUE" : "FALSE") << std::endl;
	iter_print_container(list_copy, "list_copy");
	iter_print_container(list_fill, "list_fill");
	iter_print_container(list_range, "list_range");
	list_fill.swap(list_range);
	iter_print_container(list_fill, "list_fill");
	iter_print_container(list_range, "list_range");
	list_range.resize(5);
	iter_print_container(list_range, "list_range");
	list_range.resize(10);
	iter_print_container(list_range, "list_range");
	list_range.resize(0);
	iter_print_container(list_range, "list_range");

	subject_title("OPERATIONS");

	list<verbose> list_verbose1(5, 10);
	list<verbose> list_verbose2(5, 5);
	iter_print_container(list_verbose1, "list_verbose1");
	iter_print_container(list_verbose2, "list_verbose2");
	subject_title("START OF SPLICE");
	list_verbose2.splice(++(list_verbose2.begin()), list_verbose1);
	subject_title("END OF SPLICE");
	iter_print_container(list_verbose2, "list_verbose2");
	iter_print_container(list_verbose1, "list_verbose1");
	list_verbose2.clear();
	list<verbose>	list_single(2,1);
	iter_print_container(list_single, "list_single");
	list_verbose2.splice(list_verbose2.begin(), list_single, list_single.begin());
	iter_print_container(list_verbose2, "list_verbose2");
	iter_print_container(list_single, "list_single");
	list<verbose>	list_multiple(5, 3);
	list<verbose>	list_verbose3;
	iter_print_container(list_multiple, "list_multiple");
	list_verbose3.splice(list_verbose3.begin(), list_multiple, ++(list_multiple.begin()), --(list_multiple.end()));
	iter_print_container(list_verbose3, "list_verbose3");
	iter_print_container(list_multiple, "list_multiple");
	list_verbose1.clear();
	list_verbose2.clear();
	list_verbose3.clear();
	list_multiple.clear();
	list_single.clear();

	list<int>	list_remove(10, 3);

	size_t i = 0;
	for (list<int>::iterator it = list_remove.begin(); it != list_remove.end(); it++)
	{
		*it += (i % 3 == 0);
		i++;
	}
	i = 0;
	iter_print_container(list_remove, "list_remove");
	list_remove.remove(4);
	iter_print_container(list_remove, "list_remove");
	for (list<int>::iterator it = list_remove.begin(); it != list_remove.end(); it++)
	{
		*it -= (i % 2 == 0);
		i++;
	}
	iter_print_container(list_remove, "list_remove");
	list_remove.remove_if(int_is_2);
	iter_print_container(list_remove, "list_remove");

	srand(time(NULL));
	list<int>	list_sort;

	for (size_t i = 0; i < 10; i++)
	{
		list_sort.push_back(rand() % 15);
	}
	iter_print_container(list_sort, "list_sort");
	list<int>	list_partial;
	list<int>::iterator list_sort_it = list_sort.begin();
	for (size_t i = 0; i < list_sort.size() / 2; i++)
		list_sort_it++;
	list_partial.splice(list_partial.begin(), list_sort, list_sort.begin(), list_sort_it);
	iter_print_container(list_partial, "list_partial");
	iter_print_container(list_sort, "list_sort");
	list_sort.sort();
	list_partial.sort();
	iter_print_container(list_partial, "list_partial");
	iter_print_container(list_sort, "list_sort");
	list_sort.merge(list_partial);
	iter_print_container(list_sort, "list_sort");
	list_sort.remove(6);
	std::cout << "LIST_SORT AFTER REMOVING '6':\n";
	iter_print_container(list_sort, "list_sort");
	list_sort.reverse();
	iter_print_container(list_sort, "list_sort");
	list<int>	list_reverse;
	list_reverse.push_back(1);
	list_reverse.push_back(2);
	iter_print_container(list_reverse, "list_reverse");
	list_reverse.reverse();
	iter_print_container(list_reverse, "list_reverse");

	subject_title("SWAP");

	list_copy.push_back(42);
	list_default.push_back(404);
	iter_print_container<list<int> >(list_copy, "list_copy");
	iter_print_container<list<int> >(list_default, "list_default");
	swap(list_copy, list_default);
	iter_print_container<list<int> >(list_copy, "list_copy");
	iter_print_container<list<int> >(list_default, "list_default");

	subject_title("OPERATOR OVERLOAD");

	comparison_operator_container<list<int> >(list_copy, list_default, "list_copy", "list_default");
	list<int>::iterator list_copy_it = list_copy.begin();
	for (size_t i = 0; i < list_copy.size(); i++)
		list_copy_it++;
	bidirectional_iterator_comparison(list_copy_it, list_copy.end(), "list_copy::begin + size()", "list_copy::end"); 

	return (0);
}
