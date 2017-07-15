#ifndef _SCEENETREE_H
#define _SCEENETREE_H
#include <vector>
#include <iostream>

template <typename Item>
struct Node {
	Item data;
	std::vector<Node*> children;
	Node(const Item &d = Item()) : data(d) {}
};

template <typename Item>
size_t tree_size(const Node<Item> *head);

template <typename Item>
void tree_copy(const Node<Item>* source, Node<Item>*& head);

template <typename Item>
void tree_clear(Node<Item>*& head);

template <typename Item>
Node<Item>* tree_search(Node<Item>* head, const Item& target);

template <typename Item>
size_t tree_height(const Node<Item> *head);

template <typename Item>
class SceneTree
{
public:
	// constructor
	explicit SceneTree(const Item &d = Item());
	// copy constructor
	SceneTree(const SceneTree &t);
	// deconstructor
	~SceneTree();

	// Mutators

	//*******************************************************************
	// Function Name: operator=
	// Purpose: Assigns the current tree to the given tree
	//*******************************************************************
	SceneTree& operator=(const SceneTree &t);

	//*******************************************************************
	// Function Name: insert
	// Purpose: Inserts a given entry onto the given parent
	//*******************************************************************
	bool insert(const Item &entry, const Item &parent);

	//*******************************************************************
	// Function Name: remove
	// Purpose: Removes a given entry from the tree
	//*******************************************************************
	bool remove(const Item &entry);

	// Accessors

	//*******************************************************************
	// Function Name: size
	// Purpose: Returns the number of nodes in the tree
	//*******************************************************************
	size_t size() const;

	//*******************************************************************
	// Function Name: height
	// Purpose: Returns the length of the longest path in the tree
	//*******************************************************************
	size_t height() const;

	//*******************************************************************
	// Function Name: contains
	// Purpose: Returns true if the tree contains the given entry 
	//*******************************************************************
	bool contains(const Item &entry) const;

	//*******************************************************************
	// Function Name: descendants
	// Purpose: Puts the descendants of the given entry into the given
	//          vector
	//*******************************************************************
	bool descendants(const Item &entry, std::vector<Item> &v) const;

	//*******************************************************************
	// Function Name: print
	// Purpose: Prints out the tree in preorder
	//*******************************************************************
	void print() const;

private:
	Node<Item> *root;
};

template <typename Item>
void print(Node<Item>* node);

//*******************************************************************
// Function Name: tree_height
// Purpose: Returns a pointer to the parent node of the given node
//*******************************************************************
template <typename Item>
Node<Item>* find_parent(Node<Item>* node, const Item& d);
#endif