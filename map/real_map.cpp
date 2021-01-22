/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   real_map.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 18:50:09 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/13 12:46:37 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <utility>
#include <iostream>
#include <string>

int main(void)
{
	std::map<std::string, size_t>	mymap;
	std::pair<std::string, size_t> ids[] = {
	std::pair<std::string, size_t>("b",1),
	std::pair<std::string, size_t>("c",2),
	std::pair<std::string, size_t>("d",3),
	std::pair<std::string, size_t>("a",0),
	std::pair<std::string, size_t>("e",4),
	std::pair<std::string, size_t>("f",5),
	std::pair<std::string, size_t>("g",6),
	std::pair<std::string, size_t>("h",7),
	std::pair<std::string, size_t>("i",8),
	std::pair<std::string, size_t>("j",9)
	};

	for (size_t i = 0; i < 10; i++)
		mymap.insert(ids[i]);
	std::cout << std::endl;

	for (auto it = mymap.begin(); it != mymap.end(); it++)
		std::cout << it->second << std::endl;

	std::cout << std::endl;

	for (auto it = mymap.rbegin(); it != mymap.rend(); it++)
		std::cout << it->second << std::endl;

	for (size_t i = 0; i < 10; i++)
		std::cout << "element at " << ids[i].first << " is " << mymap[ids[i].first] << std::endl;
	return (0);
}
