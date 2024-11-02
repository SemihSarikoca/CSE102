#include <stdio.h>
#include <math.h>
#include "util.h"

void leap_year(){
    printf("********** Leap Year Finder **********\n");
    /*user input*/
    int year;
    printf("Enter year:");
    scanf("%d",&year);
    printf("\n");
    /*check every posibilty and finish*/
    if(year%4000==0){ 
        printf("%d is not leap year\n",year);
    }
    else if(year%100==0 && year%400!=0){
        printf("%d is not leap year\n",year);
    }
    else if(year%100==0 && year%400==0){
        printf("%d is a leap year\n",year);
    }
    else if(year%4==0){
        printf("%d is a leap year\n",year);
    }
    else{
        printf("%d is not leap year\n",year);
    }
    printf("**************************************\n");
}
void enhanced_calculator(){
    printf("********* Enhanced Calculator ********\n");
    char output_type,op;
    int m,n,i,num3; /*num3 just for factorial bc. it has to be integer unlike others*/
    double num1,num2,result;
    printf("Enter the format of output (S or I): ");
    scanf(" %c",&output_type);
    printf("Enter the operation(+,-,*,/,!,^,%%): ");
    scanf(" %c",&op);
    switch (op){
        case '+':
            printf("Enter the first operand: ");
            scanf(" %lf",&num1);
            printf("Enter the second operand: ");
            scanf(" %lf",&num2);
            result=num1+num2;
            break;
        case '-':
            printf("Enter the first operand: ");
            scanf(" %lf",&num1);
            printf("Enter the second operand: ");
            scanf(" %lf",&num2);
            result=num1-num2;
            break;
        case '*':
            printf("Enter the first operand: ");
            scanf(" %lf",&num1);
            printf("Enter the second operand: ");
            scanf(" %lf",&num2);
            result=num1*num2;
            break;
        case '/':
            printf("Enter the first operand: ");
            scanf(" %lf",&num1);
            printf("Enter the second operand: ");
            scanf(" %lf",&num2);
            result=num1/(double)num2;
            break;
        case '!':
            do{
                printf("Enter the operand: ");
                scanf("%d",&num3);
                if(num3<0){ /*check for the posibility of user inpu to be negative*/
                    printf("Error: make sure to enter non-negative integer for factorial calculation!\n");
                } 
            }while(num3<0);
            result=1; /*even if the user enter 0 program will continue with 1 which is correct answer for 0!*/
            for(i=1;i<=num3;i++){ /*calculatin factorial with mul. every number before them*/
                result *= i;
            }
            break;
        case '^':
            printf("Enter the first operand: ");
            scanf(" %lf",&num1);
            printf("Enter the second operand: ");
            scanf(" %lf",&num2);
            result=pow(num1,num2);
            break;
        case '%':
            printf("Enter the first operand: ");
            scanf(" %lf",&num1);
            printf("Enter the second operand: ");
            scanf(" %lf",&num2);
            result=fmod(num1,num2);
            break;
        default: /*print for irregular operation*/
            printf("Error: enter one of the operation!\n");
            break;
    }
    if(output_type=='S' ||output_type=='s'){
        do{
            printf("Enter number of total digits of result: ");
            scanf(" %d",&m);
            printf("Enter number of digits after decimal point: ");
            scanf(" %d",&n);
            if(n>m){ /*warning user for n>m situation*/
                printf("Warning: number of total digits can not be bigger than the digits after decimal point!\n");
            } 
        } while (n>m); /*after the warning ask for n and m variable for user again. until it correct*/
        int exponent=floor(log10(fabs(result)))+1-(m-n); /*exponent of the e number. used fabs() for taking absolute value for log10 calculation. using floor() to take integer part of the log10 part.*/
        /* "floor(log10(fabs(result)))+1" part of the code calculate the integer digits of the result. it also become negative for the needed situations ex: 0.032 that number outputwill be -1 so code works both positive and negative way.*/
        double s_result=result / pow(10, exponent); /*dividing result to 10 power of exponent to calculate scientfic result coefficent*/
        printf("%0*.*fe%d\n",m,n,s_result,exponent); /*printing the result by usuing user input m and n. used 0 for 00.2 like situations but its actually just a backup*/
    }
    else if(output_type=='I' || output_type=='i'){
        printf("%d\n",(int)result); /*Turned double result to integer for the I output type. Using by (int)*/
    }
    else{ /*error for not picking s or i*/
        printf("Error: invalid output type! (pick S or I)\n");
    }
    printf("**************************************\n");
}
void grade_calculator(){
    int exam1, exam2, exam3, assig1, assig2; /*grades*/
    float average_exam, average_assig, final;
    printf("********** Grade Calculator **********\n");
    printf("Enter 3 exam grades of students:\n"); /*taking user exam grade input*/
    scanf("%d",&exam1);
    scanf("%d",&exam2);
    scanf("%d",&exam3);
    printf("Enter 2 assigment grades of students:\n"); /*taking user assigment input*/
    scanf("%d",&assig1);
    scanf("%d",&assig2);
    average_exam=(exam1+exam2+exam3)/3.0; /*average of exams*/
    average_assig=(assig1+assig2)/2.0; /*average of assigments*/
    final= average_exam*0.6 + average_assig*0.4; /*final grade calculation*/
    if(final>=60){
        printf("Final Grade: %.2f Passed!\n",final);
    }
    else{
        printf("Final Grade: %.2f Failed!\n",final);
    }
    printf("**************************************\n");
}  