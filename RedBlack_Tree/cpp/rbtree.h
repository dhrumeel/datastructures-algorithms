#ifndef __RB_TREE_H__
#define __RB_TREE_H__


template<typename T>
class RBtree
{
  public:
	RBtree() { NIL = new Node _root = NULL; }	// Constructor
	size_t size() const { countNodes(_root); }
	bool insert(const T& elem);
	void remove(const T& elem);
	const T* find(const T& elem) const;
	const T* max() const;
	const T* min() const;

  private:
	class Node
	{
	  public:
		Node(d, p, c): 
			parent(p), 
			left(NULL), right(NULL), 
			data(d), 
			color(c) { }
		void flipColor() { color = (color == Red) ? Black : Red; }
		enum { Red, Black } color;
		const T data;
		Node* left;
		Node* right;
		Node* parent;
	};
	
	size_t countNodes(Node* r) const;
	void rotateRight(Node* node);
	void rotateLeft(Node* node);
	void fixRedViolation(Node* node);
	Node* findNodeWithData(const T& elem) const;
	bool removeNode(Node* node);
	void fixExtraBlack(Node* node);
	Node* treeSuccessor(Node* node) const;
	Node* _root;
	Node* NIL;
}

#include "rbtree.hpp"

#endif
