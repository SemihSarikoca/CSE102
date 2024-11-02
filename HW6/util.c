#include <stdio.h>
#include <stdlib.h>
#include "util.h"

#define LINE_LENGTH 100
//compare 2 array return 0 if true retun -1 if false
int mystrcmp(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i])
            return -1;
        else if (s1[i] > s2[i])
            return 1;
        i++;
    }
    if (s1[i] == '\0' && s2[i] == '\0')
        return 0;
    else if (s1[i] == '\0')
        return -1;
    else
        return 1;
}
//count one point to another in the string(char array) and return the index
int index_func(char arr[], char c, int start_index) {
    for (int i=start_index ; i<LINE_LENGTH;i++) {
        if(arr[i] == c)
            return i;
    }
    return sizeof(arr)/sizeof(arr[0]);
}
struct Stock {
    int sID;
    int pID;
    char branch[15];
    int current_stock;
};
//menu
void menu() {
    int option, loopflag = 1;
    char features[10][15] = {"TYPE","NAME","BRAND","PRICE","-","-","-","-","-","-"};
    while (loopflag) {
        printf("Welcome operator, please select an option to continue:\n");
        printf("1- File Operations\n2- Query products\n3- Check stock status\n4- Stock control by brand\n5- Export report\n");
        scanf("%d", &option);
        switch (option) {
            case 1:
                file_operations(features);
                break;
            case 2:
                search_products(features);
                break;
            case 3:
                check_stock();
                break;
            case 4:
                brand_stock_control();
                break;
            case 5:
                printf("Exoprting the report...\n");
                loopflag = 0;
                break;
            default:
                printf("Warning: Choose one of the options!\n");
                break;
        }
    }
}
//fileoperation submenu
void file_operations(char features[10][15]) {
    int option, loopflag = 1;
    while (loopflag) {
        printf("Welcome to submenu of file operations, please select an option to continue:\n");
        printf("1- Add a new product\n2- Delete a product\n3- Update a product\n4- Add feature to products\n5- Add a new stock entry\n6- Delete a stock entry\n7- Update a stock entry\n8- Back to main menu\n");
        scanf("%d", &option);
        switch (option) {
            case 1:
                add_a_new_product(features);
                break;
            case 2:
                delete_a_product();
                break;
            case 3:
                update_a_product(features);
                break;
            case 4:
                add_feature_to_products(features);
                break;
            case 5:
                add_a_new_stock();
                break;
            case 6:
                delete_a_stock();
                break;
            case 7:
                update_a_stock();
                break;
            case 8:
                printf("Returning to the main menu...\n");
                loopflag = 0;
                break;
            default:
                printf("Warning: Choose one of the options!\n");
                break;
        }
    }
}
//add new feature to end of the product, increment pID by 1
void add_a_new_product(char features[10][15]) {
    FILE *fp = fopen("products.txt", "r+");
    if (fp == NULL) {
        printf("Error: Unable to open file\n");
        exit(101);
    }
    int lineCounter = 0;
    char line[LINE_LENGTH];
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        if (line[0] == '\n') {
            continue;
        }
        lineCounter++;
    }
    char product[10][15];
    int i = 0;
    while (mystrcmp(features[i], "-") != 0) {    
        printf("Enter %s of product: ", features[i]);
        scanf(" %s", product[i]);
        i++;
    }
    fseek(fp, 0, SEEK_END);
    i = 0;
    fprintf(fp, "%d", lineCounter);
    while (mystrcmp(features[i], "-") != 0) {    
        fprintf(fp, ",%s", product[i]);
        i++;
    }
    fprintf(fp, "\n");
    fclose(fp);
    printf("New product successfully added!\n\n");
}
//delete selected line and rearange the pID numbers
void delete_a_product() {
    FILE *fp = fopen("products.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error: Unable to open file\n");
        exit(102);
    }
    int deletedLine, lineCounter = -1, flag = 0, index;
    char line[LINE_LENGTH];
    printf("pID of the product wanted to be deleted: ");
    scanf(" %d", &deletedLine);
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        lineCounter++;
        if (line[0] == '\n') {
            continue;
        } 
        if(lineCounter == 0){
            fprintf(temp, "%s", line);
            continue;
        }
        if (deletedLine == lineCounter && flag == 0) {
            flag = 1;
            lineCounter--;
            continue;
        }
        index = index_func(line, ',', 0);
        fprintf(temp, "%d%s", lineCounter, &line[index]);
    }
    fclose(fp);
    fclose(temp);
    remove("products.txt");
    rename("temp.txt", "products.txt");
    switch (flag) {
        case 0:
            printf("There is no product with pID: %d in the data!\n\n", deletedLine);
            break;
        case 1:
            printf("Product succesfully deleted!\n\n");
            break;
    }
}
//update the selected part of the product
void update_a_product(char features[10][15]) {
    FILE *fp = fopen("products.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error: Unable to open file\n");
        exit(103);
    }
    int lineCounter = -1, flag = 0, i = 0, choice, update_id;
    char update_feature[15];

    printf("ID of the product wanted to be updated: ");
    scanf(" %d", &update_id);

    printf("Sellect the feature you want to update: \n");
    while (mystrcmp(features[i], "-") != 0) {    
        printf("%d-%s\n", i+1, features[i]);
        i++;
    }
    int total_feature = i;
    do {
        scanf("%d", &choice);
        if (choice > i)
            printf("Invalid choice, try again.\n");
    } while (choice > i);
    
    printf("Enter the new feature: ");
    scanf("%s", update_feature);

    int update_pointer, id_index = 0;
    char line[LINE_LENGTH];
    rewind(fp);
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        lineCounter++;
        if (line[0] == '\n') {
            continue;
        } 
        if (lineCounter == 0) {
            fprintf(temp, "%s", line);
            continue;
        }
        id_index = index_func(line, ',', 0);
        if (update_id == lineCounter && flag == 0) {
            flag = 1; 
            i = 0, update_pointer = 0;
            while (update_pointer < choice) {
                if (line[i] == ',') {
                    update_pointer++;
                }
                i++;
            }
            if (total_feature == choice) {
                fprintf(temp, "%.*s%s\n", i, line, update_feature);
            } else {
                fprintf(temp, "%.*s%s,", i, line, update_feature);
                i = 0, update_pointer = 0;
                while (update_pointer < choice+1) {
                    if (line[i] == ',') {
                    update_pointer++;
                    }
                    i++;
                }
                fprintf(temp, "%s", &line[i]);
            }
        } else {
            fprintf(temp, "%d%s", lineCounter, &line[id_index]);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("products.txt");
    rename("temp.txt", "products.txt");
    switch (flag) {
        case 0:
            printf("There is no product with pID: %d in the data!\n\n", update_id);
            break;
        case 1:
            printf("Product succesfully updated!\n\n");
            break;
    }
}
//add new feature the features array and this feature become "None" for all products until update_product called and updated
void add_feature_to_products(char features[10][15]) {
    FILE *fp = fopen("products.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error: Unable to open file\n");
        exit(111);
    }
    int lineCounter = 0, flag = 0, feature_index = 0;
    for (int i = 0; i<10; i++) {
        if (mystrcmp(features[i], "-") == 0) {
            feature_index = i;
            break;
        }
    }
    printf("Enter the name of the new feature: ");
    scanf(" %s", features[feature_index]);
    char line[LINE_LENGTH];
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        if (line[0] == '\n') {
            continue;
        }
        int k = index_func(line, '\n', 0);
        line[k] = ',';
        if (lineCounter == 0 && flag == 0){
            flag = 1;
            fprintf(temp, "%s%s\n", line, features[feature_index]);
        } else {
            fprintf(temp, "%sNone\n", line);
        } 
        lineCounter++;
    }
    fclose(fp);
    fclose(temp);
    remove("products.txt");
    rename("temp.txt", "products.txt");
    printf("New Feature succesfully added!\n\n");
}
//add new stock to the end of the stocks increment sID by one
void add_a_new_stock() {
    FILE *fp = fopen("stocks.txt", "r+");
    if (fp == NULL) {
        printf("Error: Unable to open file\n");
        exit(201);
    }
    struct Stock stock;
    int lineCounter = 0;
    char line[LINE_LENGTH];
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        if (line[0] == '\n') {
            continue;
        }
        lineCounter++;
    }

    FILE *fp2 = fopen("products.txt", "r");
    if (fp2 == NULL) {
        printf("Error: Unable to open file\n");
        exit(202);
    }
    int productCounter = 0;
    while (fgets(line, LINE_LENGTH, fp2) != NULL) {
        if (line[0] == '\n') {
            continue;
        }
        productCounter++;
    }
    fclose(fp2);

    printf("Enter pID of stock: ");
    scanf(" %d", &stock.pID);
    if (stock.pID > productCounter || stock.pID < 1){
        printf("Invalif pID!\n");
        exit(203);
    }
    printf("Enter branch of stock: ");
    scanf(" %s", stock.branch);
    printf("Enter current stock of product: ");
    scanf(" %d", &stock.current_stock);

    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%d,%d,%s,%d\n", lineCounter + 1, stock.pID, stock.branch, stock.current_stock);
    fclose(fp);

    printf("New stock successfully added!\n\n");
}
//delete the selected line of the stocks and rearange the sID values
void delete_a_stock() {
    FILE *fp = fopen("stocks.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error: Unable to open file\n");
        exit(204);
    }
    struct Stock stock;
    int deletedLine, lineCounter = -1, flag = 0;
    char line[LINE_LENGTH];
    printf("sID of the stock wanted to be deleted: ");
    scanf(" %d", &deletedLine);
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        lineCounter++;
        if (line[0] == '\n') {
            continue;
        } 
        if (lineCounter == 0) {
            fprintf(temp, "%s", line);
            continue;
        }
        sscanf(line, "%d,%d,%[^,],%d", &stock.sID, &stock.pID, stock.branch, &stock.current_stock);
        if (deletedLine == stock.sID) {
            flag = 1;
            lineCounter--;
            continue;
        }
        fprintf(temp, "%d,%d,%s,%d\n", lineCounter, stock.pID, stock.branch, stock.current_stock);
    }
    fclose(fp);
    fclose(temp);
    remove("stocks.txt");
    rename("temp.txt", "stocks.txt");
    switch (flag) {
        case 0:
            printf("There is no stock with sID: %d in the data!\n\n", deletedLine);
            break;
        case 1:
            printf("Stock succesfully deleted!\n\n");
            break;
    }
}
//change on the existing stock 
void update_a_stock() {
    FILE *fp = fopen("stocks.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error: Unable to open file\n");
        exit(205);
    }

    char line[LINE_LENGTH];
    FILE *fp2 = fopen("products.txt", "r");
    if (fp2 == NULL) {
        printf("Error: Unable to open file\n");
        exit(206);
    }
    int productCounter = 0;
    while (fgets(line, LINE_LENGTH, fp2) != NULL) {
        if (line[0] == '\n') {
            continue;
        }
        productCounter++;
    }
    fclose(fp2);

    struct Stock stock;
    int newCurrentStrock, newPID;
    char newBranch[15];

    int updatedLine;
    printf("sID of the stock wanted to be updated: ");
    scanf(" %d", &updatedLine);
    int choice;
    printf("What do you want to update:\n1- pID\n2- Branch\n3- Current Stock\n");
    scanf(" %d", &choice);
    
    switch (choice) {
        case 1:
            printf("Enter the new type: ");
            scanf(" %d", &newPID);
            if (newPID > productCounter || newPID < 1) {
                printf("Invalif pID!\n");
                fclose(fp);
                fclose(temp);
                exit(207);
            }
            break;
        case 2:
            printf("Enter the new name: ");
            scanf(" %s", newBranch);
            break;
        case 3:
            printf("Enter the new current stock: ");
            scanf(" %d", &newCurrentStrock);
            break;
        default:
            printf("Invalid choice!\n");
            fclose(fp);
            fclose(temp);
            exit(208);
    }
    int lineCounter = 0, flag = 0;
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        if (line[0] == '\n') {
            continue;
        } 
        lineCounter++;
        sscanf(line, "%d,%d,%[^,],%d", &stock.sID, &stock.pID, stock.branch, &stock.current_stock);
        if (updatedLine == stock.sID) {
            flag = 1;
            switch (choice) {
                case 1:
                    fprintf(temp, "%d,%d,%s,%d\n", lineCounter, newPID, stock.branch, stock.current_stock);
                    break;
                case 2:
                    fprintf(temp, "%d,%d,%s,%d\n", lineCounter, stock.pID, newBranch, stock.current_stock);
                    break;
                case 3:
                    fprintf(temp, "%d,%d,%s,%d\n", lineCounter, stock.pID, stock.branch, newCurrentStrock);
                    break;
            }
        }
        else fprintf(temp, "%d,%d,%s,%d\n", lineCounter, stock.pID, stock.branch, stock.current_stock);
    }
    fclose(fp);
    fclose(temp);
    remove("stocks.txt");
    rename("temp.txt", "stocks.txt");
    switch (flag) {
        case 0:
            printf("There is no stock with sID: %d in the data!\n\n", updatedLine);
            break;
        case 1:
            printf("Stock succesfully updated!\n\n");
            break;
    }
}
//search products sub menu
void search_products(char features[10][15]) {
    int option, loopflag = 1;
    while (loopflag) {
        printf("Welcome operator submenu of query products, please select an option to continue:\n");
        printf("1- List all products\n2- Filter products\n3- Back to main menu\n");
        scanf("%d", &option);
        switch (option) {
            case 1:
                list_all_products();
                break;
            case 2:
                filter_products(features);
                break;
            case 3:
                printf("Returning to the main menu...\n");
                loopflag = 0;
                break;
            default:
                printf("Warning: Choose one of the options!\n");
                break;
        }
    }
}
//read char by char and prints char by char
void list_all_products() {
    FILE *fp = fopen("products.txt", "r");
    char c;
    while ((c = fgetc(fp)) != EOF) {
        printf("%c", c);
    }
    fclose(fp);
}
//filter the products based on user input
void filter_products(char features[10][15]) {
    FILE *fp = fopen("products.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error: Unable to open file\n");
        exit(102);
    }
    char filter[LINE_LENGTH];
    printf("Enter the filter instruction: ");

    scanf("%s", filter);

    
    int index = -1, min_index = 0, max_index = 0, feature_index = 0;
    int filter_size = sizeof(filter)/sizeof(filter[0]);


    while (index < filter_size) {
        index = index_func(filter, ',', index+1);
        char feature_type[index], line[LINE_LENGTH];
        for (int i=0; i<index; i++) {
            feature_type[i] = filter[i];
        }

        
        if (mystrcmp(feature_type, "PRICE") == 0) {

            min_index = index_func(filter, ',', index+1);
            char min[min_index - (index+1)];
            for (int i = index+1; i < min_index; i++) {
                min[i-(index+1)] = filter[i];
            }
            double min_price = atof(min);
            
            max_index = index_func(filter, ',', min_index+1);
            char max[max_index - (min_index+1)];
            for (int i = min_index+1; i < max_index; i++) {
                max[i-(min_index+1)] = filter[i];
            }
            double max_price = atof(max);
            index = max_index+1;
            feature_index = 4;

           
            while (fgets(line, LINE_LENGTH, fp) != NULL) {
                int index_counter = 0, j=0;
                char price[10];
                for(int i = 0; line[i] != '\0'; i++) {
                    if(line[i] == ',') {
                        index_counter++;
                        continue;
                    }
                    if(index_counter == feature_index) {
                        price[j] = line[i];
                        j++;
                    }
                    if(index_counter > feature_index) {
                        break;
                    }
                }
                price[j] = '\0';
                double numPrice = atof(price);
                if (numPrice <= max_price && numPrice >= min_price) {
                    printf("%s", line);
                } else {
                    continue;
                }
            }
            
        } else {
            for (int i = 0; i<10; i++) {
                if(mystrcmp(feature_type, features[i]) == 0){
                    feature_index = i;
                    break;
                }
            }
            while (fgets(line, LINE_LENGTH, fp) != NULL) {
                int index_counter = 0, j=0;
                char feature_data[15];


                for(int i = 0; line[i] != '\n' ; i++) {

                    if(line[i] == ',') {
                        index_counter++;
                        continue;
                    }
                    if(index_counter == feature_index) {
                        feature_data[j] = line[i];
                        j++;
                    }
                    if(index_counter > feature_index) {
                        break;
                    }
                }
                
                feature_data[j] = '\0';
                if (mystrcmp(feature_data, feature_type) == 0) {
                    printf("%s", line);
                }
            }
            
        }
    
    }

    fclose(fp);
    fclose(temp);
    remove("temp.txt");
}
//check stock sub menu
void check_stock() {
    char option; 
    int loopflag = 1;
    while (loopflag) {
        printf("\nWelcome to submenu of check stock, please select an option to continue:\n");
        printf("1. Query stock of a product in a branch\n");
        printf("2. List stock of all products in a branch\n");
        printf("3. List out-of-stock products in a branch\n");
        printf("4. Return to main menu\n");
        scanf(" %c", &option);
        switch (option) {
            case '1':
                check_stock_part1();
                break;
            case '2':
                check_stock_part2();
                break;
            case '3':
                check_stock_part3();
                break;
            case '4':
                printf("Returning to the main menu...\n");
                loopflag = 0;
                break;
            default:
                printf("Warning: Choose one of the options!\n");
                break;
        }
    }
}
//check stocks by pID and Branch features
void check_stock_part1() {
    FILE *fp = fopen("stocks.txt","r");
    int search_pid;
    char search_branch[15];
    struct Stock s;
    printf("Enter the pID of the product: ");
    scanf("%d", &search_pid);
    printf("Enter the branch of the product: ");
    scanf("%s", search_branch);
    char line[LINE_LENGTH];
    printf("List of the exact pID and branch: \n");
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%d,%d,%[^,],%d", &s.sID, &s.pID, s.branch, &s.current_stock);
        int index = index_func(line, ',', 0);
        if (mystrcmp(search_branch, s.branch) == 0 && search_pid == s.pID) {
            printf("%s", &line[index]);
        } 
    }
    fclose(fp);
    printf("\n");
}
//check stock by just branch
void check_stock_part2() {
    FILE *fp = fopen("stocks.txt","r");
    int search_pid;
    char search_branch[15];
    struct Stock s;
    printf("Enter the branch for stocks data: ");
    scanf("%s", search_branch);
    char line[LINE_LENGTH];
    printf("List of the stocks in branch: \n");
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%d,%d,%[^,],%d", &s.sID, &s.pID, s.branch, &s.current_stock);
        int index = index_func(line, ',', 0);
        if (mystrcmp(search_branch, s.branch) == 0) {
            printf("%s", &line[index]);
        } 
    }
    fclose(fp);
    printf("\n");
}
//check stock by branch and print if current stock is 0 (out of stock)
void check_stock_part3() {
    FILE *fp = fopen("stocks.txt","r");
    int search_pid;
    char search_branch[15];
    struct Stock s;
    printf("Enter the branch: ");
    scanf("%s", search_branch);
    char line[LINE_LENGTH];
    printf("List of out of stocks product in the branch: \n");
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%d,%d,%[^,],%d", &s.sID, &s.pID, s.branch, &s.current_stock);
        int index = index_func(line, ',', 0);
        if (mystrcmp(search_branch, s.branch) == 0 && s.current_stock == 0) {
            printf("%d%s", s.sID, &line[index]);
        } 
    }
    printf("\n");
    fclose(fp);
}

//based on brand value take pID PRICE and current stock. Store that in double 2d array. Then print the array.
void brand_stock_control() {
    FILE *p_fp = fopen("products.txt","r");
    FILE *s_fp = fopen("stocks.txt","r");
    struct Stock s;
    char search_brand[15], brand_name[15], brand_price[10];
    printf("Enter the brand for the list: ");
    scanf("%s", search_brand);
    double memory[LINE_LENGTH][3], price;
    char line[LINE_LENGTH], buffer[LINE_LENGTH];
    int lineCounter = -1, match_counter = 0;
    while (fgets(line, LINE_LENGTH, p_fp) != NULL) {
        lineCounter++;
        int index_counter = 0, dest_index = 3, j = 0, z = 0;;
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == ',') {
                index_counter++;
                continue;
            }
            if (index_counter == dest_index) {
                brand_name[j] = line[i];
                j++;
            }
            if (index_counter == dest_index+1) {
                brand_price[z] = line[i];
                z++;
            }
            if (index_counter > dest_index+1) {
                break;
            }
        }
        brand_name[j+1]='\0',  brand_price[z+1]='\0';
        price = atof(brand_price);
        if (mystrcmp(brand_name, search_brand) == 0) {
            printf("%s", brand_name);
            memory[match_counter][0] = lineCounter;
            memory[match_counter][1] = price;
            while (fgets(buffer, LINE_LENGTH, s_fp) != NULL) {
                sscanf(buffer, "%d,%d,%[^,],%d", &s.sID, &s.pID, s.branch, &s.current_stock);
                if (lineCounter == s.pID) {
                    memory[match_counter][2] = s.current_stock;
                    break;
                }
            }
            match_counter++;
        } 
    }
    fclose(p_fp);
    fclose(s_fp);
    for (int i = 0; i < LINE_LENGTH; i++) {
        if ((int)memory[i][0] == 0) {
            break;
        } else {
            printf(" pID: %d price: %0.2f total stock: %d\n", (int)memory[i][0], memory[i][1], (int)memory[i][2]);
        }
    }
}
