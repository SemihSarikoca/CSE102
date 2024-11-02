#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define AssetType_Size 20
#define String_Size 50

typedef struct Node {
    void* data;
    struct Node* next;
} Node;
typedef struct {
    char type[AssetType_Size];
    int ivals[1];
    double svals[1];
} Asset1;
typedef struct {
    char type[AssetType_Size];
    double svals[2];
    int ivals[2];
} Asset2;
typedef struct {
    char type[AssetType_Size];
    char string1[String_Size];
    char string2[String_Size];
} Asset3;
typedef struct {
    char type[AssetType_Size];
    double value1;
    float value2;
    double value3;
} Asset4;

void fillLinkedList(Node** head);
void serializeLinkedList(Node* head);
void deserializeLinkedList(Node** head);
void printLinkedList(Node* head);

int main() {
    Node* head = NULL;
    fillLinkedList(&head);

    printLinkedList(head);

    printf("\nserializing linked list...\n");
    serializeLinkedList(head);

    Node* reconstructedHead = NULL;
    printf("deserializing linked list...\n\n");
    deserializeLinkedList(&reconstructedHead);

    printLinkedList(reconstructedHead);

    // Free the allocated memory
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    current = reconstructedHead;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    return 0;
}

void printLinkedList(Node* head) { // Prints linked list that have different struct type 
    Node* current = head;
    while (current != NULL) {
        void* data = current->data;
        if (strcmp(((Asset1*)data)->type, "Asset1") == 0) {
            Asset1* asset = (Asset1*)data;
            printf("Type: %s, Ivals: %d, Svals: %lf\n", asset->type, asset->ivals[0], asset->svals[0]);
        } else if (strcmp(((Asset2*)data)->type, "Asset2") == 0) {
            Asset2* asset = (Asset2*)data;
            printf("Type: %s, Svals: %lf, %lf, Ivals: %d, %d\n", asset->type, asset->svals[0], asset->svals[1], asset->ivals[0], asset->ivals[1]);
        } else if (strcmp(((Asset3*)data)->type, "Asset3") == 0) {
            Asset3* asset = (Asset3*)data;
            printf("Type: %s, String1: %s, String2: %s\n", asset->type, asset->string1, asset->string2);
        } else if (strcmp(((Asset4*)data)->type, "Asset4") == 0) {
            Asset4* asset = (Asset4*)data;
            printf("Type: %s, Value1: %lf, Value2: %f, Value3: %lf\n", asset->type, asset->value1, asset->value2, asset->value3);
        }
        current = current->next;
    }
}
void fillLinkedList(Node** head) { // Create linked list
    srand(time(NULL));
    int numAssets = rand() % 11 + 10; // Random number of asset between 10 - 20 
    for (int i = 0; i < numAssets; i++) {
        Node* newNode = malloc(sizeof(Node)); // Create node 
        int assetType = rand() % 4;
        // Fills linked list with 4 different struct (asset) type
        switch (assetType) {
            case 0: {
                Asset1* asset = malloc(sizeof(Asset1));
                strcpy(asset->type, "Asset1");
                asset->ivals[0] = rand() % 100;
                asset->svals[0] = (double)rand() / RAND_MAX; // Create random double number between 0-1
                newNode->data = asset;
                newNode->next = NULL;
            }
                break;
            case 1: {
                Asset2* asset = malloc(sizeof(Asset2));
                strcpy(asset->type, "Asset2");
                asset->ivals[0] = rand() % 100;
                asset->svals[0] = (double)rand() / RAND_MAX;
                asset->ivals[1] = rand() % 100;
                asset->svals[1] = (double)rand() / RAND_MAX;
                newNode->data = asset;
                newNode->next = NULL;
            }
                break;
            case 2: {
                Asset3* asset = malloc(sizeof(Asset3));
                strcpy(asset->type, "Asset3");
                sprintf(asset->string1, "[add string1]");
                sprintf(asset->string2, "[add string2]");
                newNode->data = asset;
                newNode->next = NULL;
            }
                break;
            case 3: {
                Asset4* asset = (Asset4*)malloc(sizeof(Asset4));
                strcpy(asset->type, "Asset4");
                asset->value1 = (double)rand() / RAND_MAX;
                asset->value2 = (float)rand() / RAND_MAX; // Create random float number between 0-1
                asset->value3 = (double)rand() / RAND_MAX;
                newNode->data = asset;
                newNode->next = NULL;
            }
                break;
            default:
                printf("Randomizing error!\n");
                return;
        }
        // Adding data to linked list 
        if (*head == NULL) {
            *head = newNode;
        } else {
            Node* current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
}

void serializeLinkedList(Node* head) {
    FILE* file = fopen("linkedlist.bin", "wb"); // Open binary file in write format
    if (file == NULL) { // Print error if file do not open
        printf("Error! Binary file do not opennig.\n");
        return;
    }
    Node* current = head;
    while (current != NULL) {
        void* data = current->data;
        // Write asset to the binary file with the size of specific asset
        if (strcmp(((Asset1*)data)->type, "Asset1") == 0) {
            fwrite(data, sizeof(Asset1), 1, file);
        } else if (strcmp(((Asset2*)data)->type, "Asset2") == 0) {
            fwrite(data, sizeof(Asset2), 1, file);
        } else if (strcmp(((Asset3*)data)->type, "Asset3") == 0) {
            fwrite(data, sizeof(Asset3), 1, file);
        } else if (strcmp(((Asset4*)data)->type, "Asset4") == 0) {
            fwrite(data, sizeof(Asset4), 1, file);
        }
        current = current->next; // Move to next node of the list
    }

    fclose(file);
}
void deserializeLinkedList(Node** head) {
    FILE* file = fopen("linkedlist.bin", "rb"); // Open binary file in read format
    if (file == NULL) { // Print error if file do not open
        printf("Error! Binary file do not opennig.\n");
        return;
    }

    Node* current = NULL;
    char type[AssetType_Size];
    while (fread(type, sizeof(type), 1, file) != 0) { // Read asset type 
        void* data = NULL;
        fseek(file, -sizeof(type), SEEK_CUR); // Move back (size of the type that readed, in this example "20") so its reach the start of the asset
        // Allocate memory to the asset. Make sure size is the size of the readed asset. Then read asset store to the void "data" variable
        if (strcmp(type, "Asset1") == 0) {
            data = malloc(sizeof(Asset1)); 
            fread(data, sizeof(Asset1), 1, file);
        } else if (strcmp(type, "Asset2") == 0) {
            data = malloc(sizeof(Asset2));
            fread(data, sizeof(Asset2), 1, file);
        } else if (strcmp(type, "Asset3") == 0) {
            data = malloc(sizeof(Asset3));
            fread(data, sizeof(Asset3), 1, file);
        } else if (strcmp(type, "Asset4") == 0) {
            data = malloc(sizeof(Asset4));
            fread(data, sizeof(Asset4), 1, file);
        }
        // Memory allocation error control
        if (data == NULL) {
            printf("Error at allocating memory!\n");
            break;
        }
        // Creating new node that points data
        Node* newNode = malloc(sizeof(Node));
        newNode->data = data;
        newNode->next = NULL;
        // Add node to the linked list
        if (*head == NULL) {
            *head = newNode;
            current = *head;
        } else {
            current->next = newNode;
            current = current->next;
        }
    }
    fclose(file);
}
