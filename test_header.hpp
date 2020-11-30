/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_header.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 13:35:05 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/11/30 14:28:27 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HEADER_HPP
# define TEST_HEADER_HPP

# include <iostream>
# include <string>

#if FT == 1
 #include "Vector.hpp"
  using namespace ft;
#else
 #include <vector>
  using namespace std;
#endif

template <typename Container>
void	capacity_information(Container c, std::string title)
{
	std::cout << "Size of " << title << " is " << c.size() << std::endl;
	std::cout << "Capacity of " << title << " is " << c.capacity() << std::endl;
}

void	print_version()
{
	static const std::string versions[] = {
	"STANDARD",
	"FT",
	};

	std::cout << "THE VERSION BEING RAN IS: " << versions[FT] << std::endl;
}

void	container_header(std::string name)
{
	size_t padding = 66 - name.size();

	std::cout << "******************************************************************" << std::endl;
	std::cout << std::string(padding / 2, ' ');
	std::cout << name;
	std::cout << std::string((padding / 2) + padding % 2, ' ') << std::endl;
	std::cout << "******************************************************************" << std::endl;
}

void	subject_title(std::string name)
{
	size_t padding = 66 - name.size();
	std::cout << std::endl << "------------------------------------------------------------------" << std::endl;
	std::cout << std::string(padding / 2, ' ');
	std::cout << name;
	std::cout << std::string((padding / 2) + padding % 2, ' ');
	std::cout << std::endl << "------------------------------------------------------------------" << std::endl << std::endl;
}

template <typename Container>
void	comparison_operator_container(Container a, Container b, std::string a_title, std::string b_title)
{
	std::cout << a_title << " operator == " << b_title << " = " << ((a == b) ? "True" : "False") << std::endl;
	std::cout << a_title << " operator != " << b_title << " = " << ((a != b) ? "True" : "False") << std::endl;
	std::cout << a_title << " operator > " << b_title << " = " << ((a > b) ? "True" : "False") << std::endl;
	std::cout << a_title << " operator < " << b_title << " = " << ((a < b) ? "True" : "False") << std::endl;
	std::cout << a_title << " operator >= " << b_title << " = " << ((a >= b) ? "True" : "False") << std::endl;
	std::cout << a_title << " operator <= " << b_title << " = " << ((a <= b) ? "True" : "False") << std::endl;
	std::cout << "---" << std::endl;
	std::cout << b_title << " operator == " << a_title << " = " << ((b == a) ? "True" : "False") << std::endl;
	std::cout << b_title << " operator != " << a_title << " = " << ((b != a) ? "True" : "False") << std::endl;
	std::cout << b_title << " operator > " << a_title << " = " << ((b > a) ? "True" : "False") << std::endl;
	std::cout << b_title << " operator < " << a_title << " = " << ((b < a) ? "True" : "False") << std::endl;
	std::cout << b_title << " operator >= " << a_title << " = " << ((b >= a) ? "True" : "False") << std::endl;
	std::cout << b_title << " operator <= " << a_title << " = " << ((b <= a) ? "True" : "False") << std::endl;
}

template <typename Container>
void	const_operator_print_container(const Container& c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using const [] operator element access" << std::endl;

	for (size_t i = 0;i < c.size(); i++)
	{
		std::cout << c[i];
		if (i + 1 < c.size())
			std::cout << delim;
		else
			std::cout << "\n";
	}
	std::cout << std::endl;
}

template <typename Container>
void	operator_print_container(Container c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using [] operator element access" << std::endl;

	for (size_t i = 0;i < c.size(); i++)
	{
		std::cout << c[i];
		if (i + 1 < c.size())
			std::cout << delim;
		else
			std::cout << "\n";
	}
	std::cout << std::endl;
}

//iterator print functions

template <typename Container>
void	iter_print_container(Container c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using 'iterator'" << std::endl;
	typename Container::iterator it = c.begin();

	for (;it != c.end();)
	{
		std::cout << *it;
		if (++it == c.end())
			std::cout << "\n";
		else
			std::cout << delim;
	}
	std::cout << std::endl;
}

template <typename Container>
void	const_iter_print_container(const Container c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using 'const_iterator'" << std::endl;
	typename Container::const_iterator it = c.begin();

	for (;it != c.end();)
	{
		std::cout << *it;
		if (++it == c.end())
			std::cout << "\n";
		else
			std::cout << delim;
	}
	std::cout << std::endl;
}

template <typename Container>
void	reverse_iter_print_container(Container c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using 'reverse_iterator'" << std::endl;
	typename Container::reverse_iterator it = c.rbegin();

	for (;it != c.rend();)
	{
		std::cout << *it;
		if (++it == c.rend())
			std::cout << "\n";
		else
			std::cout << delim;
	}
	std::cout << std::endl;
}

template <typename Container>
void	const_reverse_iter_print_container(const Container c, std::string title, std::string delim = ",")
{
	std::cout << "Printing " << title << " of size " << c.size() << " using 'const_reverse_iterator'" << std::endl;
	typename Container::const_reverse_iterator it = c.rbegin();

	for (;it != c.rend();)
	{
		std::cout << *it;
		if (++it == c.rend())
			std::cout << "\n";
		else
			std::cout << delim;
	}
	std::cout << std::endl;
}

#endif
