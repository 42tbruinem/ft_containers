/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_queue.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/30 13:08:51 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/05/01 17:31:54 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <test_header.hpp>
#include <iostream>
#include <string>
#include "Queue.hpp"
#include <stdlib.h>

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
void	init_queue_random(queue<Value>& c, size_t amount)
{
	for (size_t i = 0; i < amount; i++)
		c.push(generate_key<Value>());
}

void	init_queue_incremental(queue<int>& c, size_t amount)
{
	for (size_t i = 0; i < amount; i++)
		c.push(i);
}

template <class Container>
void	queue_print(const Container& c, std::string title, std::string delim = ",")
{
	Container copy(c);

	std::cout << "Printing " << title << " of size " << c.size() << std::endl;

	for (; copy.size();)
	{
		print_content(copy.front());
		copy.pop();
		std::cout << (copy.empty() ? "\n" : delim); 
	}
}

template <class Container>
void	empty_queue(Container& c)
{
	while (!c.empty())
		c.pop();
}

template <class Container>
void	queue_info(const Container& c, std::string title)
{
	std::cout << "Size of " << title << " is " << c.size() << std::endl;
}

int main(void)
{
	print_version();
	container_header("QUEUE");

	subject_title("CONSTRUCTORS");

	queue<int>		queue_default;
//	init_queue_random(queue_default, 30);
	init_queue_incremental(queue_default, 30);
	queue<int>		queue_copy(queue_default);

	queue<int>		queue_assigned = queue_default;

	subject_title("ELEMENT ACCESS");

	queue_print(queue_default, "queue_default");
	queue_print(queue_copy, "queue_copy");
	queue_print(queue_assigned, "queue_assigned");

	subject_title("CAPACITY");

	queue_print(queue_default, "queue_default");
	queue_info(queue_default, "queue_default");
	is_empty(queue_default, "queue_default");
	empty_queue(queue_default);
	is_empty(queue_default, "queue_default");
	queue_info(queue_default, "queue_default");
	queue_print(queue_default, "queue_default");
	
	subject_title("MODIFIERS");

	queue_copy.push(50);
//	queue_default.pop();
	queue_print(queue_default, "queue_default");
	queue_print(queue_copy, "queue_copy");
	
	subject_title("SWAP");

	ft::swap(queue_copy, queue_default);
	queue_print(queue_default, "queue_default");
	queue_print(queue_copy, "queue_copy");

	subject_title("COMPARISON OPERATORS");

	comparison_operator_container(queue_default, queue_copy, "queue_default", "queue_copy");
}
