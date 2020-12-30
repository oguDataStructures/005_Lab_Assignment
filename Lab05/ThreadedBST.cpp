#include "ThreadedBST.h"
#include<iostream>
using namespace std;
///-----------------------------------------------
/// Erases all nodes in the tree
/// 
void ThreadedBST::eraseTreeNodes(BSTNode* node) {
	BSTNode* curr = this->min();

	while (curr != NULL) {

		BSTNode* n = this->next(curr);

		delete curr;

		curr = n;

	} // end-while
} //end-eraseTreeNodes

///-----------------------------------------------
/// Adds a given key to the BST
/// 
void ThreadedBST::add(int key) {
	// Fill this in
	BSTNode* newnode = new BSTNode(key);
	BSTNode* ptr = this->root;
	BSTNode* par = NULL;
	if (!this->root) {
		this->root = newnode;
		return;
	}
	while (ptr) {
		par = ptr;
		if (ptr->key == key) return;
		else if (ptr->key > key) {
			if (ptr->leftLinkType == CHILD)
				ptr = ptr->left;
			else break;
		}
		else if (ptr->key < key) {
			if (ptr->rightLinkType == CHILD)
				ptr = ptr->right;
			else break;
		}
	}
	if (par->key > key) {
		newnode->left = par->left;
		newnode->right = par;
		par->leftLinkType = CHILD;
		par->left = newnode;
	}
	else {
		newnode->left = par;
		newnode->right = par->right;
		par->rightLinkType = CHILD;
		par->right = newnode;
	}
} // end-add

///-----------------------------------------------
/// Removes a given key from the BST (if it exists)
/// 
void ThreadedBST::remove(int key) {
	// Fill this in
	BSTNode* ptr = this->root;
	BSTNode* par = NULL;
	int found = 0;

	while (ptr != NULL) {
		if (key == ptr->key) {
			found = 1;
			break;
		}
		par = ptr;
		if (key < ptr->key) {
			if (ptr->leftLinkType == CHILD)
				ptr = ptr->left;
			else
				break;
		}
		else {
			if (ptr->rightLinkType == CHILD )
				ptr = ptr->right;
			else
				break;
		}
	}

	if (found == 0)
		printf("dkey not present in tree\n");

	// Two Children
	else if (ptr->leftLinkType == CHILD && ptr->rightLinkType == CHILD) {
		struct BSTNode* parsucc = ptr;
		struct BSTNode* succ = ptr->right;

		// Find leftmost child of successor
		while (succ->left != NULL) {
			parsucc = succ;
			succ = succ->left;
		}

		ptr->key = succ->key;

		if (succ->leftLinkType == THREAD && succ->rightLinkType == THREAD)
			root = CaseA(root, parsucc, succ);
		else
			root = CaseB(root, parsucc, succ);

	}
		

	// Only Left Child
	else if (ptr->leftLinkType == CHILD)
		root = CaseB(root, par, ptr);

	// Only Right Child
	else if (ptr->rightLinkType == CHILD)
		root = CaseB(root, par, ptr);

	// No child
	else
		root = CaseA(root, par, ptr);


} // end-remove


struct BSTNode* inSucc(struct BSTNode* ptr)
{
	if (ptr->rightLinkType == THREAD)
		return ptr->right;

	ptr = ptr->right;
	while (ptr->leftLinkType == CHILD)
		ptr = ptr->left;

	return ptr;
}

struct BSTNode* inPred(struct BSTNode* ptr)
{
	if (ptr->leftLinkType == THREAD)
		return ptr->left;

	ptr = ptr->left;
	while (ptr->rightLinkType == CHILD )
		ptr = ptr->right;
	return ptr;
}


///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node  that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::find(int key) {
	// Fill this in
	BSTNode* p = this->root;
	BSTNode* pp = NULL;
	if (p == NULL)
		return NULL;
	while (p) {
		pp = p;
		if (p->key == key) return p;
		else if (p->key > key) {
			if (p->leftLinkType == CHILD)
				p = p->left;
			else break;
		}
		else if (p->key < key) {
			if (p->rightLinkType == CHILD)
				p = p->right;
			else break;
		}
	}
	return NULL;
} // end-find

///-----------------------------------------------
/// Returns the minimum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::min() {
	// Fill this in
	if (root == NULL) return NULL;
	BSTNode* p = root;
	BSTNode* pp = NULL;
	while (p) {
		pp = p;
		p = p->left;
	}
	return pp;
} // end-min

///-----------------------------------------------
/// Returns the maximum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::max() {
	// Fill this in
	if (root == NULL) return NULL;
	BSTNode* p = root;
	while (p->right) {
		p = p->right;
	}
	return p;
} // end-max

///-----------------------------------------------
/// Given a valid pointer to a node in ThreadedBST,
/// returns a pointer to the node that contains the inorder predecessor
/// If the inorder predecessor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::previous(BSTNode* node) {
	// Fill this in
	if (node == NULL) {
		return;
	}
	if (node->leftLinkType == CHILD) {
		node = node->left;
		if (node->leftLinkType == CHILD && node->rightLinkType == CHILD) {
			while (node->rightLinkType == CHILD)
			{
				node= node->right;
			}
			return node;
		}
		else
		{
			return node;
		}
	}
	while (node->rightLinkType == THREAD) {
		if (node->rightLinkType == THREAD && node->leftLinkType == THREAD)
			return node->left;
		node = node->right;
	}
	return node->right;
} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {
	// Fill this in
	if (node == NULL) {
		return;
	}
	if (node->rightLinkType == THREAD)
		return node->right;
	else
		node = node->right;
	while (node->leftLinkType == CHILD) {
		node = node->left;
	}
	return node;
} // end-next

BSTNode* ThreadedBST::CaseA(BSTNode* node, BSTNode* par, BSTNode* ptr)
{
	// If Node to be deleted is root
	if (par == NULL)
		root = NULL;

	// If Node to be deleted is left
	// of its parent
	else if (ptr == par->left) {
		par->leftLinkType = THREAD;
		par->left = ptr->left;
	}
	else {
		par->rightLinkType = THREAD;
		par->right = ptr->right;
	}

	// Free memory and return new root
	free(ptr);
	return root;

}

BSTNode* ThreadedBST::CaseB(BSTNode* node, BSTNode* par, BSTNode* ptr)
{
	struct BSTNode* child;

	// Initialize child Node to be deleted has
	// left child.
	if (ptr->leftLinkType == CHILD)
		child = ptr->left;

	// Node to be deleted has right child.
	else
		child = ptr->right;

	// Node to be deleted is root Node.
	if (par == NULL)
		root = child;

	// Node is left child of its parent.
	else if (ptr == par->left)
		par->left = child;
	else
		par->right = child;

	// Find successor and predecessor
	BSTNode* s = inSucc(ptr);
	BSTNode* p = inPred(ptr);

	// If ptr has left subtree.
	if (ptr->leftLinkType == CHILD)
		p->right = s;

	// If ptr has right subtree.
	else {
		if (ptr->rightLinkType == CHILD)
			s->left = p;
	}

	free(ptr);
	return root;
}

BSTNode* ThreadedBST::CaseC(BSTNode* node, BSTNode* par, BSTNode* ptr)
{
	// Find inorder successor and its parent.
	struct BSTNode* parsucc = ptr;
	struct BSTNode* succ = ptr->right;

	// Find leftmost child of successor
	while (succ->left != NULL) {
		parsucc = succ;
		succ = succ->left;
	}

	ptr->key = succ->key;

	if (succ->leftLinkType == THREAD && succ->rightLinkType == THREAD)
		root = CaseA(root, parsucc, succ);
	else
		root = CaseB(root, parsucc, succ);

	return root;
}
