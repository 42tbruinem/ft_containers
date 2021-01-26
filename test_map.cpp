/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_map.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 15:10:32 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/26 17:44:05 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <IteratorFunctions.hpp>
#include <test_header.hpp>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <vector>
#include <set>
#include <unistd.h>

template <class Map>
void	print_keyval(const Map& container) //iterator = const_iterator should throw error apparantly
{
	for (typename Map::const_iterator it = container.begin(); it != container.end(); it++)
		std::cout << "Key: " << it->first << " : Val: " << it->second << std::endl;
}

std::vector<std::string>	generate_random_strings(std::string characters, size_t amount, size_t resultsize, bool unique = false)
{
	std::vector<std::string>	strings;
	std::string	tmp(resultsize, '\0');

	std::srand(time(NULL));
	for (size_t c = 0; c < amount; c++)
	{
		bool is_unique = false;
		while (!is_unique)
		{
			for (size_t i = 0; i < resultsize; i++)
			{
				tmp[i] = characters[std::rand() % characters.size()];
			}
			if (!unique || std::find(strings.begin(), strings.end(), tmp) == strings.end())
				is_unique = true;
		}
		strings.push_back(tmp);
	}
	return (strings);
}

std::vector<std::pair<std::string, size_t> >	create_pairs_randval(std::vector<std::string> strings, size_t maxvalue)
{
	std::vector<std::pair<std::string, size_t> >	pairs(strings.size());

	for (size_t i = 0; i < strings.size(); i++)
		pairs[i] = std::pair<std::string, size_t>(strings[i], std::rand() % maxvalue);
	return (pairs);
}

std::vector<std::pair<std::string, size_t> >	create_pairs_sequence(std::vector<std::string> strings)
{
	std::vector<std::pair<std::string, size_t> >	pairs(strings.size());

	for (size_t i = 0; i < strings.size(); i++)
		pairs[i] = std::pair<std::string, size_t>(strings[i], i);
	return (pairs);
}

template <class Map, class Value>
void	init_map_insert(Map& container, const std::vector<Value>& content)
{
	for (typename vector<Value>::iterator it = content.begin(); it != content.end(); it++)
		container.insert(*it);
}

template <class Map, class Value>
void	init_map_operator_index(Map& container, const std::vector<Value>& content)
{
	for (size_t i = 0; i < content.size(); i++)
		container[content[i].first] = content[i].second;
}

template <class Map, class Vec>
void	random_order_erase(Map& container, const Vec& content)
{
	std::set<size_t>	deleted;
	size_t				lastsize;
	srand(time(NULL));
	for (;;)
	{
		lastsize = container.size();
		size_t element_to_delete_index = std::rand() % content.size();
		std::cout << "Deleting: " << content[element_to_delete_index].first << " (" << element_to_delete_index << ")\n";
		container.erase(content[element_to_delete_index].first);
		std::cout << "CONTAINER SIZE AFTER: " << container.size() << std::endl;
		if (container.size() != lastsize)
			deleted.insert(element_to_delete_index);
		else if (deleted.find(element_to_delete_index) == deleted.end()) //couldnt delete it, but it's not deleted yet
		{
			std::cout << "COULDNT DELETE AN ELEMENT EVEN THOUGH IT'S 100% IN MY MAP" << std::endl;
			break ;
		}
		if (!container.size())
			break ;
	//	usleep(20000);
		sleep(1);
	}
	container.info();
}

template<class Map>
void	generate_random_numberkeys(Map& container, size_t amount, std::set<size_t>& numbers)
{
	srand(time(NULL));

	for (size_t i = 0; i < amount; i++)
	{
		size_t key = rand() % 300;
		numbers.insert(key);
		container.insert(std::pair<size_t, size_t>(key, i));
	}
}

int main(void)
{
	std::vector<std::string>	strings = generate_random_strings("abcdefghijklmnop", 20, 5);
	std::vector<std::pair<std::string, size_t> >	sequential_pairs = create_pairs_sequence(strings);

	for (size_t i = 0; i < strings.size(); i++)
		std::cout << strings[i] << std::endl;

	print_version();
	container_header("MAP");

	//Constructors
	subject_title("CONSTRUCTORS");

	map<std::string, size_t>	map_default;
//	map<std::string, size_t>	map_sequence;
	map<size_t, size_t>			map_numbers;
//	init_map_operator_index(map_sequence, sequential_pairs);

	std::set<size_t>	numbers;
	generate_random_numberkeys(map_numbers, 20, numbers);
	std::vector<size_t>	number_vec;
	for (auto it = numbers.begin(); it != numbers.end(); it++)
		number_vec.push_back(*it);
	std::vector<std::pair<size_t, size_t> >	number_pairs(number_vec.size());
	for (size_t i = 0 ; i < number_vec.size(); i++)
		number_pairs[i].first = number_vec[i];
//	print_keyval(map_sequence);
//	print_keyval(map_numbers);
	random_order_erase(map_numbers, number_pairs);
	return (0);
}
