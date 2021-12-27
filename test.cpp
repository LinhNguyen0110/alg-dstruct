#include "pch.h"
#include "../4_Linh_Nguyen_E2/tree.cpp"
TEST(Test_NULL_Search, null_test) {
	bin_tree* root = NULL;
  EXPECT_EQ(search_node(root,1), false);
}

TEST(Test_Insert_Search_Free, 2_test) {
	bin_tree* root = NULL;
	root = insert_node(root, 1);
	EXPECT_EQ(search_node(root, 1), true);
}

TEST(Test_Order, 3_test) {
	bin_tree* root = NULL;
	root = insert_node(root, 1);
	root = insert_node(root, 2);
	root = insert_node(root, 3);
	root = insert_node(root, 0);
	bin_tree* right = root->right;
	EXPECT_EQ(left_of(0,root), 1);
	EXPECT_EQ(right_of(2, root), 1);
	EXPECT_EQ(right_of(3, root), 1);
	EXPECT_EQ(right_of(3, right), 1);
}
TEST(Test_left_most_value, 4_test) {
	bin_tree* root = NULL;
	root = insert_node(root, 50);
	root = insert_node(root, 40);
	root = insert_node(root, 30);
	root = insert_node(root, 70);
	root = insert_node(root, 65);
	root = insert_node(root, 60);
	root = insert_node(root, 55);
	root = insert_node(root, 78);
	EXPECT_EQ(left_most_value(root->right), 55);
}
TEST(Test_remove_node, 5_test) {
	bin_tree* root = NULL;
	root = insert_node(root, 50);
	root = insert_node(root, 40);
	root = insert_node(root, 30);
	root = insert_node(root, 70);
	root = insert_node(root, 65);
	root = insert_node(root, 60);
	root = insert_node(root, 55);
	root = insert_node(root, 67);
	remove_node(root, 55);
	EXPECT_EQ(left_most_value(root->right), 60);
	root = insert_node(root, 55);
	root = insert_node(root, 62);
	remove_node(root, 70);
	EXPECT_EQ(root->right->key, 65);
}
TEST(Test_free, 6_test) {
	bin_tree* root = NULL;
	root = insert_node(root, 50);
	root = insert_node(root, 40);
	root = insert_node(root, 30);
	root = insert_node(root, 70);
	root = insert_node(root, 65);
	root = insert_node(root, 60);
	root = insert_node(root, 55);
	root = insert_node(root, 67);
	root = insert_node(root, 62);
	free(root->right);
	EXPECT_EQ(root->right->right, NULL);
}
