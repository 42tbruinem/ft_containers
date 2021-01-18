/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iterator_test_fix.cpp                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 19:35:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/18 11:17:49 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <utility>
#include <unistd.h>

template <class Key, class Value>
class node
{
	public:
		node(const Key& key = Key(), const Value& val = Value(), node *parent = NULL, node *right = NULL, node *left = NULL) : keyval(key, val), parent(parent), right(right), left(left) {}
		node	*next()
		{
			node *iter = this;
			if (iter->right)
			{
				iter = iter->right;
				while (iter->left)
					iter = iter->left;
			}
			else
			{
				while (iter->parent->right == iter)
					iter = iter->parent;
				iter = iter->parent;
			}
			return (iter);
		}
		node	*prev()
		{
			node *iter = this;
			if (iter->left)
			{
				iter = iter->left;
				while (iter->right)
					iter = iter->right;
			}
			else
			{
				while (iter->parent->left == iter)
					iter = iter->parent;
				iter = iter->parent;
			}
			return (iter);
		}
		std::pair<const Key, Value>	keyval;
		node *parent;
		node *right;
		node *left;
};

template <class Node, class Key, class Value>
class Iterator
{
	typedef std::pair<const Key, Value>	Mapped;
	typedef Mapped& mapped_reference;
	typedef Mapped* mapped_pointer;

	public:
		Iterator(Node *node = NULL) : ptr(node) {}
		Iterator(const Iterator& other) : ptr(other.ptr) {}
		~Iterator() {}
		Iterator& operator = (const Iterator& other)
		{
			if (this != &other)
			{
				this->ptr = other.ptr;
			}
			return (*this);
		}
		mapped_reference		operator * ()
		{
			return (ptr->keyval);
		}
		mapped_pointer		operator -> ()
		{
			return (&(static_cast<node<Key, Value>*>(ptr)->keyval));
		}
		Iterator&	operator ++ ()
		{
			this->ptr = this->ptr->next();
			return (*this);
		}
		Iterator	operator ++ (int)
		{
			Iterator it(*this);

//			std::cout << "left: " << (void *)this->ptr->left << std::endl;
//			std::cout << "right: " << (void *)this->ptr->right << std::endl;
//			std::cout << "parent: " << (void *)this->ptr->parent << std::endl;
			this->ptr = this->ptr->next();
//			std::cout << (void *)this->ptr << std::endl;
			return (it);
		}
		Iterator&	operator -- ()
		{
			this->ptr = this->ptr->prev();
			return (*this);
		}
		Iterator	operator -- (int)
		{
			Iterator it(*this);

			this->ptr = this->ptr->prev();
			return (it);
		}
		bool		operator == (const Iterator it)
		{
			return (it.ptr == this->ptr);
		}
		bool		operator != (const Iterator it)
		{
			return !(*this == it);
		}
	private:
		Node *ptr;
};

template <class Key, class Value>
class tree
{
	typedef node<Key, Value>	treenode;
	public:
		typedef Iterator<treenode, Key, Value>	iterator;

		tree() : len(0), root(NULL), first(), last()
		{
//			std::cout << "first: " << (void *)&this->first << std::endl;
//			std::cout << "last: " << (void *)&this->last << std::endl;
			this->first.parent = &this->last;
			this->last.parent = &this->first;
		}
		Value&	operator [] (const Key& key)
		{
			treenode *element = find(key);
			if (!element || element->keyval.first != key)
				element = insert(key);
			return element->keyval.second;
		}

		iterator	begin()
		{
			return (iterator(this->first.parent));
		}

		iterator	end()
		{
			return (iterator(&this->last));
		}

		treenode *find(const Key& key)
		{
			treenode *iter = this->root;

			while (iter)
			{
				if (key > iter->keyval.first)
					iter = iter->right;
				else if (key < iter->keyval.first)
					iter = iter->left;
				else
					break ;
			}
			return (iter);
		}

		treenode *insert(const Key& key, const Value& val = Value())
		{
			treenode **iter = &this->root;
			treenode *parent = NULL;

			while (*iter && *iter != &this->first && *iter != &this->last)
			{
				parent = (*iter);
				if (key > (*iter)->keyval.first)
					iter = &(*iter)->right;
				else if (key < (*iter)->keyval.first)
					iter = &(*iter)->left;
				else //the element exists
					return (NULL);
			}
			*iter = new treenode(key, val, parent, NULL, NULL);
			if (this->last.parent == &this->first || this->last.parent->keyval.first < key)
			{
//				std::cout << "updated highest key is " << key << std::endl;
				(*iter)->right = &this->last;
				this->last.parent = (*iter);
			}
			if (this->first.parent == &this->last || this->first.parent->keyval.first > key)
			{
//				std::cout << "updated lowest key is " << key << std::endl;
				(*iter)->left = &this->first;
				this->first.parent = (*iter);
			}
//			std::cout << key << " : " << val << " : " << (void *)(*iter) << std::endl;
			return (*iter);
		}
	private:
		treenode	*root;
		treenode	first;
		treenode	last;
		size_t len;
};

int main(void)
{
	tree<std::string, size_t>	container;

	container["y"] = 24;
	container["c"] = 4;
	container["z"] = 25;
	container["a"] = 1;
	container["b"] = 3;

	std::cout << container["a"] << std::endl;
	std::cout << container["hoi"] << std::endl;
	std::cout << container["z"] << std::endl;
	std::cout << container["b"] << std::endl;
	std::cout << container["y"] << std::endl;
	std::cout << container["c"] << std::endl;

	container["ab"] = 2;
	std::cout << container["ab"] << std::endl;

	std::cout << std::endl;

	for (tree<std::string, size_t>::iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
//		sleep(1);
	}
	return (0);
}
