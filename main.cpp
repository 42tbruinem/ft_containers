/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 19:16:57 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/21 11:15:42 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if FT == 1
 #include "Vector.hpp"
 #define vector ft::vector
#else
 #include <vector>
 #define vector std::vector
#endif

int	main(void)
{
	static const std::string versions[] = {
	"STANDARD",
	"FT",
	};

	std::cout << "THE VERSION BEING RAN IS: " << versions[FT] << std::endl;

	vector<int>	myvec;
	vector<int> yeet(5, 100);

	myvec.push_back(5);
	for (size_t i = 0; i < yeet.size() ; i++)
		std::cout << yeet[i] << std::endl;
	std::cout << std::endl;
	for (vector<int>::iterator it = yeet.begin() ; it != yeet.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;
	myvec.resize(3);
	std::cout << "Begin is lower than End? " << std::boolalpha << (yeet.begin() < yeet.end()) << std::endl;
	return (0);
}
