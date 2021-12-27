#include "tree.h"
void free_node(bin_tree* root)
{
	if (root == NULL)
		return;
	free_node(root->left);
	free_node(root->right);
	free(root);
}
int left_of(const int value, const bin_tree* root)
{
	return value < root->key;
}

int right_of(const int value, const bin_tree* root)
{
	return value > root->key;
}
bin_tree* insert_node(bin_tree* root, const int value)
{
	if (root == NULL)
	{
		bin_tree* node = (bin_tree*)malloc(sizeof(bin_tree));
		node->left = NULL;
		node->right = NULL;
		node->key = value;
		return node;
	}
	if (left_of(value, root))
		root->left = insert_node(root->left, value);
	else if (right_of(value, root))
		root->right = insert_node(root->right, value);
	return root;
}
bool search_node(const bin_tree* root, int value)
{
	if (root == NULL)
		return false;
	if (root->key == value) {
		return true;
	}
	else if (left_of(value, root)) {
		return search_node(root->left, value);
	}
	else if (right_of(value, root)) {
		return search_node(root->right, value);
	}
}
int left_most_value(const bin_tree* root)
{
	while (root->left != NULL)
		root = root->left;
	return root->key;
}
bin_tree* remove_node(bin_tree* root, int value)
{
	if (root == NULL)
		return root;
	if (left_of(value, root))
		root->left = remove_node(root->left, value);
	else if (right_of(value, root))
		root->right = remove_node(root->right, value);
	else
	{
		if (root->left == NULL)
		{
			bin_tree* new_root = root->right;
			free(root);
			return new_root;
		}
		if (root->right == NULL)
		{
			bin_tree* new_root = root->left;
			free(root);
			return new_root;
		}
		root->key = left_most_value(root->right);
		root->right = remove_node(root->right, root->key);
	}
	return root;
}