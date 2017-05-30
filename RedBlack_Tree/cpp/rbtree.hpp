#ifndef __RB_TREE_HPP__
#define __RB_TREE_HPP__

#include <stdexcept>

size_t countNodes(Node* r) const
{
	if(r == NULL)
		return 0;
	else
		return (countNodes(r->left) + countNodes(r->right) + 1);
}

template<typename T>
void RBtree<T>::rotateRight(Node* node)
{
	Node* lc = node->left;
	if(lc == NULL)
		throw logic_error("Cannot rotate right when left child is NULL");

	node->left = lc->right;
	if(lc->right)
		lc->right->parent = node;
	
	lc->right = node;
	lc->parent = node->parent;
	node->parent = lc;
	
	if(lc->parent == NULL)
		_root = lc;
	else
	{
		if(node == lc->parent->left)
			lc->parent->left = lc;
		else if(node == lc->parent->right)
			lc->parent->right = lc;
		else
			throw logic_error("node's parent does not reference node");
	}
}

template<typename T>
void RBtree<T>::rotateLeft(Node* node)
{
	Node* rc = node->right;
	if(rc == NULL)
		throw logic_error("Cannot rotate left when right child is NULL");

	node->right = rc->left;
	if(rc->left)
		rc->left->parent = node;
	
	rc->left = node;
	rc->parent = node->parent;
	node->parent = rc;
	
	if(rc->parent == NULL)
		_root = rc;
	else
	{
		if(node == rc->parent->left)
			rc->parent->left = rc;
		else if(node == rc->parent->right)
			rc->parent->right = rc;
		else
			throw logic_error("node's parent does not reference node");
	}
}

template<typename T>
const T* RBtree<T>::max() const
{
	if(_root == NULL)
	{
		return NULL;
	}
	else
	{
		Node* node = _root;
		while(node->right)
			node = node->right;
		
		return &node->data;
	}
}

template<typename T>
const T* RBtree<T>::min() const
{
	if(_root == NULL)
	{
		return NULL;
	}
	else
	{
		Node* node = _root;
		while(node->left)
			node = node->left;
		
		return &node->data;
	}
}

template<typename T>
inline
Node* RBtree<T>::findNodeWithData(const T& elem) const
{
	Node* node = _root;
	while(node)
	{
		if(elem == node->data)
			return node;
		else if(elem < node->data)
			node = node->left;
		else
			node = node->right;
	}
	
	// If we have not already returned, we have reached a leaf and the search has failed
	return NULL;
}

template<typename T>
const T* RBtree<T>::find(const T& elem) const
{
	Node* node = findNodeWithData(elem);
	if(node)
		return &(node->data);
	else
		return NULL;
}

template<typename T>
bool RBtree<T>::insert(const T& elem)
{
	Node* curNode = _root;
	Node* parNode = NULL;
	bool addToLeft = true;
	
	// Find the to-be parent
	while(curNode)
	{
		if(elem == curNode->data)
			return false;
		else if(elem < curNode->data)
		{
			parNode = curNode;
			curNode = curNode->left;
			addToLeft = true;
		}
		else
		{
			parNode = curNode;
			curNode = curNode->right;
			addToLeft = false;
		}
	}
	
	// Add new node to tree
	Node* newNode = new Node(elem, Red, parNode);
	if(parNode == NULL)
	{
		// Tree was empty, newNode should be root
		_root = newNode;
		newNode->color = Black;
		return true;
	}
	if(addToLeft)
		parNode->left = newNode;
	else
		parNode->right = newNode;
	
	if(parNode->color == Red)
		fixRedViolation(parNode);
	
	return true;	
}

// Should be called with node == lower of the 2 red nodes in the violation
template<typename T>
void RBtree<T>::fixRedViolation(Node* node)
{
	Node* father = node->parent;
	if(father == _root)
	{
		father->color = Black;
		return;
	}
	
	Node* grandpa = father->parent;
	if(father == grandpa->left)
	{	// Red violation is to left of Black grandpa
		Node* uncle = grandpa->right;
		
		if(uncle && uncle->color == Red)
		{	// Case 1: Red uncle
			// Push grandpa's Black to his 2 children
			father->color = Black;
			uncle->color = Black;
			grandpa->color = Red;
			
			if(grandpa == _root)
				grandpa->color = Black;
			else if(grandpa->parent->color == Red)
				fixRedViolation(grandpa);
			
			return;
		}
		
		if(node == father->right)
		{	// Case 2: Black or no uncle; node and grandpa on the same side of father
			rotateLeft(father);
			
			// prepare for Case 3 by renaming node and father as they are now flipped
			node = father;
			father = node->parent;
		}
		
		// Case 3: Black or no uncle; node and grandpa on opposite sides of father
		grandpa->color = Red;
		father->color = Black;
		rotateRight(grandpa);
		
		return;		
	}
	else
	{	// Red violation is to right of Black grandpa
		Node* uncle = grandpa->left;
		
		if(uncle && uncle->color = Red)
		{	// Case 1: Red uncle
			// Push grandpa's Black to his 2 children
			father->color = Black;
			uncle->color = Black;
			grandpa->color = Red;
			
			if(grandpa == _root)
				grandpa->color = Black;
			else if(grandpa->parent->color == Red)
				fixRedViolation(grandpa);
			
			return;
		}
		
		if(node == father->left)
		{	// Case 2: Black or no uncle; node and grandpa on the same side of father
			rotateRight(father);
			
			// prepare for Case 3 by renaming node and father as they are now flipped
			node = father;
			father = node->parent;
		}
		
		// Case 3: Black or no uncle; node and grandpa on opposite sides of father
		grandpa->color = Red;
		father->color = Black;
		rotateLeft(grandpa);
		
		return;
	}
	
}

template<typename T>
bool RBtree<T>::remove(const T& elem)
{
	Node* node = findNodeWithData(elem);
	Node* delNode = NULL;
	
	if(node == NULL)
		return false;

	if(node->left && node->right)
	{
		delNode = treeSuccessor(node);
		node->data = delNode->data;
	}
	else
		delNode = node;
	
	removeNode(delNode);
	
	return true;
}

// will be called with a node having at most 1 child
// will never be called with a NULL
template<typename T>
bool RBtree<T>::removeNode(Node* node)
{
	if(node->left)
	{
		
	}
	else if(node->right)
	{
	
	}
	else
	{	// node has no children
		
	}
}

template<typename T>
void RBtree::fixExtraBlack(Node* node)
{
	
}

template<typename T>
Node* RBtree<T>::treeSuccessor(Node* node) const
{
	if(node == NULL)
		return NULL;

	Node* cur = node->right;
	while(cur && cur->left)
		cur = cur->left;
	
	return cur;
}


#endif