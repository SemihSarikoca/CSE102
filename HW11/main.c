#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct Node {
    char name[MAX_NAME_LENGTH];
    int age;
    struct Node* mother;
    struct Node* father;
    struct Node* children;
    struct Node* nextSibling;
} Node;

Node* createPerson(char* name, int age) {
    Node* person = (Node*)malloc(sizeof(Node));
    strcpy(person->name, name);
    person->age = age;
    person->mother = NULL;
    person->father = NULL;
    person->children = NULL;
    person->nextSibling = NULL;
    return person;
}

Node* findPerson(Node* root, char* name) {
    if (root == NULL)
        return NULL;

    if (strcmp(root->name, name) == 0)
        return root;

    Node* person = findPerson(root->children, name);
    if (person != NULL)
        return person;

    return findPerson(root->nextSibling, name);
}

void addChild(Node* parent, Node* child) {
    child->nextSibling = parent->children;
    parent->children = child;
}

void removeChild(Node* parent, Node* child) {
    if (parent == NULL || child == NULL)
        return;
    if (parent->children == child) {
        parent->children = child->nextSibling;
    } else {
        Node* current = parent->children;
        while (current != NULL && current->nextSibling != child)
            current = current->nextSibling;
        if (current != NULL)
            current->nextSibling = child->nextSibling;
    }
}

Node* createFamilyTree(char* familyName) {
    FILE* file = fopen(familyName, "w");
    fclose(file);
    printf("Family tree '%s' created successfully.\n", familyName);
    return NULL;
}

void removeFamilyTree(char* familyName) {
    if (remove(familyName) == 0)
        printf("Family tree '%s' removed successfully.\n", familyName);
    else
        printf("Unable to remove family tree '%s'.\n", familyName);
}

void addPerson(struct Node* root) {
    char name[50];
    int age;
    char motherName[50];
    char fatherName[50];

    printf("Enter the person's name: ");
    scanf("%s", name);
    printf("Enter the person's age: ");
    scanf("%d", &age);
    printf("Enter the person's mother's name: ");
    scanf("%s", motherName);
    printf("Enter the person's father's name: ");
    scanf("%s", fatherName);

    Node* person = findPerson(root, name);
    Node* mother = findPerson(root, motherName);
    Node* father = findPerson(root, fatherName);

    if (person != NULL || mother == NULL || father == NULL) {
        printf("Invalid person, mother, or father name.\n");
        return;
    }

    Node* newPerson = createPerson(name, age);
    newPerson->mother = mother;
    newPerson->father = father;

    addChild(mother, newPerson);
    addChild(father, newPerson);

    printf("Person '%s' added successfully.\n", name);
}

void removePerson(Node* root, char* name) {
    Node* person = findPerson(root, name);
    if (person == NULL) {
        printf("Person '%s' not found.\n", name);
        return;
    }
    
    if (person->children != NULL) {
        printf("Warning: Removing this person will also remove their children. Continue? (y/n): ");
        char choice;
        scanf(" %c", &choice);
        if (choice != 'y' && choice != 'Y')
            return;
        Node* child = person->children;
        while (child != NULL) {
            Node* nextChild = child->nextSibling;
            removePerson(root, child->name);
            child = nextChild;
        }
    }

    removeChild(person->mother, person);
    removeChild(person->father, person);

    printf("Person '%s' removed successfully.\n", name);
    free(person);
}


int main() {
    Node* familyTree = NULL;
    int choice;

    while (1) {
        printf("\n------------------------------------\n");
        printf("Family Tree Management System\n");
        printf("------------------------------------\n");
        printf("1. Add a family tree\n");
        printf("2. Remove a family tree\n");
        printf("3. Add a person\n");
        printf("4. Remove a person\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[50];
                printf("Enter the family tree name: ");
                scanf("%s", name);
                char filename[100];
                sprintf(filename, "family%s.txt", name);
                familyTree = createFamilyTree(filename);
                break;
            }
            case 2: {
                char name[50];
                printf("Enter the family tree name: ");
                scanf("%s", name);
                char filename[100];
                sprintf(filename, "family%s.txt", name);
                removeFamilyTree(filename);
                break;
            }
            case 3:
                addPerson(familyTree);
                break;
            case 4: {
                char name[50];
                printf("Enter the person's name: ");
                scanf("%s", name);
                removePerson(familyTree, name);
                break;
            }
            case 5:
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;
}


