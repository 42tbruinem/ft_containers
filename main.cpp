/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 19:16:57 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/11 21:25:27 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.hpp>
#include <iostream>

int	main(void)
{
	ft::vector<int>	myvec;
	ft::vector<int> yeet(5, 100);

	myvec.push_back(5);
	for (size_t i = 0; i < yeet.size() ; i++)
		std::cout << yeet[i] << std::endl;
	std::cout << std::endl;
	for (ft::vector<int>::iterator it = yeet.begin() ; it != yeet.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;
	myvec.resize(3);
	for (auto val : yeet)
		std::cout << val << std::endl;
	std::cout << "Begin is lower than End? " << std::boolalpha << (yeet.begin() < yeet.end()) << std::endl;
	return (0);
}
