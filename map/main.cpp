/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 13:50:22 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/18 17:09:57 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"
#include <string>
#include <iostream>

int main(void)
{
	ft::map<std::string, size_t>	container;

	container["y"] = 24;
//	std::cout << "------" << std::endl;
	container["c"] = 4;
	container["z"] = 25;
	container["a"] = 1;
	container["b"] = 3;

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
		std::cout << it->first << " : " << it->second << std::endl;
//		sleep(1);
	}
	return (0);
}
