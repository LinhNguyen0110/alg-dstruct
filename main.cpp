#include "tree.h"
int main()
{
	bin_tree* tree = NULL;
	char op[1000], last;
	int value[1000];
	int n, i = 0;
	while (scanf("%c", &op[i])) {
		if ((op[i] != 'a') && (op[i] != 'r') && (op[i] != 'f')) {
			break;
		}
		scanf("%d%c", &value[i], &last);
		i += 1;
	}
	for (int j = 0; j < i; j++) {
		switch (op[j])
		{
		case'a':
			tree = insert_node(tree, value[j]);
			break;
		case 'r':
			tree = remove_node(tree, value[j]);
			break;
		case 'f':
			n = search_node(tree, value[j]);
			if (n == 1) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
			break;
		}
	}
	free_node(tree);
	return 0;
}