/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   binary_unique_ft.cpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/13 18:40:14 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/12/13 18:57:51 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <List.hpp>
#include <iostream>

using namespace ft;

class couple
{
	public:
		int a, b;
		couple() : a(0), b(0) {}
		couple(int a, int b) : a(a), b(b) {}
};

std::ostream& operator << (std::ostream& stream, couple& object)
{
	stream << "[" << object.a << "," << object.b << "]";
	return (stream);
}

int main(void)
{
	couple			data[] = {{3,0}, {8,0}, {4,0}, {4,1}, {6,0}, {7,0}, {4,1}, {3,0}, {3,5}};
	list<couple>	test;

	for (size_t i = 0; i < 9; i++)
		test.push_back(data[i]);
	for (auto it = test.begin(); it != test.end();)
		std::cout << *it << ((++it != test.end()) ? "," : "\n");

	test.unique([](couple& a, couple& b){return a.a == b.a; });

	for (auto it = test.begin(); it != test.end();)
		std::cout << *it << ((++it != test.end()) ? "," : "\n");

	return (0);
}
