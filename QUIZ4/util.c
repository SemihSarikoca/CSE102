#include <stdio.h>
#include "util.h"

void d_square(int size){
	int i,j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1){
                printf("* ");
            }
            else{
                printf("  ");
            }
        }
        printf("\n");
    }
}

void d_triangle(int size){
	int row,col,space;
    for (row = 1; row <= size; row++){
        for (space = 1; space <= size-row; space++){
            	printf(" ");
        }
    	for (col = 1; col <= (2*row-1); col++){
        	if (row == 1 || row == size || col == 1 || col == (2*row-1)){
                printf("*");
        	}
        	else{
            	printf(" ");
        	}
    	}
        printf("\n");
    }
}

void writetofile() {
    FILE *file = fopen("shapes.txt", "w");
    char shapeType;
    int size;
    do {
        printf("Enter shape type (s for square, t for triangle, e to end): ");
        scanf(" %c", &shapeType);
        if (shapeType == 'e') {
            break;
        } 
        printf("Enter size (between 3 - 10): ");
        scanf("%d", &size);
        if (size < 3 || size > 10) {
            printf("Invalid size. Please enter a size between 3 - 10.\n");
            continue;
        }
        fprintf(file, "%c,%d\n", shapeType, size);
    } while (shapeType != 'e');
    fclose(file);
}

void drawfromfile(){
    char shapeType;
    int size;
    FILE *file = fopen("shapes.txt", "r");
    if (file == NULL){
        printf("Error opening file.\n");
        return;
    }
    while(fscanf(file, "%c,%d\n", &shapeType, &size) == 2){
        if(shapeType == 's'){
            d_square(size);
        }
        else if(shapeType == 't'){
            d_triangle(size);
        }
        else if(shapeType == 'e'){
            break;
        }
        else{
            printf("Error chose one of the options -> s, t, e");
        }
    }
    fclose(file);
}

void deletefile(){
    if (remove("shapes.txt") == 0){
        printf("File deleted successfully.\n");
    } 
	else{
        printf("Error deleting file.\n");
    }
}