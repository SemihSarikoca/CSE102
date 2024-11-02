#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Order {
    char* customerName;
    int orderID;
    char* items;
    time_t orderTime;
    struct Order* next;
} Order;

typedef struct LIFO {
    Order* top;
} LIFO;

typedef struct FIFO {
    Order* front;
    Order* rear;
} FIFO;

Order* createOrder(char* customerName, int orderID, char* items, time_t orderTime);
void enqueue(Order** list, char* customerName, int orderID, char* items, time_t orderTime);
Order* dequeue(Order** list, time_t thresholdTime);
void dequeue_first(Order** list);

void serializeLIFO(LIFO* stack, const char* filename);
LIFO* deserializeLIFO(const char* filename);

void serializeFIFO(FIFO* queue, const char* filename);
FIFO* deserializeFIFO(const char* filename);

void printOrderList(Order* list);


int main() {
    Order* list = NULL;
    time_t thresholdTime = 10;

    int choice;
    char customerName[100];
    int orderID;
    char items[100];
    time_t orderTime;

    Order* removedOrders;

    LIFO stack;
    LIFO* deserializedLIFO;
    FIFO queue;
    FIFO* deserializedFIFO;


    do {
        printf("\n--- Order Management System ---\n");
        printf("1. Add an order\n");
        printf("2. Remove orders older than 24 hours\n");
        printf("3. Print order list\n");
        printf("4. Serialize LIFO data structure\n");
        printf("5. Deserialize LIFO data structure\n");
        printf("6. Serialize FIFO data structure\n");
        printf("7. Deserialize FIFO data structure\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("\nEnter customer name: ");
                fgets(customerName, sizeof(customerName), stdin);
                customerName[strcspn(customerName, "\n")] = '\0';

                printf("Enter order ID: ");
                scanf("%d", &orderID);
                getchar();

                printf("Enter items: ");
                fgets(items, sizeof(items), stdin);
                items[strcspn(items, "\n")] = '\0';

                orderTime = time(NULL);

                enqueue(&list, customerName, orderID, items, orderTime);
                printf("Order added successfully!\n");
                break;
            case 2:
                    removedOrders = dequeue(&list, thresholdTime);
                    if (removedOrders == NULL) {
                        printf("No orders to remove.\n");
                    } else {
                        printf("\n--- Removed Orders ---\n");
                        printOrderList(removedOrders);
                        Order* temp;
                        while (removedOrders != NULL) {
                            temp = removedOrders;
                            removedOrders = removedOrders->next;
                            free(temp);
                        }
                        printf("----------------------\n");
                    }
                break;
            case 3:
                printf("\n--- Order List ---\n");
                printOrderList(list);
                printf("------------------\n");
                break;
            case 4:
                    stack.top = list;
                    serializeLIFO(&stack, "lifo_data.bin");
                    printf("LIFO data structure serialized to a binary file.\n");
                break;
            case 5:
                    deserializedLIFO = deserializeLIFO("lifo_data.bin");
                    if (deserializedLIFO == NULL) {
                        printf("Failed to deserialize LIFO data structure.\n");
                    } else {
                        printf("LIFO data structure deserialized from a binary file.\n");
                        list = deserializedLIFO->top;
                    }
                break;
            case 6:
                    queue.front = queue.rear = list;
                    serializeFIFO(&queue, "fifo_data.bin");
                    printf("FIFO data structure serialized to a binary file.\n");
                break;
            case 7:
                    deserializedFIFO = deserializeFIFO("fifo_data.bin");
                    if (deserializedFIFO == NULL) {
                        printf("Failed to deserialize FIFO data structure.\n");
                    } else {
                        printf("FIFO data structure deserialized from a binary file.\n");
                        list = deserializedFIFO->front;
                    }
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 8);

    Order* temp;
    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }

    return 0;
}

Order* createOrder(char* customerName, int orderID, char* items, time_t orderTime) {
    Order* newOrder = malloc(sizeof(Order));
    newOrder->customerName = strdup(customerName);
    newOrder->orderID = orderID;
    newOrder->items = strdup(items);
    newOrder->orderTime = orderTime;
    newOrder->next = NULL;
    return newOrder;
}
void enqueue(Order** list, char* customerName, int orderID, char* items, time_t orderTime) {
    Order* newOrder = createOrder(customerName, orderID, items, orderTime);

    if (*list == NULL) {
        *list = newOrder;
    } else {
        Order* current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newOrder;
    }
}
Order* dequeue(Order** list, time_t thresholdTime) {
    Order* current = *list;
    Order* previous = NULL;
    Order* removedOrders = NULL;

    time_t currentTime = time(NULL);
    while (current != NULL) {
        if (currentTime - current->orderTime >= thresholdTime) {
            if (previous == NULL) {
                *list = current->next;
                current->next = removedOrders;
                removedOrders = current;
                current = *list;
            } else {
                previous->next = current->next;
                current->next = removedOrders;
                removedOrders = current;
                current = previous->next;
            }
        } else {
            previous = current;
            current = current->next;
        }
    }

    return removedOrders;
}
void dequeue_first(Order** list) {
    if (*list == NULL) {
        return;
    }
    Order* removedOrder = *list;
    *list = (*list)->next;
    removedOrder->next = NULL;

    free(removedOrder->customerName);
    free(removedOrder->items);
    free(removedOrder);
}

void serializeLIFO(LIFO* stack, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file != NULL) {
        Order* current = stack->top;
        while (current != NULL) {
            fwrite(current, sizeof(Order), 1, file);
            current = current->next;
        }
        fclose(file);
    }
}
LIFO* deserializeLIFO(const char* filename) {
    LIFO* stack = malloc(sizeof(LIFO));
    stack->top = NULL;

    FILE* file = fopen(filename, "rb");
    if (file != NULL) {
        Order temp;
        while (fread(&temp, sizeof(Order), 1, file) == 1) {
            Order* newOrder = createOrder(temp.customerName, temp.orderID, temp.items, temp.orderTime);
            newOrder->next = stack->top;
            stack->top = newOrder;
        }
        fclose(file);
        return stack;
    } else {
        free(stack);
        return NULL;
    }
}

void serializeFIFO(FIFO* queue, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file != NULL) {
        Order* current = queue->front;
        while (current != NULL) {
            fwrite(current, sizeof(Order), 1, file);
            current = current->next;
        }
        fclose(file);
    }
}
FIFO* deserializeFIFO(const char* filename) {
    FIFO* queue = malloc(sizeof(FIFO));
    queue->front = queue->rear = NULL;

    FILE* file = fopen(filename, "rb");
    if (file != NULL) {
        Order temp;
        while (fread(&temp, sizeof(Order), 1, file) == 1) {
            Order* newOrder = createOrder(temp.customerName, temp.orderID, temp.items, temp.orderTime);
            newOrder->next = NULL;
            if (queue->front == NULL) {
                queue->front = queue->rear = newOrder;
            } else {
                queue->rear->next = newOrder;
                queue->rear = newOrder;
            }
        }
        fclose(file);
        return queue;
    } else {
        free(queue);
        return NULL;
    }
}

void printOrderList(Order* list) {
    Order* current = list;
    while (current != NULL) {
        printf("Customer Name: %s, Order ID: %d, Items: %s, Order Time: %s", current->customerName, current->orderID, current->items, ctime(&current->orderTime));
        current = current->next;
    }
}
