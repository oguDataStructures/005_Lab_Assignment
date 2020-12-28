#include "ThreadedBST.h"

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
	BSTNode* p = this->root;
	BSTNode* pp = NULL;
	if (!this->root) {
		this->root = newnode;
		return;
	}
	while (p) {
		pp = p;
		if (p->key == key) return;
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
	if (pp->key > key) {
		newnode->left = pp->left;
		newnode->right = pp;
		pp->leftLinkType = CHILD;
		pp->left = newnode;
	}
	else {
		newnode->left = pp;
		newnode->right = pp->right;
		pp->rightLinkType = CHILD;
		pp->right = newnode;
	}
} // end-add

///-----------------------------------------------
/// Removes a given key from the BST (if it exists)
/// 
void ThreadedBST::remove(int key) {
	// Fill this in
} // end-remove

///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode *ThreadedBST::find(int key) {
	// Fill this in
	return NULL;
} // end-find

///-----------------------------------------------
/// Returns the minimum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::min() {
	// Fill this in
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
	return NULL;
} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {
	// Fill this in
	return node->right;
} // end-next