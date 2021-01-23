/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 13:50:22 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/23 12:32:23 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"
#include <string>
#include <iostream>
#include <vector>

int main(void)
{
	ft::map<std::string, size_t>	container;
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

	for (ft::map<std::string, size_t>::iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << "ITERATE: " << it->first << " : " << it->second << std::endl;
	}
	// container.info();
	// container.erase("aa");
	// auto test = container.find("a");
	// std::cout << ((test == container.end()) ? "True" : "False") << std::endl;
	// container.erase("a");
	// container.info();
	// for (ft::map<std::string, size_t>::iterator it = container.begin(); it != container.end(); it++)
	// {
	// 	std::cout << it->first << " : " << it->second << std::endl;
	// 	sleep(1);
	// }
	container.erase("a");
	container.info();
	container.clear();
	container.info();

	container["a"] = 5;
	for (size_t i = 0; i < strings.size(); i++)
		container[std::string(strings[i])] = i;
	for (ft::map<std::string, size_t>::iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
//		sleep(1);
	}
// 	return (0);
}
