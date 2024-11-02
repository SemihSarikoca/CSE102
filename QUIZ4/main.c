#include <stdio.h>
#include "util.h"

int main(){
    char option;
    do {
        printf("Select an option:\n");
        printf("1. Write sequence of shapes to file\n");
        printf("2. Draw shapes from file\n");
        printf("3. Exit\n");
        printf("Option: ");
        scanf(" %c", &option);
        switch (option) {
            case '1':
                writetofile();
                break;
            case '2':
                drawfromfile();
                break;
            case '3':
                deletefile();
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
        printf("\n");
    } while (option != '3');
    return 0;
}