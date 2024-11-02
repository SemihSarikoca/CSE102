#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Order {
    int orderID;
    char customerName[100];
    char items[200];
    char orderTime[100];
    struct Order* next;
} Order;

Order* createOrder(char* customerName, int orderID, char* items, char* orderTime) {
    Order* newOrder = (struct Order*)malloc(sizeof(struct Order));
    newOrder->orderID = orderID;
    strcpy(newOrder->customerName, customerName);
    strcpy(newOrder->items, items);
    strcpy(newOrder->orderTime, orderTime);
    newOrder->next = NULL;
    return newOrder;
}
Order* enqueue(Order* queue, char* customerName, int orderID, char* items, char* orderTime) {
    Order* newOrder = createOrder(customerName, orderID, items, orderTime);
    if (queue == NULL) {
        return newOrder;
    }
    Order* temp = queue;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newOrder;
    return queue;
}
Order* dequeue(Order* queue) {
    if (queue == NULL) {
        return NULL;
    }
    Order* temp = queue;
    queue = queue->next;
    free(temp);
    return queue;
}
void display(Order* queue) {
    printf("Display Orders by Order Time:\n");
    Order* temp = queue;
    while (temp != NULL) {
        printf("- Order ID: %d, Customer Name: %s, Items: %s\n", temp->orderID, temp->customerName, temp->items);
        temp = temp->next;
    }
}
void updateOrder(Order* queue, int orderID, char* newItems) {
    Order* temp = queue;
    while (temp != NULL) {
        if (temp->orderID == orderID) {
            strcpy(temp->items, newItems);
            break;
        }
        temp = temp->next;
    }
}
Order* deleteOrder(Order* queue, int orderID) {
    if (queue == NULL) {
        return NULL;
    }

    if (queue->orderID == orderID) {
        Order* temp = queue;
        queue = queue->next;
        free(temp);
        return queue;
    }

    Order* current = queue;
    Order* prev = NULL;
    while (current != NULL && current->orderID != orderID) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Order with ID %d not found.\n", orderID);
        return queue;
    }

    prev->next = current->next;
    free(current);
    return queue;
}
void freeQueue(Order* queue) {
    Order* temp;
    while (queue != NULL) {
        temp = queue;
        queue = queue->next;
        free(temp);
    }
}
int main() {
    Order* queue = NULL;
    char choice;
    char customerName[100];
    int orderID;
    char items[100];
    char orderTime[100];
    do {
        printf("1. Add Order\n");
        printf("2. Remove First Order\n");
        printf("3. Remove Order by ID\n");
        printf("4. Display Orders\n");
        printf("5. Update Order Items\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        switch (choice) {
            case '1':
                printf("Enter Customer Name: ");
                scanf(" %[^\n]s", customerName);
                printf("Enter Order ID: ");
                scanf("%d", &orderID);
                printf("Enter Items: ");
                scanf(" %[^\n]s", items);
                queue = enqueue(queue, customerName, orderID, items, orderTime);
                printf("Order added successfully.\n\n");
                display(queue);
                break;
            case '2':
                queue = dequeue(queue);
                printf("Oldest order removed successfully.\n\n");
                display(queue);
                break;
            case '3':
                printf("Enter Order ID: ");
                scanf("%d", &orderID);
                deleteOrder(queue, orderID);
                display(queue);
                break;    
            case '4':
                display(queue);
                break;
            case '5':
                printf("Enter Order ID to update: ");
                scanf("%d", &orderID);
                printf("Enter New Items: ");
                scanf(" %[^\n]s", items);
                updateOrder(queue, orderID, items);
                printf("\n");
                display(queue);
                break;
            case '6':
                freeQueue(queue);
                printf("exiting...\n");
                break;
            default:
                printf("Invalid choice! Please choose again.\n");
                break;
        }
    } while (choice != '6');
    return 0;
}
