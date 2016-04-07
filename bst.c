#include <stdio.h>
#include <string.h>

#include "bst.h"


/*
 ******************************************************************************
 * Create a new binary search tree.
 * Return the new pointer.
 ******************************************************************************
 */
bst *bst_create() {
	bst *my_tree;

	if (! (my_tree = (bst *)malloc(sizeof(bst)))) return NULL;

	my_tree->root = NULL;
	my_tree->size = 0;

	return my_tree;
}


/*
 * Helper function:
 * Destroy the nodes in the tree recursively.
 */
void bst_destroy_recursive(struct bstnode_s *node) {
	if (node == NULL) {
		// empty child - do nothing
		return;
	} else if (node->left == NULL && node->right == NULL) {
		// no children, so free this child
		free(node);
		return;
	} 


	// ok, so we have some children, at least on one side, but possibly
	// on both

	if (node->left) {
		// children on one side - free them
		bst_destroy_recursive(node->left);
	}

	if (node->right) {
		// children on one side - free them
		bst_destroy_recursive(node->right);
	}

	// then the parent node itself
	free(node);
}


/*
 ******************************************************************************
 * Destroy the binary search tree cleanly, freeing all memory.
 * If the tree is empty, then nothing to do. Otherwise
 * call the recursive destroy function.
 ******************************************************************************
 */
void bst_destroy(bst *my_tree) {
	if (my_tree == NULL) {
		// nothing to do!
		return;
	}

	// recursively free the nodes
	bst_destroy_recursive(my_tree->root);

	// and finally the binary search tree struct itself
	free(my_tree);
}


/*
 ******************************************************************************
 * Return the current size.
 ******************************************************************************
 */

int bst_size(bst *my_tree) {
	return my_tree->size;
}


/*
 * Helper function:
 * Perform the search recursively - binary search.
 * Return 1 for sucessful search, 0 for failure.
 */

int bst_search_recursive(struct bstnode_s *node, int data) {
	if (data > node->data) {
		if (node->right != NULL) {
			return bst_search_recursive(node->right,data) ; // Go right
		}
		else {
			return 0 ;
		}
	} else if (data < node->data) {
		if (node->left != NULL) {
			return bst_search_recursive(node->left,data) ; // Go left
		} else {
			return 0 ;
		}
	} else {
		return 1 ; // Found the value
	}
}

/*
 ******************************************************************************
 * Search for a value recursively - binary search.
 * If the tree is empty, then not found. Otherwise search
 * recursively.
 * Return 1 for sucessful search, 0 for failure.
 ******************************************************************************
 */

int bst_search(bst *my_tree, int data) {
	if (my_tree->root == NULL) {
		return 0;	// empty tree - return false
	} else {
		return bst_search_recursive(my_tree->root, data);
	}
}

/*
 * Helper function:
 * Recursive insert.
 * Do not insert duplicate values.
 * Return 1 for sucessful insert, 0 for failure.
 */

int bst_insert_recursive(struct bstnode_s *node, int data) {
	if (data > node->data) {
		if (node->right != NULL) { 
			return bst_insert_recursive(node->right,data) ; // Go right
		} else {
			if (! (node->right = (struct bstnode_s *) malloc(sizeof(struct bstnode_s)))) {
				return 0 ;
			} else {
				node->right->data = data ;
				node->right->left = NULL ;
				node->right->right = NULL ;
				return 1 ;
			}
		}
	} else if (data < node->data) {
		if (node->left != NULL) { 
			return bst_insert_recursive(node->right,data) ; // Go right
		} else {
			if (! (node->left = (struct bstnode_s *) malloc(sizeof(struct bstnode_s)))) {
				return 0 ;
			} else {
				node->left->data = data ;
				node->left->left = NULL ;
				node->left->right = NULL ;
				return 1 ;
			}
		}
	} else {
		return 0 ; // Duplicates
	}
}

/*
 ******************************************************************************
 * Insert a (unique) value into the tree.
 * Do not insert duplicate values.
 * If the tree is empty, it's the new root. Otherwise,
 * do a recursive insert.
 * Return 1 for sucessful insert, 0 for failure.
 ******************************************************************************
 */
int bst_insert(bst *my_tree, int data) {
	struct bstnode_s *node;

	// empty tree?
	if (my_tree->root == NULL) {
		if (! (node=(struct bstnode_s *)malloc(sizeof(struct bstnode_s))) ) return 0; // return fail
		node->left  = NULL;
		node->right = NULL;
		node->data  = data;

		my_tree->root = node;
		my_tree->size = 1;

		return 1;
	} else {
		if (bst_insert_recursive(my_tree->root, data)) {
			my_tree->size++;
			return 1;
		} else {
			return 0;
		}
	}
}

/*
 * Helper function:
 * Traverse the tree in-order (left, root, right).
 * Append each value to the string 'str'.
 * Assumes that the string has been allocated and has enough
 * space to hold all the values.
 */
void bst_inorder_tostring_recursive(struct bstnode_s *node, char *str) {
	char buf[10];

	if (node == NULL) {
		return;
	} else {
		bst_inorder_tostring_recursive(node->left, str);

		sprintf(buf, "%d ", node->data);
		strcat(str, buf);

		bst_inorder_tostring_recursive(node->right, str);
	}
}


/*
 ******************************************************************************
 * Traverse the tree in-order (left, root, right).
 * Append each value to the string 'str'.
 * Assumes that the string has been allocated and has enough
 * space to hold all the values.
 ******************************************************************************
 */
void bst_inorder_tostring(bst *my_tree, char *str) {
	char buf[10];

	// initialise the string (assumes it has already been allocated)
	*str = '\0';

	// empty tree?
	if (my_tree->root == NULL) {
		return;
	} else {
		bst_inorder_tostring_recursive(my_tree->root->left, str);

		sprintf(buf, "%d ", my_tree->root->data);
		strcat(str, buf);

		bst_inorder_tostring_recursive(my_tree->root->right, str);
	}
}

/*
 * Helper function:
 * Traverse the tree pre-order (root, left, right).
 * Append each value to the string 'str'.
 * Assumes that the string has been allocated and has enough
 * space to hold all the values.
 */

void bst_preorder_tostring_recursive(struct bstnode_s *node, char *str) {
	char buf[10];

	if (node == NULL) {
		return;
	} else {
		sprintf(buf, "%d ", node->data);
		strcat(str, buf);

		bst_preorder_tostring_recursive(node->left, str);
		bst_preorder_tostring_recursive(node->right, str);
	}
}


/*
 ******************************************************************************
 * Traverse the tree pre-order (root, left, right).
 * Append each value to the string 'str'.
 * Assumes that the string has been allocated and has enough
 * space to hold all the values.
 ******************************************************************************
 */
void bst_preorder_tostring(bst *my_tree, char *str) {
	char buf[10];

	// initialise the string (assumes it has already been allocated)
	*str = '\0';

	// empty tree?
	if (my_tree->root == NULL) {
		return;
	} else {
		sprintf(buf, "%d ", my_tree->root->data);
		strcat(str, buf);

		bst_preorder_tostring_recursive(my_tree->root->left, str);
		bst_preorder_tostring_recursive(my_tree->root->right, str);
	}
}


/*
 ******************************************************************************
 * Print the tree to stdout.
 * Use the bst_inorder_tostring() to traverse the tree
 * in-order and print the resultant string
 * to stdout.
 ******************************************************************************
 */
void bst_display(bst *my_tree) {
	/* temp string for display */
	char *str = NULL;

	// malloc 4 chars per entry (' 100'), and enough for twice the current size
	str = (char *) malloc(bst_size(my_tree) * 2 * 4 * sizeof(char));

	bst_inorder_tostring(my_tree, str);

	printf("BST contains: %s\n", str);

	free(str);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  bst_find_min_recur
 *    Arguments:  
 *      Returns:  
 *  Description:  
 * =====================================================================================
 */

int bst_find_min_recur(struct bstnode_s * node) {
	if (node->left != NULL) {
		return bst_find_min_recur(node->left) ;
	} else {
		return node->data ;
	}
}		/* -----  end of function bst_find_min_recur  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  bst_find_min
 *    Arguments:  bst * tree - The tree of which we're finding the minimum.
 *      Returns:  Minimum value present in binary tree. Default return value of 0.
 *  Description:  Finds the minimum value present in the tree.
 * =====================================================================================
 */

int bst_find_min(bst * tree) {
	if (tree == NULL) {
		return 0 ;
	} else {
		if (tree->root == NULL) {
			return 0 ;
		} else {
			return bst_find_min_recur(tree->root) ;
		}
	}
}		/* -----  end of function bst_find_min  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  bst_find_max_recur
 *    Arguments:  
 *      Returns:  
 *  Description:  
 * =====================================================================================
 */

int bst_find_max_recur(struct bstnode_s * node) {
	if (node->right != NULL) {
		return bst_find_max_recur(node->right) ;
	} else {
		return node->data ;
	}
}		/* -----  end of function bst_find_max_recur  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  bst_find_max
 *    Arguments:  bst * tree - The tree of which we're finding the maximum.
 *      Returns:  Minimum value present in binary tree. Default return value of 0.
 *  Description:  Finds the maximum value present in the tree.
 * =====================================================================================
 */

int bst_find_max(bst * tree) {
	if (tree == NULL) {
		return 0 ;
	} else {
		if (tree->root == NULL) {
			return 0 ;
		} else {
			return bst_find_max_recur(tree->root) ;
		}
	}
}		/* -----  end of function bst_find_max  ----- */

enum {
	FAILURE,
	SUCCESS,
	NO_CHILDREN,
	ONE_CHILD,
} ;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  bst_remove_recur
 *    Arguments:  
 *      Returns:  
 *  Description:  
 * =====================================================================================
 */

int bst_remove_recur(struct bstnode_s * node, int data) {
	if (data > node->data) {
		if (node->right != NULL) {
			int returnState = bst_remove_recur(node->right,data) ;
			if (returnState == NO_CHILDREN) {
				free(node->right) ;
				node->right = NULL ;
				return SUCCESS ;
			} else if (returnState == ONE_CHILD) {
				struct bstnode_s * temp = node->right ;
				node->right = node->right->right ;
				free(temp) ;
			} 
			return returnState ;
		}
		else {
			return FAILURE ;
		}
	} else if (data < node->data) {
		if (node->left != NULL) {
			int returnState = bst_remove_recur(node->left,data) ;
			if (returnState == NO_CHILDREN) {
				free(node->left) ;
				node->left = NULL ;
				return SUCCESS ;
			} else if (returnState == ONE_CHILD) {
				struct bstnode_s * temp = node->left ;
				node->left = node->left->left ;
				free(temp) ;
			} 
			return returnState ;
		}
		else {
			return FAILURE ;
		}
	} else {
		if (node->left == NULL) {
			if (node->right == NULL) {
				return NO_CHILDREN ;
			} else {
				return ONE_CHILD ;
			}
		} else if (node->right == NULL) {
			if (node->left == NULL) {
				return NO_CHILDREN ;
			} else {
				return ONE_CHILD ;
			}
		} else {
			int newVal = bst_find_min_recur(node) ;
			node->data = newVal ;
			bst_remove_recur(node->right, newVal) ;
			return SUCCESS ;
		}
	}
}		/* -----  end of function bst_remove_recur  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  bst_remove
 *    Arguments:  bst * tree - The tree from which we're removing the data.
 *                int data - Data to remove.
 *      Returns:  1 if sucessful, 0 otherwise
 *  Description:  Traverses the binary tree and removes the node containing data, the
 *                function then reconfigures the tree such that it still fulfills the
 *                criteria for being a bst.
 * =====================================================================================
 */

int bst_remove(bst * tree, int data) {
	if (tree != NULL) {
		if (tree->root != NULL) {
			return bst_remove_recur(tree->root, data) ;
		} else {
			return 0 ;
		}
	} else {
		return 0 ;
	}
}		/* -----  end of function bst_remove  ----- */


