#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 50
#define DATABASE_FILE "furniture_database.txt"

struct Furniture {
    char name[50];
    char color[20];
    float price;
    int serialNumber;
    int quantity;
};

void print_inventory(struct Furniture products[], int count);
void remove_inventory(struct Furniture products[], int *count);
void add_inventory(struct Furniture products[], int *count);
int read_inventory(struct Furniture products[]);

int search_name(struct Furniture products[], int count, char name[], int startIndex);
int search_color(struct Furniture products[], int count, char color[], int startIndex);

int main() {
    struct Furniture products[MAX_PRODUCTS];
    while (1) {
        int count = read_inventory(products);
        int k;
        char option;
        char searchName[50];
        char searchColor[20];
        printf("1 - See All Products\n2 - Add New Product\n3 - Remove Product\n4 - Search Product\n5 - Exit\n");
        scanf(" %c", &option);
        switch (option) {
            case '1':
                print_inventory(products, count);
                break;
            case '2':
                add_inventory(products, &count);
                break;
            case '3':
                remove_inventory(products, &count);
                break;
            case '4':
                printf("1 - Name\n2 - Color\n");
                scanf("%d", &k);
                if (k == 1) {
                    printf("Enter the name of product: ");
                    scanf("%s", searchName);
                    search_name(products, count, searchName, 0);
                } else if (k == 2) {
                    printf("Enter the color of product: ");
                    scanf("%s", searchColor);
                    search_color(products, count, searchColor, 0);
                }
                break;
            case '5':
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                break;
        }
    }
    return 0;
}

void print_inventory(struct Furniture products[], int count) {
    printf("\n----------- All Furniture -----------\n");
    printf("Name\tColor\tPrice\tSerial Number\tQuantity\n");
    printf("-------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("Name: %s\nColor: %s\nPrice: %.2f\nSerial Number: %d\nQuantity %d\n\n", products[i].name, products[i].color, products[i].price, products[i].serialNumber, products[i].quantity);
    }
    
    printf("-------------------------------------\n");
}
void remove_inventory(struct Furniture products[], int *count) {
    if (*count == 0) {
        printf("\nNo furniture available to remove.\n");
        return;
    }
    
    int lineCount;
    printf("\nEnter the line number of the product to remove: ");
    scanf("%d", &lineCount);
    
    if (lineCount < 0 || lineCount > *count) {
        printf("\nInvalid line number. Please enter a valid line number.\n");
        return;
    }
    
    int index = lineCount - 1;
    struct Furniture removedFurniture = products[index];

    // Shift elements to the left to remove the furniture
    for (int i = index; i < *count - 1; i++) {
        products[i] = products[i + 1];
    }
    
    (*count)--;
    
    // Save the changes to the database file
    FILE *file = fopen(DATABASE_FILE, "w");
    if (file == NULL) {
        printf("\nError opening file.\n");
        return;
    }
    fprintf(file, "%s %s %.2f %06d %d", products[0].name, products[0].color, products[0].price, products[0].serialNumber, products[0].quantity);
    for (int i = 1; i < *count; i++) {
        fprintf(file, "\n%s %s %.2f %06d %d", products[i].name, products[i].color, products[i].price, products[i].serialNumber, products[i].quantity);
    }
    
    fclose(file);
    printf("\nFurniture at line number %d removed successfully!\n", lineCount);
    printf("Removed Furniture Details:\n");
    printf("Name: %s\n", removedFurniture.name);
    printf("Color: %s\n", removedFurniture.color);
    printf("Price: %.2f\n", removedFurniture.price);
    printf("Serial Number: %06d\n", removedFurniture.serialNumber);
    printf("Quantity: %d\n", removedFurniture.quantity);


}
void add_inventory(struct Furniture products[], int *count) {
    if (*count >= MAX_PRODUCTS) {
        printf("\nCannot add more furniture. Maximum limit reached.\n");
        return;
    }
    
    struct Furniture newProduct;
    
    printf("\nEnter details of the new furniture:\n");
    printf("Name: ");
    scanf("%s", newProduct.name);
    printf("Color: ");
    scanf("%s", newProduct.color);
    printf("Price: ");
    scanf("%f", &newProduct.price);
    printf("Serial Number: ");
    scanf("%d", &newProduct.serialNumber);
    printf("Quantity: ");
    scanf("%d", &newProduct.quantity);
    
    products[*count] = newProduct;
    (*count)++;
    
    // Save the changes to the database file
    FILE *file = fopen(DATABASE_FILE, "a");
    if (file == NULL) {
        printf("\nError opening file.\n");
        return;
    }
    
    fprintf(file, "\n%s %s %.2f %06d %d", newProduct.name, newProduct.color, newProduct.price, newProduct.serialNumber, newProduct.quantity);
    fclose(file);
    printf("\nNew furniture added successfully!\n");
    printf("Added Furniture Details:\n");
    printf("Name: %s\n", newProduct.name);
    printf("Color: %s\n", newProduct.color);
    printf("Price: %.2f\n", newProduct.price);
    printf("Serial Number: %06d\n", newProduct.serialNumber);
    printf("Quantity: %d\n", newProduct.quantity);
}
int read_inventory(struct Furniture products[]) {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        printf("\nError opening file.\n");
        return 0;
    }
    int count = 0;
    while (!feof(file) && count < MAX_PRODUCTS) {
        fscanf(file, "%s %s %f %d %d\n", products[count].name, products[count].color, &products[count].price, &products[count].serialNumber, &products[count].quantity);
        count++;
    }
    fclose(file);
    return count;
}
int search_name(struct Furniture products[], int count, char name[], int startIndex) {
    if (startIndex >= count) {
        return -1;
    }
    if (strcmp(products[startIndex].name, name) == 0) {
        printf("Name: %s\n", products[startIndex].name);
        printf("Color: %s\n", products[startIndex].color);
        printf("Price: %.2f\n", products[startIndex].price);
        printf("Serial Number: %06d\n", products[startIndex].serialNumber);
        printf("Quantity: %d\n", products[startIndex].quantity);
        printf("-----------------------\n");
    }
    return search_name(products, count, name, startIndex + 1);
}
int search_color(struct Furniture products[], int count, char color[], int startIndex) {
    if (startIndex >= count) {
        return -1;
    }
    if (strcmp(products[startIndex].color, color) == 0) {
        printf("Name: %s\n", products[startIndex].name);
        printf("Color: %s\n", products[startIndex].color);
        printf("Price: %.2f\n", products[startIndex].price);
        printf("Serial Number: %06d\n", products[startIndex].serialNumber);
        printf("Quantity: %d\n", products[startIndex].quantity);
        printf("-----------------------\n");
    }
    return search_color(products, count, color, startIndex + 1);
}
