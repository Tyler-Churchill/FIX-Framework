#include "SceneTree.h"

template <typename Item>
size_t tree_size(const Node<Item> *head)
{
	size_t count = 1;
	for (auto n : head->children)
	{
		count += tree_size(n);
	}
	return count;
}

template <typename Item>
void tree_copy(const Node<Item>* source, Node<Item>*& head)
{
	for (size_t x = 0; x < source->children.size(); x++)
	{
		head->children.push_back(new Node<Item>(source->children[x]->data));
		tree_copy(source->children[x], head->children[x]);
	}
}

template <typename Item>
void tree_clear(Node<Item>*& head)
{
	for (auto i : head->children)
	{
		tree_clear(i);
	}
	delete head;
}

template <typename Item>
Node<Item>* tree_search(Node<Item> *head, const Item& target)
{
	if (head->data == target)
	{
		return head;
	}
	else
	{
		for (auto n : head->children)
		{
			auto i = tree_search(n, target);
			if (i != nullptr)
				return i;
		}
	}
	return nullptr;
}

template <typename Item>
size_t tree_height(const Node<Item> *head)
{
	size_t max = 0;
	for (auto i : head->children)
	{
		max = fmax(max, tree_height(i));
	}
	return max + 1;
}


/*******************************************
Tree class.
*******************************************/

template <typename Item>
SceneTree<Item>::SceneTree(const Item &d)
{
	root = new Node<Item>(d);
}

template <typename Item>
SceneTree<Item>::SceneTree(const SceneTree &t)
{
	root = new Node<Item>(t.root->data);
	tree_copy(t.root, root);
}

template <typename Item>
SceneTree<Item>::~SceneTree()
{
	tree_clear(root);
}

// Mutators
template <typename Item>
SceneTree<Item>& SceneTree<Item>::operator=(const SceneTree<Item> &t)
{
	if (size() > 1)
	{
		tree_clear(root);
	}
	root = new Node<Item>(t.root->data);
	tree_copy(t.root, root);
	return *this;
}

template <typename Item>
bool SceneTree<Item>::insert(const Item &entry, const Item &parent)
{
	if (!contains(entry) && contains(parent))
	{
		auto *x = tree_search(root, parent);
		if (x != nullptr)
		{
			x->children.push_back(new Node<Item>(entry));
			return true;
		}
	}
	return false;
}

template <typename Item>
bool SceneTree<Item>::remove(const Item &entry)
{
	if (contains(entry))
	{
		auto *p = find_parent(root, entry);
		auto *e = tree_search(root, entry);

		for (auto c : e->children)
		{
			p->children.push_back(c);
		}
		p->children.erase(std::remove(p->children.begin(), p->children.end(), e));
		delete e;

		return true;
	}
	return false;
}

// Accessors

template <typename Item>
size_t SceneTree<Item>::size() const
{
	return tree_size(root);
}

template <typename Item>
size_t SceneTree<Item>::height() const
{
	return tree_height(root);
}

template <typename Item>
bool SceneTree<Item>::contains(const Item &entry) const
{
	return (tree_search(root, entry) != nullptr);
}

template <typename Item>
bool SceneTree<Item>::descendants(const Item &entry, std::vector<Item> &v) const
{
	if (contains(entry))
	{
		auto *x = tree_search(root, entry);
		for (auto i : x->children)
		{
			v.push_back(decendants(i, v));
		}

		return true;
	}
	return false;
}

template <typename Item>
void SceneTree<Item>::print() const
{
	print(root);
}

// Non member
template <typename Item>
void print(Node<Item>* root)
{
	std::cout << root->data << " ";
	for (auto i : root->children)
	{
		print(i);
	}
}

template <typename Item>
Node<Item>* find_parent(Node<Item>* root, const Item& d)
{
	for (auto i : root->children)
	{
		if (i->data == d)
		{
			return root;
		}
		find_parent(i, d);
	}
	return nullptr;
}