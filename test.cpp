#include "pch.h"
#include "../4_Linh_Nguyen_H_40/splay_tree.cpp"
TEST(test_add, test1) {
	tree_t* tree = NULL;
	//tree_t* tree = NULL;
	tree = add_node(tree, 20);
	tree = add_node(tree, 30);
	tree = add_node(tree, 50);
	tree = add_node(tree, 40);
	EXPECT_TRUE(tree->right->key, 30);
	tree = tree->right;
	EXPECT_TRUE(tree->right->key, 50);
	tree = tree->right;
	EXPECT_TRUE(tree->left->key, 40);
	destroy_tree(tree);
}
TEST(test_rotate_left, test2) {
	tree_t* tree = NULL;
	//tree_t* tree = NULL;
	tree = add_node(tree, 20);
	tree = add_node(tree, 30);
	tree = add_node(tree, 50);
	tree = add_node(tree, 40);
	tree = rotate_left(tree);
	EXPECT_TRUE(tree->key, 30);
	EXPECT_TRUE(tree->left->key, 20);
	EXPECT_TRUE(tree->right->key, 50);
	destroy_tree(tree);
}
TEST(test_rotate_right, test3) {
	tree_t* tree = NULL;
	tree = add_node(tree, 30);
	tree = add_node(tree, 20);
	tree = add_node(tree, 10);
	tree = rotate_right(tree);
	EXPECT_TRUE(tree->key, 30);
	EXPECT_TRUE(tree->left->key, 10);
	EXPECT_TRUE(tree->right->key, 30);
	destroy_tree(tree);
}
TEST(test_splay, test4) {
	tree_t* tree = NULL;
	//tree_t* tree = NULL;
	tree = add_node(tree, 20);
	tree = add_node(tree, 30);
	tree = add_node(tree, 40);
	tree = add_node(tree, 50);
	tree = add_node(tree, 100);
	tree = add_node(tree, 200);
	tree = tree_splay(tree, 50);
	EXPECT_TRUE(tree->left->key,30);
	EXPECT_TRUE(tree->right->key, 100);
	tree_t* left = tree->left;
	EXPECT_TRUE(left->left->key, 20);
	EXPECT_TRUE(left->right->key, 40);
	destroy_tree(tree);
}
TEST(test_remove, test5) {
	tree_t* tree = NULL;
	//tree_t* tree = NULL;
	tree = add_node(tree, 20);
	tree = add_node(tree, 30);
	tree = add_node(tree, 40);
	tree = add_node(tree, 50);
	tree = add_node(tree, 100);
	tree = add_node(tree, 200);
	tree = tree_splay(tree, 50);
	tree = remove_node(tree, 100);
	EXPECT_TRUE(tree->key, 50);
	EXPECT_TRUE(tree->right->key, 200);
	EXPECT_TRUE(tree->left->key, 30);
	tree = remove_node(tree, 40);
	EXPECT_TRUE(tree->key, 30);
	EXPECT_TRUE(tree->right->key, 50);
	EXPECT_TRUE(tree->left->key, 20);
	destroy_tree(tree);
}
TEST(test_destroy, test6) {
	tree_t* tree = NULL;
	//tree_t* tree = NULL;
	tree = add_node(tree, 20);
	tree = add_node(tree, 30);
	tree = add_node(tree, 40);
	tree = add_node(tree, 50);
	tree = add_node(tree, 100);
	tree = add_node(tree, 200);
	destroy_tree(tree);
	EXPECT_TRUE(tree, NULL);
}
