/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_map_specific_case2.cpp                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 19:47:00 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/26 19:30:09 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(void)
{
	static const char *keys[] = {
	"koiok",
	"knhof",
	"gdkha",
	"kobcl",
	"egbce",
	"dpbij",
	"jdhbb",
	"cmojk",
	"dpnog",
	};

	static const char *deletion[] = {
	"ebbhd",
	"ebbhd",
	"dgjlj",
	"dangm",
	"djpnf",
	"ikdgp",
	"aglkk",
	"hkecj",
	"fpidp",
	"egbce",
	"bilpj",
	"ikdgp",
	"ilhga",
	"kpajo",
	"ilgcf",
	"kobcl",
	"glfhe",
	"amgfd",
	"dpbij",
	"jpmmn",
	"cmojk",
	"hlkgl",
	"dpnog",
	"kpajo",
	"koiok",
	"knhof",
	"jdhbb",
	"gdkha",
	};

	std::vector<std::string>	keys_vec(keys, keys + sizeof(keys) / sizeof(char *));
	std::vector<std::string>	delete_vec(deletion, deletion + sizeof(deletion) / sizeof(char *));

	ft::map<std::string, size_t>	mymap;
	for (size_t i = 0; i < keys_vec.size(); i++)
		mymap[keys_vec[i]] = i;

	for (size_t i = 0; i < delete_vec.size(); i++)
		mymap.erase(delete_vec[i]);
	mymap.erase("knhof");
	for (ft::map<std::string, size_t>::iterator it = mymap.begin(); it != mymap.end(); it++)
		std::cout << "Key: " << it->first << " : Val: " << it->second << std::endl;
	return (0);
}
