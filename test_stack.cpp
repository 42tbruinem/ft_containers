/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_stack.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/30 13:08:51 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/30 14:08:52 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <test_header.hpp>
#include <iostream>
#include <string>
#include "Stack.hpp"

template <class Type>
Type	generate_key()
{
	return (rand() % 300);
}

template <>
std::string	generate_key<std::string>()
{
	const size_t		length = 10;
	const std::string	characters("abcdefghijklmnopqrstuvwxyz");
	std::string			key(10, '\0');

	for (size_t i = 0; i < length; i++)
		key[i] = characters[rand() % characters.size()];
	return (key);
}

template <class Value>
void	init_stack_random(stack<Value>& c, size_t amount)
{
	for (size_t i = 0; i < amount; i++)
		c.push(generate_key<Value>());
}

void	init_stack_incremental(stack<int>& c, size_t amount)
{
	for (size_t i = 0; i < amount; i++)
		c.push(i);
}

template <class Container>
void	stack_print(const Container& c, std::string title, std::string delim = ",")
{
	Container copy(c);

	std::cout << "Printing " << title << " of size " << c.size() << std::endl;

	for (; copy.size();)
	{
		print_content(copy.top());
		copy.pop();
		std::cout << (copy.empty() ? "\n" : delim); 
	}
}

template <class Container>
void	empty_stack(Container& c)
{
	while (!c.empty())
		c.pop();
}

template <class Container>
void	stack_info(const Container& c, std::string title)
{
	std::cout << "Size of " << title << " is " << c.size() << std::endl;
}

int main(void)
{
	print_version();
	container_header("STACK");

	subject_title("CONSTRUCTORS");

	stack<int>		stack_default;
//	init_stack_random(stack_default, 30);
	init_stack_incremental(stack_default, 30);
	stack<int>		stack_copy(stack_default);

	stack<int>		stack_assigned = stack_default;

	subject_title("ELEMENT ACCESS");

	stack_print(stack_default, "stack_default");
	stack_print(stack_copy, "stack_copy");
	stack_print(stack_assigned, "stack_assigned");

	subject_title("CAPACITY");

	stack_print(stack_default, "stack_default");
	stack_info(stack_default, "stack_default");
	is_empty(stack_default, "stack_default");
	empty_stack(stack_default);
	is_empty(stack_default, "stack_default");
	stack_info(stack_default, "stack_default");
	stack_print(stack_default, "stack_default");
	
	subject_title("MODIFIERS");

	stack_copy.push(50);
//	stack_default.pop();
	stack_print(stack_default, "stack_default");
	stack_print(stack_copy, "stack_copy");
	
	subject_title("SWAP");

	ft::swap(stack_copy, stack_default);
	stack_print(stack_default, "stack_default");
	stack_print(stack_copy, "stack_copy");

	subject_title("COMPARISON OPERATORS");

	comparison_operator_container(stack_default, stack_copy, "stack_default", "stack_copy");
}
