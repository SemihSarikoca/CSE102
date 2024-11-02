#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

void part1();
void part2();

int main(){
    part1();
    part2();
    return 0;
}

void part1(){
    int arr[MAX_SIZE], num, i, new_size;
    for(i = 0; i < MAX_SIZE; i++){
        scanf("%d", &num);
        if(num == -100) break;
        arr[i] = num;
        new_size = i+1;
    }
    char label[new_size];
    for(i = 0; i < new_size; i++){
        if(arr[i]%2 == 0){
            label[i] = 'e';
        }
        else{
            label[i] = 'o';    
        }
    }
    printf("output:\n");
    for(i = 0; i < new_size; i++){
        printf("%d %c\n", arr[i], label[i]);
    } 
}

void part2(){
    FILE *fp;
    fp = fopen("text.txt", "r");
    if(fp == NULL){
        printf("Error: Could not open file.\n");
        exit(1);
    }
    int i, row;
    fscanf(fp, " %d", &row);
    int ages[row];
    char occupations[row], teams[row], team;
    float salary[row];
    for(i = 0; i < row; i++){
        fscanf(fp, " %d %c %f %c", &ages[i], &occupations[i], &salary[i], &teams[i]);
    }
    int counter = 0;
    float average_s, total_s = 0.0;
    printf("Please select a team: ");
    scanf(" %c", &team);
    for(i = 0; i < row; i++){
        if(teams[i] == team){
            counter++;
            total_s += salary[i];
        }
    }
    if(counter == 0){
        printf("There are no fans of b in the database!\n");
    }
    else{
        average_s = total_s / counter;
        printf("Average salaries of fans of %c: %.2f\n", team, average_s);
    }
    fclose(fp);
}