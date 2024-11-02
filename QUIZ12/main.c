#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_GROUP_NAME_LENGTH 10
#define MAX_CUSTOMERS 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    char groupName[MAX_GROUP_NAME_LENGTH];
    int priorityLevel;
} Customer;

typedef struct {
    Customer* customers[MAX_CUSTOMERS];
    int size;
} PriorityQueue;

void initializeQueue(PriorityQueue* queue);
void insertCustomer(PriorityQueue* queue, Customer* customer);
void removeCustomer(PriorityQueue* queue, const char* customerName);
void displayCustomers(const PriorityQueue* queue);
void readCustomersFromFile(PriorityQueue* queue);
void writeCustomersToFile(const PriorityQueue* queue);
void searchCustomer(const PriorityQueue* queue, const char* customerName, int index);
void changePriority(PriorityQueue* queue, const char* customerName, int newPriorityLevel);

int main() {
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    PriorityQueue queue;
    initializeQueue(&queue);
    readCustomersFromFile(&queue);
    char option;
    char customerName[MAX_NAME_LENGTH];
    char newGroupName[MAX_GROUP_NAME_LENGTH];
    int newPriorityLevel;
    do {
        printf("\n=========== Welcome to the ABC Bank ===========\n\n");
        printf("1-Insert New Customer\n");
        printf("2-Remove Customer\n");
        printf("3-Display customers in order\n");
        printf("4-Search a customer\n");
        printf("5-Change priority settings\n");
        printf("6-Exit\n");
        printf("Please select an option: ");
        scanf(" %c", &option);
        printf("...\n");
        switch (option) {
        case '1':
            printf("Please enter customer's Name: ");
            scanf(" %[^\n]s", newCustomer->name);
            printf("Please enter customer's Age: ");
            scanf(" %d", &newCustomer->age);
            printf("Please enter customer's Priority Group: ");
            scanf(" %s", newGroupName);
            strcpy(newCustomer->groupName, newGroupName);
            if (strcmp(newGroupName, "NORMAL") == 0){
                newCustomer->priorityLevel = 1;
            } else if (strcmp(newGroupName, "VETERAN") == 0) {
                newCustomer->priorityLevel = 2;
            } else if (strcmp(newGroupName, "OD") == 0) {
                newCustomer->priorityLevel = 3;
            } else if (strcmp(newGroupName, "VIP") == 0) {
                newCustomer->priorityLevel = 4;
            } else {
                printf("Invalid priority group!\n");
                free(newCustomer);
                break;
            }
            insertCustomer(&queue, newCustomer);
            printf("Customer added successfully...\n");
            break;
        case '2':
            printf("Please enter customer's name to remove: ");
            scanf(" %[^\n]s", customerName);
            removeCustomer(&queue, customerName);
            printf("Customer removed successfully...\n");
            break;
        case '3':
            displayCustomers(&queue);
            break;
        case '4':
            printf("Please enter customer's name to search: ");
            scanf(" %[^\n]s", customerName);
            searchCustomer(&queue, customerName, 0);
            break;
        case '5':
            printf("Please enter customer's name: ");
            scanf(" %[^\n]s", customerName);
            printf("Please enter new priority level: ");
            scanf("%d", &newPriorityLevel);
            changePriority(&queue, customerName, newPriorityLevel);
            printf("Priority level changed successfully...\n");
            searchCustomer(&queue, customerName, 0);
            break;
        case '6':
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option! Please choose correctly.\n");
            break;
        }
    } while(option != '6');

    for (int i = 0; i < queue.size; i++) {
        if (queue.customers[i] != NULL) {
            free(queue.customers[i]);
        }
    }
    return 0;
}

void initializeQueue(PriorityQueue* queue) {
    queue->size = 0;
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        queue->customers[i] = NULL;
    }
}
void insertCustomer(PriorityQueue* queue, Customer* customer) {
    if (queue->size >= MAX_CUSTOMERS) {
        printf("Queue is full.\n");
        return;
    }
    int i = queue->size - 1;
    while (i >= 0 && customer->priorityLevel > queue->customers[i]->priorityLevel) {
        queue->customers[i + 1] = queue->customers[i];
        i--;
    }
    queue->customers[i + 1] = customer;
    queue->size++;
    writeCustomersToFile(queue);
}
void removeCustomer(PriorityQueue* queue, const char* customerName) {
    int i = 0;
    while (i < queue->size && strcmp(queue->customers[i]->name, customerName) != 0) {
        i++;
    }
    if (i == queue->size) {
        printf("Customer not found in the queue.\n");
        return;
    }
    free(queue->customers[i]);
    queue->customers[i] = NULL;
    for (int j = i; j < queue->size; j++) {
        queue->customers[j] = queue->customers[j + 1];
    }
    queue->size--;
    writeCustomersToFile(queue);
}
void displayCustomers(const PriorityQueue* queue) {
    printf("Customers:\n");
    for (int i = 0; i < queue->size; i++) {
        Customer* customer = queue->customers[i];
        printf("%d. ", i+1);
        printf("Name: %s, Age: %d, Group: %s, Priority: %d\n", customer->name, customer->age, customer->groupName, customer->priorityLevel);
    }
}
void readCustomersFromFile(PriorityQueue* queue) {
    FILE* fp = fopen("customers.txt", "r");
    if (fp == NULL) {
        printf("Error! Unable to open file");
        return;
    }
    char line[50];
    while (fgets(line, sizeof(line), fp)) {
        char name[MAX_NAME_LENGTH];
        int age;
        char groupName[MAX_GROUP_NAME_LENGTH];
        int priorityLevel;
        sscanf(line, "%[^-]-%d-%[^-]-%d", name, &age, groupName, &priorityLevel);
        Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
        strcpy(newCustomer->name, name);
        newCustomer->age = age;
        strcpy(newCustomer->groupName, groupName);
        newCustomer->priorityLevel = priorityLevel;
        insertCustomer(queue, newCustomer);
    }
    fclose(fp);
}
void writeCustomersToFile(const PriorityQueue* queue) {
    FILE* file = fopen("customers.txt", "w");
    if (file == NULL) {
        printf("Error! Unable to open file");
        return;
    }
    for (int i = 0; i < queue->size; i++) {
        Customer* customer = queue->customers[i];
        fprintf(file, "%s-%d-%s-%d\n", customer->name, customer->age, customer->groupName, customer->priorityLevel);
    }
    fclose(file);
}
void searchCustomer(const PriorityQueue* queue, const char* customerName, int index) {
    if (index >= queue->size) {
        printf("Customer not found.\n");
        return;
    }
    Customer* customer = queue->customers[index];
    if (strcmp(customer->name, customerName) == 0) {
        printf("Customer found:\n");
        printf("Name: %s, Age: %d, Group: %s, Priority: %d\n", customer->name, customer->age, customer->groupName, customer->priorityLevel);
        return;
    }
    searchCustomer(queue, customerName, index + 1);
}
void changePriority(PriorityQueue* queue, const char* customerName, int newPriorityLevel) {
    for (int i = 0; i < queue->size; i++) {
        Customer* customer = queue->customers[i];
        if (strcmp(customer->name, customerName) == 0) {
            customer->priorityLevel = newPriorityLevel;
            printf("Priority level changed for customer: %s\n", customer->name);
            writeCustomersToFile(queue);
            return;
        }
    }
    printf("Customer not found.\n");
}
