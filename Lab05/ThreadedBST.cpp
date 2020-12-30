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
	return NULL;
} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {
	// Fill this in
	BSTNode* p = node;
	BSTNode* pp = node->left;
	if (p == NULL) return NULL;
	if (p->left == NULL) return p->right;
	if (p->right == NULL)
		return NULL;
	if (p->key<root->key) {
		while (p->leftLinkType == CHILD && p->rightLinkType == CHILD) {
			if (p->left->left == NULL) {
				p = p->right;
			}
			p = p->left;
			if (pp == p) {
				return p->right->right;
			}
			if (p->leftLinkType == THREAD && p->rightLinkType == THREAD)
				return p;
		}
		return p->right;
	}
	else {
		while (p->leftLinkType == CHILD && p->rightLinkType == CHILD)
		{
			if (p == root) {
				p = p->right;
				continue;
			}
			p = p->left;
			if (pp == p) {
				return p->right->right;
			}
			if (p->leftLinkType == CHILD && p->rightLinkType == THREAD) {
				return p->left;
			}
			if (p->leftLinkType == THREAD && p->rightLinkType == THREAD) {
				return p;
			}
		}
		if (p->right != NULL) {
			return p->right;
		}
		else {
			return p->left;
		}
	}
} // end-next