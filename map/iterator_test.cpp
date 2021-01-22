/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iterator_test.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/13 19:35:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/16 19:11:53 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

template <class Key, class Value>
class node;

template <class Key, class Value>
class nodebase
{
	public:
		nodebase(node<Key, Value> *parent = NULL, node<Key, Value> *right = NULL, node<Key, Value> *left = NULL) : parent(parent), right(right), left(left) {}
		node<Key, Value>	*parent;
		node<Key, Value>	*left;
		node<Key, Value>	*right;
		node<Key, Value>	*increment() throw ();
		node<Key, Value>	*decrement() throw ();
};

template <class Key, class Value>
class node : public nodebase<Key, Value>
{
	typedef nodebase<Key, Value>	base;
	public:
		node(const Key& key, const Value& val = Value(), node *parent = NULL, node *right = NULL, node *left = NULL) : keyval(key, val), base(parent, right, left) {}
		node	*next()
		{
			const Key& key(this->keyval.first);
			node *iter = this;

			while (iter)
			{
				const Key& current_key = iter->keyval.first;
				if (current_key > key)
					return (iter);
				if (iter->right)
					return (iter->right);
				else
					return (iter->parent);
			}
			return (iter);
		}
		node	*prev()
		{
			const Key& key(this->keyval.first);
			node *iter = this;

			while (iter)
			{
				const Key& current_key = iter->keyval.first;
				if (current_key > key)
					return (iter);
				if (iter->left)
					iter = iter->left;
				else
					iter = iter->parent;
			}
			return (iter);
		}
		std::pair<const Key, Value>	keyval;
};

template <class Node, class Value>
class Iterator
{
	typedef Value& value_reference;
	typedef Value* value_pointer;

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
		value_reference		operator * ()
		{
			return (ptr->keyval);
		}
		value_pointer		operator -> ()
		{
			return (&ptr->keyval);
		}
		Iterator&	operator ++ ()
		{
			this->ptr = this->ptr->next();
			return (*this);
		}
		Iterator	operator ++ (int)
		{
			Iterator it(*this);

			this->ptr = this->ptr->next();
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
		bool		operator == (const Iterator& it)
		{
			return (it.ptr == this->ptr);
		}
		bool		operator != (const Iterator& it)
		{
			return !(it == *this);
		}
	private:
		Node *ptr;
};

template <class Key, class Value>
class tree
{
	typedef node<Key, Value>	treenode;
	public:
		typedef Iterator<node<Key, Value>, std::pair<const Key, Value>>	iterator;

		tree() : len(0), root(NULL), first(), last() {}
		Value&	operator [] (const Key& key)
		{
			treenode *element = find(key);
			if (!element || static_cast<treenode*>(element)->keyval.first != key)
				element = insert(key);
			return static_cast<treenode*>(element)->keyval.second;
		}
		iterator	begin()
		{
			treenode *lowest = this->root;
			while (lowest->left)
				lowest = lowest->left;
			return (iterator(lowest));
		}
		iterator	end()
		{
			treenode	*highest = this->root;
			while (highest->right)
				highest = highest->right;
			highest->right = &this->last;
			this->last.parent = highest;
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

			while (*iter)
			{
				parent = (*iter);
				if (key > (static_cast<treenode*>(*iter))->keyval.first)
					iter = &(*iter)->right;
				else if (key < (static_cast<treenode*>(*iter))->keyval.first)
					iter = &(*iter)->left;
				else
					return (NULL);
			}
			*iter = new treenode(key, val, parent, NULL, NULL);
			std::cout << (void *)iter << std::endl;
			return (*iter);
		}
	private:
		treenode *root;
		nodebase<Key, Value>	first;
		nodebase<Key, Value>	last;
		size_t len;
};

int main(void)
{
	tree<std::string, size_t>	container;

	container["a"] = 5;
	container["z"] = 25;
	container["c"] = 8;
	container["y"] = 30;
	container["b"] = 10;

	std::cout << container["a"] << std::endl;
	std::cout << container["hoi"] << std::endl;
	std::cout << container["z"] << std::endl;
	std::cout << container["b"] << std::endl;
	std::cout << container["y"] << std::endl;
	std::cout << container["c"] << std::endl;

	container["ab"] = 100;

	std::cout << container["ab"] << std::endl;
	for (tree<std::string, size_t>::iterator it = container.begin(); it != container.end(); it++)
		std::cout << it->second << std::endl;

	return (0);
}
