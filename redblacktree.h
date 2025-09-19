#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LEN(a) (sizeof(a) / sizeof((a)[0]))

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

typedef struct {
    Node *root;
} RBTree;


Node* create_node(int data);
void rotateLeft(RBTree *tree, Node *x);
void rotateRight(RBTree *tree, Node *y);
void fixViolation(RBTree *tree, Node *z);
void insert(RBTree *tree, int data);
void inorder(Node *r);
void printTree(Node* root, int indent);


Node* search(Node* root, int value);

#endif

