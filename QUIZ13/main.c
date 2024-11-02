#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* leftNode;
    struct Node* rightNode;
};

struct BST {
    struct Node* root;
};

void freeNodes(struct Node* node);

struct Node* createNode(int value);
void insertNode(struct Node* curr, int value);
void addNode(struct BST* bst, int value);

struct Node* findMinValueNode(struct Node* node);
struct Node* removeNode(struct Node* node, int value, struct BST* bst);

struct Node* searchNode(struct Node* node, int value);

int countNodes(struct Node* node);
int getMaxDepth(struct Node* node);
int countLeafNodes(struct Node* node);

void printTree(struct BST* bst);
void printInOrder(struct Node* node);
void printPreOrder(struct Node* node);
void printPostOrder(struct Node* node);
void printLevelOrder(struct Node* node);
void printTheTree(struct Node* node, int level);

int main() {
    struct BST bst;
    bst.root = NULL;
    FILE* file = fopen("input.txt", "r");
    int temp;
    if (file != NULL) {
        while (fscanf(file, "%d", &temp) == 1) {
            addNode(&bst, temp);
        }
        fclose(file);
    }

    char choice;
    int value;
    struct Node* foundNode;
    do {
        printf("----------------------------\n");
        printf("1. Add a node\n");
        printf("2. Remove a node\n");
        printf("3. Search for a node\n");
        printf("4. Count nodes\n");
        printf("5. Get max depth\n");
        printf("6. Count leaf nodes\n");
        printf("7. Print tree\n");
        printf("8. Exit\n");
        printf("----------------------------\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        switch (choice) {
            case '1':
                printf("Enter the value to add: ");
                scanf("%d", &value);
                addNode(&bst, value);
                printf("Node with value %d added to the BST.\n", value);
                break;
            case '2':
                printf("Enter the value to remove: ");
                scanf("%d", &value);
                bst.root = removeNode(bst.root, value, &bst);
                printf("Node with value %d removed from the BST.\n", value);
                break;
            case '3':
                printf("Enter the value to search: ");
                scanf("%d", &value);
                foundNode = searchNode(bst.root, value);
                if (foundNode != NULL) {
                    printf("Node with value %d found in the BST.\n", value);
                } else {
                    printf("Node with value %d not found in the BST.\n", value);
                }
                break;
            case '4':
                printf("Total number of nodes in the BST: %d\n", countNodes(bst.root));
                break;
            case '5':
                printf("Maximum depth of the BST: %d\n", getMaxDepth(bst.root));
                break;
            case '6':
                printf("Number of leaf nodes in the BST: %d\n", countLeafNodes(bst.root));
                break;
            case '7':
                printTree(&bst);
                break;
            case '8':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != '8');

    freeNodes(bst.root);
    
    return 0;
}

void freeNodes(struct Node* node) {
    if (node != NULL) {
        freeNodes(node->leftNode);
        freeNodes(node->rightNode);
        free(node);
    }
}

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->leftNode = NULL;
    newNode->rightNode = NULL;
    return newNode;
}
void insertNode(struct Node* curr, int value) {
    if (value < curr->value) {
        if (curr->leftNode == NULL) {
            curr->leftNode = createNode(value);
        } else {
            insertNode(curr->leftNode, value);
        }
    } else if (value > curr->value) {
        if (curr->rightNode == NULL) {
            curr->rightNode = createNode(value);
        } else {
            insertNode(curr->rightNode, value);
        }
    }
}
void addNode(struct BST* bst, int value) {
    if (bst->root == NULL) {
        bst->root = createNode(value);
    } else {
        insertNode(bst->root, value);
    }
}

struct Node* findMinValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->leftNode != NULL) {
        current = current->leftNode;
    }
    return current;
}
struct Node* removeNode(struct Node* node, int value, struct BST* bst) {
    if (node == NULL) {
        return node;
    }
    if (value < node->value) {
        node->leftNode = removeNode(node->leftNode, value, bst);
    } else if (value > node->value) {
        node->rightNode = removeNode(node->rightNode, value, bst);
    } else {
        if (node->leftNode == NULL) {
            struct Node* temp = node->rightNode;
            free(node);
            return temp;
        } else if (node->rightNode == NULL) {
            struct Node* temp = node->leftNode;
            free(node);
            return temp;
        }
        struct Node* minValueNode = findMinValueNode(node->rightNode);
        node->value = minValueNode->value;
        node->rightNode = removeNode(node->rightNode, minValueNode->value, bst);
    }
    return node;
}

struct Node* searchNode(struct Node* node, int value) {
    if (node == NULL || node->value == value) {
        return node;
    }
    if (value < node->value) {
        return searchNode(node->leftNode, value);
    } else {
        return searchNode(node->rightNode, value);
    }
}

int countNodes(struct Node* node) {
    if (node == NULL) {
        return 0;
    }

    return 1 + countNodes(node->leftNode) + countNodes(node->rightNode);
}
int getMaxDepth(struct Node* node) {
    if (node == NULL) {
        return 0;
    }

    int leftDepth = getMaxDepth(node->leftNode);
    int rightDepth = getMaxDepth(node->rightNode);

    return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
}
int countLeafNodes(struct Node* node) {
    if (node == NULL) {
        return 0;
    }

    if (node->leftNode == NULL && node->rightNode == NULL) {
        return 1;
    }

    return countLeafNodes(node->leftNode) + countLeafNodes(node->rightNode);
}

void printTree(struct BST* bst) {
    if (bst->root == NULL) {
        printf("Binary Search Tree is empty.\n");
        return;
    }
    printf("------------------\n");
    printf("1. Print In-Order\n");
    printf("2. Print Pre-Order\n");
    printf("3. Print Post-Order\n");
    printf("4. Print Level-Order\n");
    printf("5. Print The-Tree\n");
    printf("------------------\n");
    printf("Enter your choice: ");
    char choice;
    scanf(" %c", &choice);
    switch (choice) {
        case '1':
            printInOrder(bst->root);
            break;
        case '2':
            printPreOrder(bst->root);
            break;
        case '3':
            printPostOrder(bst->root);
            break;
        case '4':
            printLevelOrder(bst->root);
            break;
        case '5':
            printf("Tree:\n");
            printTheTree(bst->root, 0);
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }
    printf("\n");
}
void printInOrder(struct Node* node) {
    if (node != NULL) {
        printInOrder(node->leftNode);
        printf("%d ", node->value);
        printInOrder(node->rightNode);
    }
}
void printPreOrder(struct Node* node) {
    if (node != NULL) {
        printf("%d ", node->value);
        printPreOrder(node->leftNode);
        printPreOrder(node->rightNode);
    }
}
void printPostOrder(struct Node* node) {
    if (node != NULL) {
        printPostOrder(node->leftNode);
        printPostOrder(node->rightNode);
        printf("%d ", node->value);
    }
}
void printLevelOrder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = node;
    while (front < rear) {
        struct Node* current = queue[front++];
        printf("%d ", current->value);
        if (current->leftNode != NULL) {
            queue[rear++] = current->leftNode;
        }
        if (current->rightNode != NULL) {
            queue[rear++] = current->rightNode;
        }
    }
}
void printTheTree(struct Node* node, int level) {
    if (node != NULL) {
        printTheTree(node->rightNode, level + 1);
        for (int i = 0; i < level; i++) {
            printf("    ");
        }
        printf("%d\n", node->value);
        printTheTree(node->leftNode, level + 1);
    }
}