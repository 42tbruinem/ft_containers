/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 13:50:22 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/24 00:28:31 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <IteratorFunctions.hpp>
#include <test_header.hpp>

int main(void)
{
	print_version();

	map<std::string, size_t>	container;
	std::vector<std::string> strings = {
		"aa",
		"a",
		"za",
		"zb",
		"c",
		"b",
		"y",
		"hoi",
		"ab",
	};

	container["aa"] = 1;
	container["a"] = 100;
	container["za"] = 25;
	container["zb"] = 26;
	container["c"] = 4;
	container["b"] = 3;
	container["y"] = 24;

	std::cout << container["a"] << std::endl;
	std::cout << container["hoi"] << std::endl;
	std::cout << container["z"] << std::endl;
	std::cout << container["b"] << std::endl;
	std::cout << container["y"] << std::endl;
	std::cout << container["c"] << std::endl;

	std::cout << container["ab"] << std::endl;
	container["ab"] = 2;
	std::cout << container["ab"] << std::endl;

	std::cout << std::endl;

	for (map<std::string, size_t>::iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << "ITERATE: " << it->first << " : " << it->second << std::endl;
	}
	// container.info();
	// container.erase("aa");
	// auto test = container.find("a");
	// std::cout << ((test == container.end()) ? "True" : "False") << std::endl;
	// container.erase("a");
	// container.info();
	// for (map<std::string, size_t>::iterator it = container.begin(); it != container.end(); it++)
	// {
	// 	std::cout << it->first << " : " << it->second << std::endl;
	// 	sleep(1);
	// }
	container.erase("a");
	container.clear();

	container["a"] = 5;
	for (size_t i = 0; i < strings.size(); i++)
		container[std::string(strings[i])] = i;
	for (map<std::string, size_t>::iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
//		sleep(1);
	}
	container.erase("a");
	container.erase("a");
	map<std::string, size_t>::iterator it = container.find("a");
	std::cout << "returned iterator == to end() ? " << ((it == container.end()) ? "True" : "False") << std::endl;
	map<std::string, size_t>	container2(container);
	for (auto it = container2.begin(); it != container2.end(); it++)
		std::cout << "Key: " << it->first << " | Val: " << it->second << std::endl;

	const map<std::string, size_t>	container3(container2);
	for (auto it = container3.begin(); it != container3.end(); it++)
		std::cout << "Const Key: " << it->first << " | Val: " << it->second << std::endl;

	map<std::string, size_t>::const_iterator const_it(container2.begin());
	const_it++;
	std::cout << const_it->first << std::endl;
// 	return (0);
}
