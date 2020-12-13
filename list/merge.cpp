/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   merge.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/13 19:06:00 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/12/13 19:45:31 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>

using namespace std;

int main(void)
{
	int			data[] = {0, 3, 3, 5, 6, 6, 25};
	int			data2[] = {1, 3,4,4,5,9,20,21};
	list<int>	test;
	list<int>	test2;

	for (size_t i = 0; i < 7; i++)
	{
		test.push_back(data[i]);
		test2.push_back(data2[i]);
	}

	for (auto it = test.begin(); it != test.end();)
		std::cout << *it << ((++it != test.end()) ? "," : "\n");
	for (auto it = test2.begin(); it != test2.end();)
		std::cout << *it << ((++it != test2.end()) ? "," : "\n");
	test.merge(test2, [](int& a, int& b) { return a < b; });
	for (auto it = test.begin(); it != test.end();)
		std::cout << *it << ((++it != test.end()) ? "," : "\n");
	return (0);
}
