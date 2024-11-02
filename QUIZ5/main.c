#include <stdio.h>

void CFconverter();
void convert_C();
void convert_F();
void numberinverter();
void numberconverter();
void convert_print();
int decimalToBinary(int num);

void main(){
    CFconverter();
    numberinverter();
    numberconverter();
}
// Part 1
void CFconverter(){
    char option;
    printf("---------Part1---------\n");
    do{
        printf("Temperature Conversion Menu\n");
        printf("1. Convert Celsius to Fahrenheit\n");
        printf("2. Convert Fahrenheit to Celsius\n");
        printf("3. Quit\n");
        printf("Enter your choice (1-3): ");
        scanf(" %c",&option);
        switch (option){
            case '1':
                convert_C();
                break;
            case '2':
                convert_F();
                break;
            case '3':
                printf("Goodbye!\n");
                break;
            default:
                printf("invalid input!\n");
                break;
        }
    }while(option != '3');
}
void convert_C(){
    double cel, fah;
    printf("Enter the temperature value to convert: ");
    scanf(" %lf",&cel);
    fah = cel * (9.0/5.0) + 32;
    printf("%.2f Celsius = %.2f Fahrenheit\n\n",cel,fah);
}
void convert_F(){
    double cel, fah;
    printf("Enter the temperature value to convert: ");
    scanf(" %lf",&fah);
    cel = (5.0/9.0) * (fah - 32);
    printf("%.2f Fahrenheit = %.2f Celsius\n\n",fah,cel);
}
// Part 2 
void numberinverter(){
    int number, reversed=0, digit=0;
    printf("---------Part2---------\n");
    do{
        printf("Enter a number (3, 4, or 5 digits): ");
        scanf(" %d", &number);
        int temp = number;
        while (temp != 0){
            temp /= 10;
            digit++;
        }
        if (digit < 3 || digit > 5) {
            printf("Invalid input! Number must have 3, 4, or 5 digits.\n");
        }
    }while(digit < 3 || digit > 5);
    while (number != 0) {
        int renum = number % 10;
        reversed = reversed * 10 + renum;
        number /= 10;
    }
    printf("%d\n", reversed);
}


// Part 3
void numberconverter(){
    char option;
    printf("---------Part3---------\n");
    do{
        printf("Menu:\n");
        printf("1. Convert a number to decimal, binary, octal, and hexadecimal\n");
        printf("2. Quit\n");
        printf("Enter your choice (1-2): ");
        scanf(" %c",&option);
        switch (option){
            case '1':
                convert_print();
                break;
            case '2':
                printf("Goodbye!\n");
                break;
            default:
                printf("invalid input!\n");
                break;
        }
    }while(option != '2');
}
void convert_print(){
    int num;
    printf("Enter a number: ");
    scanf(" %d",&num);
    printf("Binary equivalent: %ld\n", decimalToBinary(num));
    printf("Octal equivalent: %o\n", num);
    printf("Hexadecimal equivalent: %x\n", num);
}
int decimalToBinary(int num){
    int binarynumber = 0, base = 1;
    while (num > 0){
        binarynumber = binarynumber + ((num % 2) * base);
        num /= 2;
        base *= 10;
    }
    return binarynumber;
}
