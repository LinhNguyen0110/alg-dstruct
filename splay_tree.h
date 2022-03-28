#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#pragma warning (disable : 4996)
typedef struct splay_tree
{
	int key;
	struct splay_tree* left, * right;
} tree_t;
tree_t* add_node(tree_t* tree, int value);
tree_t* rotate_right(tree_t* tree);
tree_t* rotate_left(tree_t* tree);
tree_t* tree_splay(tree_t* tree, int value);
tree_t* remove_node(tree_t* tree, int value);
tree_t* find_node(tree_t* t, int key);
void print_tree(tree_t* tree, int x);
void destroy_tree(tree_t* tree);


