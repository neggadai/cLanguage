#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

typedef struct {
    Node *root;
} RBTree;

Node* create_node(int data) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) {
    fprintf(stderr,"Error: cannot allocate memory\n");
    exit(1);
    }
    n->data = data;
    n->color = RED; 
    n->left = n->right = n->parent = NULL;
    return n;
}

void rotateLeft(RBTree *tree, Node *x) {
    Node *y = x->right;
    if (y == NULL) return;
    x->right = y->left;
    if (y->left) y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rotateRight(RBTree *tree, Node *y) {
    Node *x = y->left;
    if (x == NULL) return;
    y->left = x->right;
    if (x->right) x->right->parent = y;

    x->parent = y->parent; 
    if (y->parent == NULL)
        tree->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void fixViolation(RBTree *tree, Node *z) {
    while (z != tree->root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent; 
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(tree, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent; 
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(tree, z->parent->parent); 
            }
        }
    }
    if (tree->root) tree->root->color = BLACK; 
}

void insert(RBTree *tree, int data) {
    Node *z = create_node(data);
    Node *y = NULL;
    Node *x = tree->root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        tree->root = z;
    else if (z->data < y->data)
        y->left = z; 
    else
        y->right = z;  

    fixViolation(tree, z);
}

void inorder(Node *r) {
    if (!r) return;
    inorder(r->left);
    printf("%d(%c) ", r->data, r->color == RED ? 'R' : 'B');
    inorder(r->right);
}


void printTree(Node* root, int indent) {
    if (root == NULL) return;

    for (int i = 0; i < indent; i++) printf("    ");
    printf("%d(%c)\n", root->data, root->color == RED ? 'R' : 'B');


    if (root->left) {
        for (int i = 0; i < indent; i++) printf("    ");
        printf("/ \n");
        printTree(root->left, indent + 1);
    }
    if (root->right) {
        for (int i = 0; i < indent; i++) printf("    ");
        printf("\\ \n");
        printTree(root->right, indent + 1);
    }
}

int main() { 
    RBTree tree; tree.root = NULL;
    int vals[] = {20, 15, 25, 10, 5, 1, 30, 22, 27};
    for (size_t i = 0; i < sizeof(vals)/sizeof(vals[0]); ++i)
        insert(&tree, vals[i]);

    printf("Inorder (value(color)):\n");
    inorder(tree.root);
    printf("\n");
    printTree(tree.root, 0);
    return 0;
}

