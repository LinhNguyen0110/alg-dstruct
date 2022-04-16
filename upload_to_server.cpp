#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)
typedef struct node {
    struct node* first;
    struct node* second;
    struct node* third;
    struct node* fourth;
    struct node* parent;
    int size;
    int key[3];
} node;

node* create_node(int value) {
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        printf("No memory allocated!");
        return 0;
    }
    if (new_node) {
        new_node->first = NULL;
        new_node->second = NULL;
        new_node->third = NULL;
        new_node->fourth = NULL;

        new_node->parent = NULL;

        new_node->size = 1;
        new_node->key[0] = value;

        return new_node;
    }
    return NULL;
}

node* create_node_2(int value, node* node_one, node* node_two, node* node_three, node* node_four, node* node_parent) {
    node* new_node_2 = (node*)malloc(sizeof(node));
    if (new_node_2 == NULL) {
        printf("No memory allocated!");
        return 0;
    }
    if (new_node_2) {
        new_node_2->first = node_one;
        new_node_2->second = node_two;
        new_node_2->third = node_three;
        new_node_2->fourth = node_four;
        new_node_2->parent = node_parent;
        new_node_2->size = 1;
        new_node_2->key[0] = value;
        return new_node_2;
    }
    return NULL;
}

bool find(int value, int* key, int size) {
    for (int i = 0; i < size; ++i) {
        if (key[i] == value) {
            return true;
        }
    }
    return false;
}

void swap(int* x, int* y) {
    int r = (*x);
    (*x) = (*y);
    (*y) = r;
}

void sort(int* x, int* y) {
    if (*x > *y) {
        swap(x, y);
    }
}

void sort_plus(int* x, int* y, int* z) {
    if (*x > *y) {
        swap(x, y);
    }
    if (*x > *z) {
        swap(x, z);
    }
    if (*y > *z) {
        swap(y, z);
    }
}

void sort_keys(int size, int* key) {
    if (size == 1) {
        return;
    }
    if (size == 2) {
        sort(&key[0], &key[1]);
    }
    if (size == 3) {
        sort_plus(&key[0], &key[1], &key[2]);
    }
}

void add_key(int value, node* tree_node) {
    if (tree_node == NULL) {
        return;
    }
    tree_node->key[tree_node->size] = value;
    tree_node->size++;
    sort_keys(tree_node->size, tree_node->key);
}

void remove_key(int value, node* tree_node) {
    if (tree_node == NULL) {
        return;
    }
    if (tree_node->size >= 1 && tree_node->key[0] == value) {
        tree_node->key[0] = tree_node->key[1];
        tree_node->key[1] = tree_node->key[2];
        tree_node->size--;
    }
    else if (tree_node->size == 2 && tree_node->key[1] == value) {
        tree_node->key[1] = tree_node->key[2];
        tree_node->size--;
    }
}

void become_node_2(int value, int* key, node* tree_node, node* node_one, node* node_two) {
    tree_node->first = node_one;
    tree_node->second = node_two;
    tree_node->third = NULL;
    tree_node->fourth = NULL;
    tree_node->parent = NULL;
    tree_node->size = 1;
    key[0] = value;
}

bool is_leaf(node* tree) {
    if (tree == NULL) {
        return false;
    }
    if ((tree->first == NULL) && (tree->second == NULL) && (tree->third == NULL)) {
        return true;
    }
    return false;
}

node* split_tree(node* item) {
    if (item == NULL) {
        return NULL;
    }
    if (item->size < 3) {
        return item;
    }
    node* x = create_node_2(item->key[0], item->first, item->second, NULL, NULL, item->parent);
    node* y = create_node_2(item->key[2], item->third, item->fourth, NULL, NULL, item->parent);
    if (x->first) {
        x->first->parent = x;
    }
    if (x->second) {
        x->second->parent = x;
    }
    if (y->first) {
        y->first->parent = y;
    }
    if (y->second) {
        y->second->parent = y;
    }
    if (item->parent != NULL) {
        add_key(item->key[1], item->parent);

        if (item->parent->first == item) {
            item->parent->first = NULL;
        }
        else if (item->parent->second == item) {
            item->parent->second = NULL;
        }
        else if (item->parent->third == item) {
            item->parent->third = NULL;
        }

        if (item->parent->first == NULL) {
            item->parent->fourth = item->parent->third;
            item->parent->third = item->parent->second;
            item->parent->second = y;
            item->parent->first = x;
        }
        else if (item->parent->second == NULL) {
            item->parent->fourth = item->parent->third;
            item->parent->third = y;
            item->parent->second = x;
        }
        else {
            item->parent->fourth = y;
            item->parent->third = x;
        }
        node* tmp = item->parent;
        free(item);
        return tmp;
    }
    else {
        x->parent = item;
        y->parent = item;
        become_node_2(item->key[1], item->key, item, x, y);
        return item;
    }
}

node* search(node* tree, int value) {
    if (tree == NULL) {
        return NULL;
    }
    if (find(value, tree->key, tree->size)) {
        return tree;
    }
    else if (value < tree->key[0]) {
        return search(tree->first, value);
    }
    else if ((tree->size == 2) && (value < tree->key[1]) || (tree->size == 1)) {
        return search(tree->second, value);
    }
    else if (tree->size == 2) {
        return search(tree->third, value);
    }
}

node* add_node(node* tree, int value) {
    if (tree == NULL) {
        return create_node(value);
    }
    if (search(tree, value)) {
        return split_tree(tree);
    }
    if (is_leaf(tree)) {
        add_key(value, tree);
    }
    else if (value <= tree->key[0]) {
        add_node(tree->first, value);
    }
    else if ((tree->size == 1) || ((tree->size == 2) && value <= tree->key[1])) {
        add_node(tree->second, value);
    }
    else {
        add_node(tree->third, value);
    }
    return split_tree(tree);
}

node* find_min(node* tree) {
    if (tree == NULL) {
        return tree;
    }
    if ((tree->first) == NULL) {
        return tree;
    }
    else {
        return find_min(tree->first);
    }
}

node* redistribute(node* is_leaf) {
    if (is_leaf == NULL) {
        return NULL;
    }
    node* parent = is_leaf->parent;
    node* first = parent->first;
    node* second = parent->second;
    node* third = parent->third;
    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
        if (first == is_leaf) {
            parent->first = parent->second;
            parent->second = parent->third;
            parent->third = NULL;
            add_key(parent->key[0], parent->first);
            parent->first->third = parent->first->second;
            parent->first->second = parent->first->first;
            if (is_leaf->first != NULL) {
                parent->first->first = is_leaf->first;
            }
            else if (is_leaf->second != NULL) {
                parent->first->first = is_leaf->second;
            }
            if (parent->first->first != NULL) {
                parent->first->first->parent = parent->first;
            }
            remove_key(parent->key[0], parent);
        }
        else if (second == is_leaf) {
            add_key(parent->key[0], first);
            remove_key(parent->key[0], parent);
            if (is_leaf->first != NULL) {
                first->third = is_leaf->first;
            }
            else if (is_leaf->second != NULL) {
                first->third = is_leaf->second;
            }
            if (first->third != NULL) {
                first->third->parent = first;
            }
            parent->second = parent->third;
            parent->third = NULL;
            free(second);
        }
        else if (third == is_leaf) {
            add_key(parent->key[1], second);
            parent->third = NULL;
            remove_key(parent->key[1], parent);
            if (is_leaf->first != NULL) {
                second->third = is_leaf->first;
            }
            else if (is_leaf->second != NULL) {
                second->third = is_leaf->second;
            }
            if (second->third != NULL) {
                second->third->parent = second;
            }
            free(third);
        }
    }
    else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
        if (third == is_leaf) {
            if (is_leaf->first != NULL) {
                is_leaf->second = is_leaf->first;
                is_leaf->first = NULL;
            }
            add_key(parent->key[1], is_leaf);
            if (second->size == 2) {
                parent->key[1] = second->key[1];
                remove_key(second->key[1], second);
                is_leaf->first = second->third;
                second->third = NULL;
                if (is_leaf->first != NULL) {
                    is_leaf->first->parent = is_leaf;
                }
            }
            else if (first->size == 2) {
                parent->key[1] = second->key[0];
                is_leaf->first = second->second;
                second->second = second->first;
                if (is_leaf->first != NULL) {
                    is_leaf->first->parent = is_leaf;
                }
                second->key[0] = parent->key[0];
                parent->key[0] = first->key[1];
                remove_key(first->key[1], first);
                second->first = first->third;
                if (second->first != NULL) {
                    second->first->parent = second;
                }
                first->third = NULL;
            }
        }
        else if (second == is_leaf) {
            if (third->size == 2) {
                if (is_leaf->first == NULL) {
                    is_leaf->first = is_leaf->second;
                    is_leaf->second = NULL;
                }
                add_key(parent->key[1], second);
                parent->key[1] = third->key[0];
                remove_key(third->key[0], third);
                second->second = third->first;
                if (second->second != NULL) {
                    second->second->parent = second;
                }
                third->first = third->second;
                third->second = third->third;
                third->third = NULL;
            }
            else if (first->size == 2) {
                if (is_leaf->second == NULL) {
                    is_leaf->second = is_leaf->first;
                    is_leaf->first = NULL;
                }
                add_key(parent->key[0], second);
                parent->key[0] = first->key[1];
                remove_key(first->key[1], first);
                second->first = first->third;
                if (second->first != NULL) {
                    second->first->parent = second;
                }
                first->third = NULL;
            }
        }
        else if (first == is_leaf) {
            if (is_leaf->first == NULL) {
                is_leaf->first = is_leaf->second;
                is_leaf->second = NULL;
            }
            add_key(parent->key[0], first);
            if (second->size == 2) {
                parent->key[0] = second->key[0];
                remove_key(second->key[0], second);
                first->second = second->first;
                if (first->second != NULL) {
                    first->second->parent = first;
                }
                second->first = second->second;
                second->second = second->third;
                second->third = NULL;
            }
            else if (third->size == 2) {
                parent->key[0] = second->key[0];
                second->key[0] = parent->key[1];
                parent->key[1] = third->key[0];
                remove_key(third->key[0], third);
                first->second = second->first;
                if (first->second != NULL) {
                    first->second->parent = first;
                }
                second->first = second->second;
                second->second = third->first;
                if (second->second != NULL) {
                    second->second->parent = second;
                }
                third->first = third->second;
                third->second = third->third;
                third->third = NULL;
            }
        }
    }
    else if (parent->size == 1) {
        add_key(parent->key[0], is_leaf);
        if (first == is_leaf && second->size == 2) {
            parent->key[0] = second->key[0];
            remove_key(second->key[0], second);
            if (is_leaf->first == NULL) {
                is_leaf->first = is_leaf->second;
            }
            is_leaf->second = second->first;
            second->first = second->second;
            second->second = second->third;
            second->third = NULL;
            if (is_leaf->second != NULL) {
                is_leaf->second->parent = is_leaf;
            }
        }
        else if (second == is_leaf && first->size == 2) {
            parent->key[0] = first->key[1];
            remove_key(first->key[1], first);
            if (is_leaf->second == NULL) {
                is_leaf->second = is_leaf->first;
            }
            is_leaf->first = first->third;
            first->third = NULL;
            if (is_leaf->first != NULL) {
                is_leaf->first->parent = is_leaf;
            }
        }
    }
    return parent;
}

node* merge(node* is_leaf) {
    if (is_leaf == NULL) {
        return NULL;
    }
    node* parent = is_leaf->parent;
    if (parent->first == is_leaf) {
        add_key(parent->key[0], parent->second);
        parent->second->third = parent->second->second;
        parent->second->second = parent->second->first;
        if (is_leaf->first != NULL) {
            parent->second->first = is_leaf->first;
        }
        else if (is_leaf->second != NULL) {
            parent->second->first = is_leaf->second;
        }
        if (parent->second->first != NULL) {
            parent->second->first->parent = parent->second;
        }
        remove_key(parent->key[0], parent);
        free(parent->first);
        parent->first = NULL;
    }
    else if (parent->second == is_leaf) {
        add_key(parent->key[0], parent->first);
        if (is_leaf->first != NULL) {
            parent->first->third = is_leaf->first;
        }
        else if (is_leaf->second != NULL) {
            parent->first->third = is_leaf->second;
        }
        if (parent->first->third != NULL) {
            parent->first->third->parent = parent->first;
        }
        remove_key(parent->key[0], parent);
        free(parent->second);
        parent->second = NULL;
    }
    if (parent->parent == NULL) {
        node* tmp = NULL;
        if (parent->first != NULL) {
            tmp = parent->first;
        }
        else {
            tmp = parent->second;
        }
        tmp->parent = NULL;
        free(parent);
        return tmp;
    }
    return parent;
}

node* fix(node* is_leaf) {
    if (is_leaf == NULL) {
        return NULL;
    }
    if (is_leaf->size == 0 && is_leaf->parent == NULL) {
        free(is_leaf);
        return NULL;
    }
    if (is_leaf->size != 0) {
        if (is_leaf->parent) {
            return fix(is_leaf->parent);
        }
        else {
            return is_leaf;
        }
    }
    node* parent = is_leaf->parent;
    if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2) {
        is_leaf = redistribute(is_leaf);
    }
    else if (parent->size == 2 && parent->third->size == 2) {
        is_leaf = redistribute(is_leaf);
    }
    else {
        is_leaf = merge(is_leaf);
    }
    return fix(is_leaf);
}

node* remove_node(node* tree, int value) {
    if (tree == NULL) {
        return NULL;
    }
    node* item = search(tree, value);
    if (item == NULL) {
        return tree;
    }
    node* min = NULL;
    if (item->key[0] == value) {
        min = find_min(item->second);
    }
    else {
        min = find_min(item->third);
    }
    if (min != NULL) {
        int* z = (value == item->key[0] ? &(item->key[0]) : &(item->key[1]));
        swap(z, &min->key[0]);
        item = min;
    }
    remove_key(value, item);
    return fix(item);
}

void print(node* tree) {
    if (tree == NULL) {
        return;
    }
    print(tree->first);
    for (int i = 0; i < tree->size; i++) {
        printf("%d ", tree->key[i]);
    }
    print(tree->second);
    print(tree->third);
}

void destroy(node* tree) {
    if (tree == NULL) {
        return;
    }
    destroy(tree->first);
    destroy(tree->second);
    destroy(tree->third);
    free(tree);
}

int main(void) {
    char letter;
    int key = 0;
    node* tree = NULL;
    while (scanf("%c", &letter) >= 1) {
        if (letter != 'p' && letter != 'q') {
            scanf("%i", &key);
        }
        switch (letter) {
        case 'a':
            tree = add_node(tree, key);
            break;
        case 'r':
            tree = remove_node(tree, key);
            break;
        case 'f':
            if (search(tree, key)) {
                printf("yes\n");
            }
            else {
                printf("no\n");
            }
            break;
        case 'p':
            print(tree);
            printf("\n");
            break;
        case 'q':
            destroy(tree);
            return 0;
        }
    }
}
