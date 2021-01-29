/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_map.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 15:10:32 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/29 13:42:04 by tbruinem      ########   odam.nl         */
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
		std::cout << "Deleting: " << content[element_to_delete_index] << " (" << element_to_delete_index << ")\n";
		container.erase(content[element_to_delete_index]);
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
//		sleep(1);
	}
	container.info();
}

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

template<class Map, class Key>
void	init_map_random(Map& container, size_t amount, std::vector<Key>& keys)
{
	srand(time(NULL));

	size_t i = 0;
	for (; i < amount;)
	{
		Key key = generate_key<Key>();
		size_t oldsize = container.size();
		container.insert(std::pair<Key, size_t>(key, i));
		if (oldsize != container.size())
		{
			keys.push_back(key);
			i++;
		}
	}
}

template <class Container>
void	map_information(const Container& c, std::string title)
{
	std::cout << "Size of " << title << " is " << c.size() << std::endl;
}

template <class Container, class Key>
void	map_count_key(const Container& c, std::string title, const Key& key)
{
	std::cout << title << " contains the key: '" << key << "' " << c.count(key) << " times" << std::endl;
}

template <class Container, class Key>
void	map_lowerbound_key(const Container& c, std::string title, const Key& key)
{
	std::cout << "finding lowerbound of key: '" << key << "' in " << title << std::endl;
	std::cout << "Results in: ";
	typename Container::const_iterator it = c.lower_bound(key);
	if (it == c.end())
		std::cout << "the end";
	else
		print_content(*it);
	std::cout << std::endl;
}

template <class Container, class Key>
void	map_upperbound_key(const Container& c, std::string title, const Key& key)
{
	std::cout << "finding upperbound of key: '" << key << "' in " << title << std::endl;
	std::cout << "Results in: ";
	typename Container::const_iterator it = c.upper_bound(key);
	if (it == c.end())
		std::cout << "the end";
	else
		print_content(*it);
	std::cout << std::endl;
}

template <class Container, class Key>
void	map_equalrange_key(const Container& c, std::string title, const Key& key)
{
	std::cout << "finding equalrange of key: '" << key << "' in " << title << std::endl;
	std::cout << "Results in ";
	std::pair<typename Container::const_iterator, typename Container::const_iterator>	it = c.equal_range(key);
	std::cout << "first: ";
	if (it.first == c.end())
		std::cout << "the end";
	else
		std::cout << it.first->first;
	std::cout << ", last: ";
	if (it.second == c.end())
		std::cout << "the end";
	else
		std::cout << it.second->first;
	std::cout << std::endl;
}

template <class Container, class Key>
void	map_keycomp_iter(const Container& c, std::string title, const Key& key)
{
	typename Container::key_compare comp_funct = c.key_comp();
	std::cout << "Comparing all elements of " << title << " against key: '" << key << "' using key_compare" << std::endl;

	for (typename Container::const_iterator it = c.begin(); it != c.end(); it++)
	{
		bool before = comp_funct(it->first, key);
		bool after = comp_funct(key, it->first);

		std::cout << "(" << it->first << ") ";
		if (!before && !after)
			std::cout << "is equivalent to ";
		else if (before)
			std::cout << "goes before ";
		else
			std::cout << "goes after ";
		std::cout << "key: " << key << std::endl;
	}
}

template <class Container, class Key>
void	map_valcomp_iter(const Container& c, std::string title, const Key& key)
{
	typename Container::value_compare comp_funct = c.value_comp();
	typename Container::value_type	pair(key, 404);
	std::cout << "Comparing all elements of " << title << " against key: '" << key << "' using value_compare" << std::endl;

	for (typename Container::const_iterator it = c.begin(); it != c.end(); it++)
	{
		bool before = comp_funct(*it, pair);
		bool after = comp_funct(pair, *it);

		std::cout << "(" << it->first << ") ";
		if (!before && !after)
			std::cout << "is equivalent to ";
		else if (before)
			std::cout << "goes before ";
		else
			std::cout << "goes after ";
		std::cout << "key: " << key << std::endl;
	}
}

int main(void)
{
	print_version();
	container_header("MAP");

	subject_title("CONSTRUCTORS");

	std::vector<std::string>	map_default_keys;
	map<std::string, size_t>	map_default;

	init_map_random(map_default, 10, map_default_keys);
	map<std::string, size_t>	map_range(map_default.begin(), map_default.end());
	map<std::string, size_t>	map_copy(map_range);
	map_default = map_copy;

//	random_order_erase(map_default, map_default_keys);
	subject_title("ELEMENT ACCESS");

	operator_print_container(map_default, "map_default", map_default_keys, " : ");

	subject_title("ITERATORS");

//	random_order_erase(map_range, map_default_keys);
//	random_order_erase(map_copy, map_default_keys);
	iter_print_container(map_default, "map_default", "\n");
	const_iter_print_container(map_default, "map_default", "\n");
	reverse_iter_print_container(map_default, "map_default", "\n");
	const_reverse_iter_print_container(map_default, "map_default", "\n");

	subject_title("CAPACITY");

	map<std::string, size_t>	map_empty;
	is_empty(map_empty, "map_empty");
	map_empty["empty"] = 0;
	is_empty(map_empty, "map_empty");
	map_information(map_empty, "map_empty");
	std::cout << "Max size of " << "map_empty" << " is " << map_empty.max_size() << std::endl;

	subject_title("MODIFIERS");

	map_information(map_default, "map_default");
	map_default.clear();
	map_information(map_default, "map_default");
	iter_print_container(map_default, "map_default", "\n");
	map_default.insert(std::pair<std::string, size_t>("hello", 42));
	iter_print_container(map_default, "map_default", "\n");
	map_default.erase("not in map");
	iter_print_container(map_default, "map_default", "\n");
	map_default.erase("hello");
	iter_print_container(map_default, "map_default", "\n");
	map_default.insert(std::pair<std::string, size_t>("now I'm over here", 404));
	map_empty.clear();
	iter_print_container(map_default, "map_default", "\n");
	iter_print_container(map_empty, "map_empty", "\n");
	map_default.swap(map_empty);
	iter_print_container(map_default, "map_default", "\n");
	iter_print_container(map_empty, "map_empty", "\n");

	subject_title("LOOKUP");
	
	map_count_key(map_empty, "map_empty", "now I'm over here");
	iter_print_container(map_empty, "map_empty", "\n");
	map_empty.erase("now I'm over here");
	map_count_key(map_empty, "map_empty", "now I'm over here");
	map_empty["a"] = 0;
	map_empty["b"] = 1;
	map_empty["c"] = 2;

	map_lowerbound_key(map_empty, "map_empty", "b");
	map_upperbound_key(map_empty, "map_empty", "b");
	map_equalrange_key(map_empty, "map_empty", "b");
	map_empty.clear();
	map_lowerbound_key(map_empty, "map_empty", "b");
	map_upperbound_key(map_empty, "map_empty", "b");
	map_equalrange_key(map_empty, "map_empty", "b");

	subject_title("OBSERVERS");
	map_empty["a"] = 0;
	map_empty["b"] = 1;
	map_empty["c"] = 2;

	map_keycomp_iter(map_empty, "map_empty", "b");
	map_valcomp_iter(map_empty, "map_empty", "b");
	return (0);
}
