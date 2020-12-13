/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/13 19:06:00 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/12/13 20:05:15 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>

using namespace std;

int main(void)
{
	int			data[] = {0, 3,2,5, 5,3, 6, 2,8,6, 25};
	list<int>	test;

	for (size_t i = 0; i < 11; i++)
	{
		test.push_back(data[i]);
	}

	for (auto it = test.begin(); it != test.end();)
		std::cout << *it << ((++it != test.end()) ? "," : "\n");
//	test.merge(test2, [](int& a, int& b) { return a < b; });
//	test.sort();
	test.splice(++(++(test.begin())), test, test.begin());
	for (auto it = test.begin(); it != test.end();)
		std::cout << *it << ((++it != test.end()) ? "," : "\n");
	return (0);
}