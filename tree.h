#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#pragma warning(disable:4996)

typedef struct tree
{
	int key;
	int leaves_number;
	struct tree* left, * right;
} bin_tree;

void free_node(bin_tree* root);
int left_of(const int value, const bin_tree* root);
int right_of(const int value, const bin_tree* root);
bin_tree* insert_node(bin_tree* root, const int value);
bool search_node(const bin_tree* root, int value);
int left_most_value(const bin_tree* root);
bin_tree* remove_node(bin_tree* root, int value);