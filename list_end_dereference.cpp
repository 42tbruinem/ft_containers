/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_end_dereference.cpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/09 11:27:11 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/12/09 11:30:11 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>

using namespace std;

int main(void)
{
	list<string>	listerino;


	listerino.push_back("yeet");
	listerino.push_back("yeet");
	listerino.push_back("yeet");
	listerino.push_back("yeet");
	std::cout << *(listerino.end()) << std::endl;
	return (0);
}
