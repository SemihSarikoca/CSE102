#include <stdio.h>
#include <stdlib.h>
#define LINE_LENGTH 100

struct Stock {
    int sID;
    int pID;
    char branch[15];
    int current_stock;
};

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
int index_func(char arr[LINE_LENGTH], char c, int start_index) {
    for (int i=start_index ; i<LINE_LENGTH;i++) {
        if(arr[i] == c)
            return i;
    }
    return sizeof(arr)/sizeof(arr[0]);
}

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
void delete_a_product() {
    FILE *fp = fopen("products.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error: Unable to open file\n");
        exit(102);
    }

    int deletedLine, lineCounter = -1, flag = 0;
    char line[LINE_LENGTH];
    int index;
    printf("pID of the product wanted to be deleted: ");
    scanf(" %d", &deletedLine);
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        lineCounter++;
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

    while (fgets(line, LINE_LENGTH, fp) != NULL) {
        lineCounter++;
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
void add_feature_to_products(char features[10][15]) {
    FILE *fp = fopen("products.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error: Unable to open file\n");
        exit(111);
    }
    int lineCounter = 0, flag = 0;
    
    int feature_index = 0;
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
        }
        
        else
            fprintf(temp, "%sNone\n", line);
        lineCounter++;
    }
    fclose(fp);
    fclose(temp);
    
    remove("products.txt");
    rename("temp.txt", "products.txt");
    printf("New Feature succesfully added!\n\n");
}

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
            int total_stock = 0;
            while (fgets(buffer, LINE_LENGTH, s_fp) != NULL) {
                sscanf(buffer, "%d,%d,%[^,],%d", &s.sID, &s.pID, s.branch, &s.current_stock);
                if (lineCounter == s.pID) {
                    total_stock += s.current_stock;
                }
            }
            memory[match_counter][2] = total_stock; 
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



int main(){
    char features[10][15] = {"TYPE","NAME","BRAND","PRICE","-","-","-","-","-","-"};
    //add_a_new_product(features);
    //delete_a_product();
    //update_a_product(features);
    //add_feature_to_products(features);
    //filter_products(features);
    //brand_stock_control();
    return 0;
}