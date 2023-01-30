#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <stdio.h>
#include <stdlib.h>

// struktura wezla
// key to przechowywana wartosc
// left i right to wskazniki na dzieci, odpowiednio o wartosci mniejszej i wiekszej
struct Node
{
    int key;
    struct Node *left, *right;
};

struct Node* newNode(int key);
struct Node* rightRotate(struct Node* root);
struct Node* leftRotate(struct Node* root);
struct Node* splay(struct Node* root, int key);
struct Node* insertNode(struct Node* root, int key);
struct Node* deleteNode(struct Node* root, int key);
void displayTree(struct Node *root, int level);
struct Node *deleteTree(struct Node *root);
struct Node *searchNode(struct Node *root, int key);
void displayInOrder(struct Node *root);
int getNumber();
struct Node *askUserForChoice(struct Node *root);

#endif // SPLAYTREE_H
