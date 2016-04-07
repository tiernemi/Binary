/* test framework include */
#include "wvtest.h"

/* EDIT HERE: add your code include(s) */
#include "../bst.h"
#include "stdio.h"

/* EDIT HERE: write your tests */
#define N_TESTS 10000
#define SEED 97

WVTEST_MAIN("binary search tree tests - Testing remove functionality")
{
	bst *my_tree = NULL;
	my_tree = bst_create();
	bst_insert(my_tree, 7);
	bst_insert(my_tree, 2);
	bst_insert(my_tree, 11);
	bst_insert(my_tree, 9);
	bst_insert(my_tree, 1);

	// Test removal of all elements.
	WVPASSEQ(bst_remove(my_tree, 7),1) ;
	WVPASSEQ(bst_search(my_tree,7),0) ;
	WVPASSEQ(bst_remove(my_tree, 2),1) ;
	WVPASSEQ(bst_search(my_tree,2),0) ;
	WVPASSEQ(bst_remove(my_tree,11),1) ;
	WVPASSEQ(bst_search(my_tree,11),0) ;
	WVPASSEQ(my_tree->size,2) ;
	WVPASSEQ(my_tree->root->left->data,1) ;
	WVPASSEQ(bst_remove(my_tree, 9),1) ;
	WVPASSEQ(bst_search(my_tree,9),0) ;
	WVPASSEQ(bst_remove(my_tree, 1),1) ;
	WVPASSEQ(bst_search(my_tree,1),0) ;

	WVPASSEQ(bst_remove(my_tree, 1),0) ;
	bst_insert(my_tree, 7);
	bst_insert(my_tree, 2);
	bst_insert(my_tree, 11);
	// Test double child root removal. //
	WVPASSEQ(bst_remove(my_tree, 7),1) ;
	bst_insert(my_tree, 5);
	bst_insert(my_tree, 4);
	bst_insert(my_tree, 10);
	bst_insert(my_tree, 7);
	bst_insert(my_tree, 8);
	// Test single child removal. //
	WVPASSEQ(bst_remove(my_tree, 10),1) ;
	WVPASSEQ(bst_remove(my_tree, 8),1) ;
	// Test double child removal //
	WVPASSEQ(bst_remove(my_tree, 5),1) ;
	WVPASSEQ(bst_remove(my_tree, 7),1) ;

	bst_destroy(my_tree);
	my_tree = bst_create() ;

	// Test a lot of removals //
	int i = 0 ;
	for (i = -100 ; i < 600 ; ++i) {
		bst_insert(my_tree, i) ; 
	}
	for (i = 300 ; i < 500 ; ++i) {
		WVPASSEQ(bst_remove(my_tree,i),1) ;
	}



	bst_destroy(my_tree);
}

WVTEST_MAIN("binary search tree tests - Finding the min")
{
	bst *my_tree = NULL;
	my_tree = bst_create();
	bst_insert(my_tree, 7);
	bst_insert(my_tree, 2);
	bst_insert(my_tree, 11);
	bst_insert(my_tree, 9);
	bst_insert(my_tree, 1);
	WVPASSEQ(bst_find_min(my_tree),1) ;

	bst_insert(my_tree, -5);
	bst_insert(my_tree, 1000);
	bst_insert(my_tree, 10);
	bst_insert(my_tree, -150);
	WVPASSEQ(bst_find_min(my_tree),-150) ;

	// How it handles null pointers and empty trees. //
	bst *my_tree2 = NULL;
	WVPASSEQ(bst_find_min(my_tree2),0) ;
	my_tree2 = bst_create();
	WVPASSEQ(bst_find_min(my_tree2),0) ;
	bst_insert(my_tree2,1000) ;
	WVPASSEQ(bst_find_min(my_tree2),1000) ;

	bst_destroy(my_tree);
	bst_destroy(my_tree2);
}

WVTEST_MAIN("binary search tree tests - Finding the max")
{
	bst *my_tree = NULL;
	my_tree = bst_create();
	bst_insert(my_tree, 7);
	bst_insert(my_tree, 2);
	bst_insert(my_tree, 11);
	bst_insert(my_tree, 9);
	bst_insert(my_tree, 1);
	WVPASSEQ(bst_find_max(my_tree),11) ;

	bst_insert(my_tree, -5);
	bst_insert(my_tree, 1000);
	bst_insert(my_tree, 10);
	bst_insert(my_tree, -150);
	WVPASSEQ(bst_find_max(my_tree),1000) ;

	// How it handles null pointers and empty trees. //
	bst *my_tree2 = NULL;
	WVPASSEQ(bst_find_max(my_tree2),0) ;
	my_tree2 = bst_create();
	WVPASSEQ(bst_find_max(my_tree2),0) ;
	bst_insert(my_tree2,1000) ;
	WVPASSEQ(bst_find_max(my_tree2),1000) ;

	bst_destroy(my_tree);
	bst_destroy(my_tree2);
}



WVTEST_MAIN("binary search tree tests - performance of search after randomly ordered insert")
{
	/* init the hash table */
	bst *my_tree = NULL;
	my_tree = bst_create();
	WVPASSEQ(bst_size(my_tree), 0);

	/* seed rng */
	srand48(SEED);

	/* store 3 values that are definitely in the tree */
	int existing0;
	int existing1;
	int existing2;

	int i;
	for (i=0; i<N_TESTS; i++) {
		printf("hi\n");
		int k = (int)(N_TESTS * drand48());
		bst_insert(my_tree, k);

		/* store the values */
		if      (i == N_TESTS/4) existing0 = k;
		else if (i == N_TESTS/3) existing1 = k;
		else if (i == N_TESTS/2) existing2 = k;
	}

	/* search for existing entries */
	WVPASS(bst_search(my_tree, existing0));
	WVPASS(bst_search(my_tree, existing1));
	WVPASS(bst_search(my_tree, existing2));

	/* search for non-existing entries */
	WVFAIL(bst_search(my_tree, 2 * N_TESTS));
	WVFAIL(bst_search(my_tree, 3 * N_TESTS));
	WVFAIL(bst_search(my_tree, 4 * N_TESTS));

	/* tidy up */
	bst_destroy(my_tree);
}


WVTEST_MAIN("binary search tree tests - performance of search after linearly ordered insert (effectively linked list)")
{
	/* init the hash table */
	bst *my_tree = NULL;
	my_tree = bst_create();
	WVPASSEQ(bst_size(my_tree), 0);

	int i;
	for (i=0; i<N_TESTS; i++) {
		bst_insert(my_tree, i);
	}

	/* search for existing entries */
	WVPASS(bst_search(my_tree, N_TESTS/4));
	WVPASS(bst_search(my_tree, N_TESTS/3));
	WVPASS(bst_search(my_tree, N_TESTS/2));

	/* search for non-existing entries */
	WVFAIL(bst_search(my_tree, 2 * N_TESTS));
	WVFAIL(bst_search(my_tree, 3 * N_TESTS));
	WVFAIL(bst_search(my_tree, 4 * N_TESTS));

	/* tidy up */
	bst_destroy(my_tree);
}


WVTEST_MAIN("binary search tree tests - search")
{
	/* init the hash table */
	bst *my_tree = NULL;
	my_tree = bst_create();
	WVPASSEQ(bst_size(my_tree), 0);

	bst_insert(my_tree, 7);
	bst_insert(my_tree, 2);
	bst_insert(my_tree, 11);
	bst_insert(my_tree, 9);
	bst_insert(my_tree, 1);
	bst_insert(my_tree, 53);
	bst_insert(my_tree, 99);
	bst_insert(my_tree, 17);
	bst_insert(my_tree, 3);
	bst_insert(my_tree, 4);

	/* search for existing entries */
	WVPASS(bst_search(my_tree, 1));
	WVPASS(bst_search(my_tree, 53));

	/* search for non-existing entries */
	WVFAIL(bst_search(my_tree, 43));
	WVFAIL(bst_search(my_tree, 5));

	/* tidy up */
	bst_destroy(my_tree);
}


WVTEST_MAIN("binary search tree tests - pre-order traversal")
{
	/* init the hash table */
	bst *my_tree = NULL;
	my_tree = bst_create();
	WVPASSEQ(bst_size(my_tree), 0);

	bst_insert(my_tree, 7);
	bst_insert(my_tree, 2);
	bst_insert(my_tree, 11);
	bst_insert(my_tree, 9);
	bst_insert(my_tree, 1);
	bst_insert(my_tree, 53);
	bst_insert(my_tree, 99);
	bst_insert(my_tree, 17);
	bst_insert(my_tree, 3);
	bst_insert(my_tree, 4);

	/* temp string for display */
	char *str = NULL;

	// malloc 4 chars per entry (' 100'), and enough for twice the current size
	str = (char *) malloc(bst_size(my_tree) * 2 * 4 * sizeof(char));

	/* write out the tree to the given string, using a 'pre-order' traversal */
	/* note that pre-order means: root first, left child, right child */
	/* this shows the structure of the tree */
	bst_preorder_tostring(my_tree, str);
	WVPASSEQSTR(str, "7 2 1 3 4 11 9 53 17 99 ");


	// reset the string
	str[0] = '\0';
	bst_insert(my_tree, 42);
	bst_preorder_tostring(my_tree, str);
	WVPASSEQSTR(str, "7 2 1 3 4 11 9 53 17 42 99 ");

	/* tidy up */
	bst_destroy(my_tree);
	free(str);
}

WVTEST_MAIN("binary search tree tests - in-order traversal")
{
	/* init the hash table */
	bst *my_tree = NULL;
	my_tree = bst_create();
	WVPASSEQ(bst_size(my_tree), 0);

	bst_insert(my_tree, 7);
	bst_insert(my_tree, 2);
	bst_insert(my_tree, 11);
	bst_insert(my_tree, 9);
	bst_insert(my_tree, 1);
	bst_insert(my_tree, 53);
	bst_insert(my_tree, 99);
	bst_insert(my_tree, 17);
	bst_insert(my_tree, 3);
	bst_insert(my_tree, 4);

	/* temp string for display */
	char *str = NULL;

	// malloc 4 chars per entry (' 100'), and enough for twice the current size
	str = (char *) malloc(bst_size(my_tree) * 2 * 4 * sizeof(char));

	/* write out the tree to the given string, using an 'in-order' traversal */
	/* note that pre-order means: left child, root, right child */
	/* this produces a sorted sequence */
	bst_inorder_tostring(my_tree, str);
	WVPASSEQSTR(str, "1 2 3 4 7 9 11 17 53 99 ");


	// reset the string
	str[0] = '\0';
	bst_insert(my_tree, 42);
	bst_inorder_tostring(my_tree, str);
	WVPASSEQSTR(str, "1 2 3 4 7 9 11 17 42 53 99 ");

	/* tidy up */
	bst_destroy(my_tree);
	free(str);
}

WVTEST_MAIN("binary search tree tests - insert/sizes")
{
	/* init the hash table */
	bst *my_tree = NULL;
	my_tree = bst_create();
	WVPASSEQ(bst_size(my_tree), 0);

	bst_insert(my_tree, 7);
	WVPASSEQ(bst_size(my_tree), 1);

	bst_insert(my_tree, 2);
	WVPASSEQ(bst_size(my_tree), 2);

	bst_insert(my_tree, 11);
	WVPASSEQ(bst_size(my_tree), 3);

	/* no duplicates */
	bst_insert(my_tree, 11);
	WVPASSEQ(bst_size(my_tree), 3);

	bst_insert(my_tree, 9);
	WVPASSEQ(bst_size(my_tree), 4);

	bst_insert(my_tree, 1);
	WVPASSEQ(bst_size(my_tree), 5);

	/* tidy up */
	bst_destroy(my_tree);
}

WVTEST_MAIN("binary search tree tests - create/destroy")
{
	/* init the hash table */
	bst *my_tree = NULL;
	my_tree = bst_create();

	WVPASSEQ(bst_size(my_tree), 0);

	/* tidy up */
	bst_destroy(my_tree);
}

