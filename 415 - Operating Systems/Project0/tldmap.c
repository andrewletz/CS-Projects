/*
CIS 415 Project 0
Author: Andrew Letz
Duck ID: aletz
This is my own work except for:
- Used Cormen et al. "Introduction to Algorithms" 3rd edition
for BST pseudo-code implementation
- Used Dr. Sventek's stack, queue implementations for guidance
*/
#include "tldmap.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h> // IBM's library for strcasecmp()
#include <stdio.h>

// BST node implementation
struct tldnode {
	char* key; // tld stored here
	long count;
	TLDNode *left;
	TLDNode *right;
	TLDNode *parent;
};

/*
 * find the node corresponding to *theTLD, returning a pointer to it if found
 * returns NULL otherwise
*/
static TLDNode *tld_search(const TLDMap *tld, char *theTLD) {
	TLDNode *start = tld->self; // get root of bst
//	printf("\n** tld_search **\n");
	while (start != NULL && start->key != NULL) {
		//printf("tld_search: while\n");
		if (strcasecmp(start->key, theTLD) != 0) { // tlds aren't equal
			//printf("tld_search: compared strings\n");
			if (strcasecmp(theTLD, start->key) < 0) { // theTLD < current nodes tld
				start = start->left; // go left
			} else {
				start = start->right; // go right
			}
		} else { // found the tld
			return start; // success
		}
	}
	return NULL; // not found
}

/*
 * in order traverse tld, performing nodeFunc on each node found
*/
static void tld_inorder(TLDNode *root, void (*nodeFunc)(TLDNode *node)) {
	if (root != NULL) {
		TLDNode *left = root->left;
		TLDNode *right = root->right;

		tld_inorder(left, nodeFunc);
		(*nodeFunc)(root);
		tld_inorder(right, nodeFunc);
	}
}

/*
 * release all allocated memory from input node
*/
static void tld_releaseNode(TLDNode *node) {
	free(node->key);
	free(node);
}

static void tld_destroy(const TLDMap *tld) {
	TLDNode *root = (TLDNode *)tld->self; // get root

	tld_inorder(root, &tld_releaseNode); // in order traverse, freeing nodes as we go
	free((void *)tld); // free overall structure
}

static int tld_insert(const TLDMap *tld, char *theTLD, long v) {
	TLDNode *root = (TLDNode *)tld->self;
	//printf("\n ** tld_insert **\n");
	if (root->key == NULL) { // tree is empty
	//	printf("tld_insert: tree is empty\n");
		root->key = malloc(strlen(theTLD) + 1); // allocate space so key isn't NULL
		strcpy(root->key, theTLD);
	//	printf("tld_insert: copied into root key\n");
		root->count = v;
		root->left = NULL;
		root->right = NULL;
		return 1; // inserted into root
	}
	
	// if tree wasn't empty, continue
	TLDNode *searchNode = tld_search(tld, theTLD);
//	printf("tld_insert: search node returned\n");
	if (searchNode != NULL) { // already exists
//		printf("tld_insert: node already exists\n");
		return 0;
	}

	// primary insert logic, root existed and theTLD is a new key
	TLDNode *z = (TLDNode *)malloc(sizeof(TLDNode));
	if (z != NULL) {
		z->key = malloc(strlen(theTLD) + 1); // allocate space so key isn't NULL
		strcpy(z->key, theTLD);
		z->count = v;
		z->left = NULL;
		z->right = NULL;
		z->parent = NULL;

//		printf("tld_insert: z initialized\n");

		TLDNode *y = NULL;
		TLDNode *x = root; // x starts as the root
		while (x != NULL) {
			y = x;
			if (strcasecmp(z->key, x->key) < 0) {
				x = x->left;
			} else {
				x = x->right;
			}
		}
		z->parent = y;
		if (strcasecmp(z->key, y->key) < 0) {
			y->left = z;
		} else {
			y->right = z;
		}
	} else {
		free(z->key);
		free(z);
		z = NULL;
		return 0; // couldn't allocate properly, don't return successful
	}
	return 1;
}

static int tld_reassign(const TLDMap *tld, char *theTLD, long v) {
	TLDNode *desired = tld_search(tld, theTLD);
	if (desired != NULL) {
		desired->count = v;
		return 1;
	}
	return 0;
}

static int tld_lookup(const TLDMap *tld, char *theTLD, long *v) {
	TLDNode *desired = tld_search(tld, theTLD);
	if (desired != NULL) {
		*v = desired->count;
		return 1;
	}
	return 0;
}

/*
 * in order traverse to get size of the bst whose root is input
 * stores the result in n
*/
static void tld_getSize(TLDNode *root, long *n) {
	if (root != NULL) {
		TLDNode *left = root->left;
		TLDNode *right = root->right;

		tld_getSize(left, n);
		*n += 1;
		tld_getSize(right, n);
	}	
}

/*
 * in order traverse tld, duplicating each node into the input array
*/
static void tld_inorderCopy(TLDNode *root, void **inputArr, long *index) {
//	printf("\n ** tld_inorderCopy **\n");
	if (root != NULL) {
	//	printf("tld_inorderCopy: root isn't null, index is %i\n", (int) *index);
		TLDNode *left = root->left;
		TLDNode *right = root->right;

		tld_inorderCopy(left, inputArr, index);
	//	printf("tld_inorderCopy: before memcpy: index of %i\n", (int) *index);
		//memcpy(inputArr[*index], root, sizeof(void *));
		inputArr[*index] = root;
	//	printf("tld_inorderCopy: memcpy executed with index of %i\n", (int) *index);
		*index += 1;
		tld_inorderCopy(right, inputArr, index);
	}	
}

static const Iterator *tld_itCreate(const TLDMap *tld) {
	const Iterator *it = NULL;
	long numNodes = 0;
	tld_getSize(tld->self, &numNodes); // store # of nodes in numNodes
//	printf("tld_itCreate: we have %i nodes\n", (int) numNodes);
	void **nodeArr = (void **)malloc(sizeof(void *) * numNodes); // allocate nodeArr

	if (nodeArr != NULL) {
	//	printf("tld_itCreate: nodeArr allocated successfully\n");
		long index = 0;
		tld_inorderCopy(tld->self, nodeArr, &index); // copy all nodes into nodeArr
		it = Iterator_create(numNodes, nodeArr);
		if (it == NULL) {
			free(nodeArr);
		}
	} else {
		free(nodeArr);
	}
	return it;
}

char *TLDNode_tldname(TLDNode *node) {
	return node->key;
}

long TLDNode_count(TLDNode *node) {
	return node->count;
}

static TLDMap template = {
	NULL, tld_destroy, tld_insert, tld_reassign, tld_lookup, tld_itCreate
};

const TLDMap *TLDMap_create(void) {
	TLDMap *bst = (TLDMap *)malloc(sizeof(TLDMap));

	if (bst != NULL) {
		TLDNode *root = (TLDNode *)malloc(sizeof(TLDNode));

		if (root != NULL) {
			root->key = NULL;
			root->count = 0;
			root->left = NULL;
			root->right = NULL;
			root->parent = NULL;
			*bst = template;
			bst->self = root;
		} else {
			free(root);
			free(bst);
			bst = NULL;
		}
	} else {
		free(bst);
		bst = NULL;
	}
	return bst;
}
