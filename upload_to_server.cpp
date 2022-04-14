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
tree_t* tree_splay(tree_t* tree, int value);
tree_t* add_node(tree_t* tree, int value)
{
	if (tree == NULL)
	{
		tree = (tree_t*)malloc(sizeof(tree_t));
		if (tree== NULL) {
			return NULL;
		}
		tree->key = value;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}
	if(value == tree->key){
		return tree;
	}
	if (value < tree->key)
	{
		tree->left = add_node(tree->left, value);
	}
	else
	{
		tree->right = add_node(tree->right, value);
	}
	return tree;
}


tree_t* rotate_right(tree_t* tree)
{
	tree_t* tmp = tree->left;
	tree->left = tmp->right;
	tmp->right = tree;
	return tmp;
}

tree_t* rotate_left(tree_t* tree)
{
	tree_t* tmp = tree->right;
	tree->right = tmp->left;
	tmp->left = tree;
	return tmp;
}

tree_t* tree_splay(tree_t* tree, int value)
{

	if (!tree)
		return tree;
	if (tree->key == value)
		return tree;
	if (tree->key > value)
	{
		if (tree->left == NULL)
			return tree;

		if (tree->left->key > value)
		{
			tree->left->left = tree_splay(tree->left->left, value);
			tree = rotate_right(tree);
		}
		else if (tree->left->key < value)
		{
			tree->left->right = tree_splay(tree->left->right, value);

			if (tree->left->right)
				tree->left = rotate_left(tree->left);
		}
		if (tree->left == NULL)
			return tree;
		else
			return rotate_right(tree);
	}
	else
	{
		if (!tree->right)
			return tree;

		if (tree->right->key > value)
		{
			tree->right->left = tree_splay(tree->right->left, value);

			if (tree->right->left)
				tree->right = rotate_right(tree->right);
		}
		else if (tree->right->key < value)
		{
			tree->right->right = tree_splay(tree->right->right, value);
			tree = rotate_left(tree);
		}

		if (!tree->right)
			return tree;
		else
			return rotate_left(tree);
	}
}

tree_t* remove_node(tree_t* tree, int value)
{
	if (!tree)
		return NULL;
	tree_t* tmp;
	tree = tree_splay(tree, value);
	if (tree->key != value)
		return tree;
	tmp = tree;
	if (!tree->left)
	{
		tree = tree->right;
	}
	else
	{
		tree = tree_splay(tree->left, value);
		tree->right = tmp->right;
	}
	return tree;
}

tree_t* find_node(tree_t* t, int key)
{
	tree_t* temp = NULL;
	if (t == NULL )
		return NULL;
	if (t->key == key)
		return t;
	else {
		if (key < t->key)
			temp = find_node(t->left, key);
		else
			temp = find_node(t->right, key);
	}
	return temp;
}


void print_tree(tree_t* tree, int x)
{
	int i;
	if (tree)
	{
		print_tree(tree->right, x + 1);
		for (i = 0; i < x; i++)
			printf("       ");
		printf("%i\n", tree->key);
		print_tree(tree->left, x + 1);
	}

}


void destroy_tree(tree_t* tree)
{
	if (!tree)
		return;
	if (tree)
	{
		destroy_tree(tree->left);
		destroy_tree(tree->right);
		free(tree);
	}
}
int main()
{
	char func;
	int value;
	tree_t* tree = NULL;
	while (fscanf(stdin,"%c %i", &func, &value) > 0)
	{
		switch (func)
		{
		case 'a':
			tree = add_node(tree, value);
			break;
		case 'r':
			tree = remove_node(tree, value);
			break;
		case 'f':
			tree = tree_splay(tree, value);
			if(tree)
			{
			if (tree->key == value)
				printf("yes\n");
			else
				printf("no\n");
			}
			else
			{
				printf("no\n");
			}
			break;

		}


	}
	destroy_tree(tree);

}