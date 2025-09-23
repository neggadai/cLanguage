#include <assert.h>
#include <stdio.h>
#include "redblacktree.h"


void inorderFill(Node *root, int *arr, int *idx) {
    if (!root) return;
    inorderFill(root->left, arr, idx);
    arr[(*idx)++] = root->data;
    inorderFill(root->right, arr, idx);
}

int main() {
    RBTree tree;
    tree.root = NULL;

    int values[] = {20, 15, 25, 10, 5, 1, 30, 22, 27};
    int n = ARRAY_LEN(values);

    for(int i=0;i<n;i++)
        insert(&tree, values[i]);


    assert(tree.root != NULL);


    for(int i=0;i<n;i++)
        assert(search(tree.root, values[i]) != NULL);

    assert(search(tree.root, 99) == NULL);


    int arr[20], idx=0;
    inorderFill(tree.root, arr, &idx);
    for(int i=1;i<idx;i++)
        assert(arr[i-1]<arr[i]);

    printf("All tests passed!\n");
    return 0;
}

