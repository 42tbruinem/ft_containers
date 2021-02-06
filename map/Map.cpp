/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Map.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 19:13:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/04 15:31:02 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"

ft::nodebase::nodebase(nodebase *parent, nodebase *left, nodebase *right) : parent(parent), left(left), right(right) {}

ft::nodebase::nodebase(const nodebase& other) : parent(other.parent), left(other.left), right(other.right) {}

ft::nodebase& ft::nodebase::operator = (const nodebase& other)
{
	if (this != &other)
	{
		this->parent = other.parent;
		this->left = other.left;
		this->right = other.right;
	}
	return (*this);
}

ft::nodebase::~nodebase() {}

ft::nodebase	*ft::nodebase::next()
{
	nodebase *iter = this;
	if (iter->right)
	{
		iter = iter->right;
		while (iter->left)
			iter = iter->left;
	}
	else
	{
		while (iter->parent && iter->parent->right == iter)
			iter = iter->parent;
		iter = iter->parent;
	}
	return (iter);
}

ft::nodebase	*ft::nodebase::prev()
{
	nodebase *iter = this;
	if (iter->left)
	{
		iter = iter->left;
		while (iter->right)
			iter = iter->right;
	}
	else
	{
		while (iter->parent && iter->parent->left == iter)
			iter = iter->parent;
		iter = iter->parent;
	}
	return (iter);
}

ft::nodebase	**ft::nodebase::link_to_parent()
{
	nodebase *parent = this->parent;
	if (!parent)
		return (NULL);
	if (parent->left == this)
		return (&parent->left);
	if (parent->right == this)
		return (&parent->right);
	return (NULL);
}
