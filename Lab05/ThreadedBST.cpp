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

} // end-remove

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
	
} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
/// 
BSTNode* ThreadedBST::next(BSTNode* c) {
	// Fill this in
	if (c->rightLinkType == THREAD)
		return c->right;
	else
		c = c->right;
	while (c->leftLinkType == CHILD) {
		c = c->left;
	}
	return c;
} // end-next