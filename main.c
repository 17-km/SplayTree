#include <stdio.h>
#include <stdlib.h>
#include "SplayTree.h"

int main()
{
    struct Node *root = NULL;
    root = insertNode(root, 50);
    root = insertNode(root, 30);
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    root = insertNode(root, 70);
    root = insertNode(root, 60);
    root = insertNode(root, 80);
    root = insertNode(root, 55);

    displayTree(root, 0);
    root = insertNode(root, 90);
    displayTree(root, 0);
    root = deleteNode(root, 50);
    displayTree(root, 0);
    root = insertNode(root, 22);
    displayTree(root, 0);
    root = insertNode(root, 54);
    displayTree(root, 0);
    root = insertNode(root, 90);
    displayTree(root, 0);
    root = searchNode(root, 20);
    displayTree(root, 0);
    displayInOrder(root);

    root = askUserForChoice(root);

    return 0;
}
