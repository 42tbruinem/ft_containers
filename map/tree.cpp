/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/11 13:13:03 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/17 01:09:30 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <exception>
#include <utility>

template <class Key, class T>
class	Node
{
	public:
		Node(const Key& key, const T& value, Node *parent = NULL, Node *right = NULL, Node *left = NULL) : value(value), parent(parent), right(right), left(left) {}
		Node(const Node& other) : key(other.key), value(other.value), parent(other.parent), right(other.right), left(other.left) {}
		Key		key;
		T		value;
		Node *parent;
		Node *right;
		Node *left;
};

template <class Node, class ReferenceType, class PointerType>
class	Iterator
{
	public:
		Iterator(Node *ptr = NULL) : ptr(ptr) {}
		Iterator(const Iterator& other) : ptr(other.ptr) {}
		~Iterator() {}
		Iterator& operator ++ ()
		{
			
		}
		Iterator& operator ++ (int)
		{

		}
		Iterator& operator -- ()
		{

		}
		Iterator& operator -- (int)
		{

		}
		ReferenceType operator * ()
		{

		}
		PointerType operator -> ()
		{

		}
	private:
		Node	*ptr;
};

template <class Key, class T>
class map
{
	public:
		typedef Node<Key, T> node;
		typedef Iterator<node, T& T*> iterator;
	public:
		map() : root(NULL), last(NULL), len(0) {}
		~map()
		{
			traverse(this->root, [](node *nd) { delete nd; });
		}
		std::pair<iterator, bool>	insert(const std::pair<Key, T>& keyval)
		{
			

		}
		{
			node **iter = &this->root;
			node *parent = NULL;
			if (!iter)
				return ;
			while (*iter)
			{
				parent = *iter;
				Key current_key = (*iter)->key;
				if (current_key > keyval.first)
					iter = &(*iter)->left;
				else if (current_key < keyval.first)
					iter = &(*iter)->right;
				else
				{
					(*iter)->value = keyval.second;
					return ;
				}
			}
			*iter = new node(keyval.first, keyval.second, parent);
		}
		void	print()
		{
			traverse(this->root, [](node *nd) { std::cout << nd->value; });
		}
		T&		operator [] (const Key& key)
		{
			node *element = this->find(this->root, key);
			if (!element)
				
		}
	private:
		node	*find(node *nd, const Key& key)
		{
			if (!nd)
				return (NULL);
			if (node->key == key)
				return (node);
			if (nd->right)
				find(nd->right);
			if (nd->left)
				find(nd->left);
			return (NULL);
		}
		void	traverse(node *nd, void (*funct)(Node<Key, T>*))
		{
			if (!nd)
				return ;
			if (nd->right)
				traverse(nd->right, funct);
			if (nd->left)
				traverse(nd->left, funct);
			funct(nd);
		}
		node *root;
		node *last;
		size_t len;
};

int main(void)
{
	map<std::string, size_t>	mymap = map<std::string, size_t>();
	std::string ids[] = {
	"hoi",
	"hello",
	"doei",
	"bob",
	"ans",
	"timmy",
	"yeet",
	"skeet",
	"bieba",
	"boeba"
	};

	for (size_t i = 0; i < 10; i++)
		mymap.insert(std::pair<std::string, size_t>(ids[i], i));
	std::cout << std::endl;

	for (size_t i = 0; i < 10; i++)
		std::cout << "element at " << ids[i] << " is " << mymap[ids[i]] << std::endl;
	return (0);
}
