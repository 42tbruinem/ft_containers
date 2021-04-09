/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_test.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 13:17:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/04/09 13:20:08 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <iostream>
#include <unistd.h>

size_t calc_capacity(size_t size)
{
	return((size_t)pow(2, ceil(log2(size))));
}

int main(void)
{
	for (size_t i = 0; i < 1000; i++)
	{
		std::cout << "input: " << i << " | output: " << calc_capacity(i) << std::endl;
		sleep(1);
	}
	return (0);
}
