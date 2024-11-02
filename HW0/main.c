#include <stdio.h>
#include "util.h"

int main() {

    /* A fractional number: 13/7 */
    int num1 = 13, den1 = 7;
    /* A second fractional number: 13/11 */
    int num2 = 30, den2 = 11;
    /* An unitilized fractional number */
    int num3, den3;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    int usernum1,userden1; /* user input fractional number*/
    int usernum2,userden2; /* user input fractional number*/
    int usernum3,userden3; /* variable for the computation */

    printf("Write the numerator and denominator for the first number\n"); 
    scanf("%d",&usernum1);
    scanf("%d",&userden1);
    if(userden1==0){ /*error control for undefined fractional number*/
        printf("Error: pick denominator different from 0\n");
        return 0;
    }
   
    printf("Write the numerator and denominator for the second number\n");
    scanf("%d",&usernum2);
    scanf("%d",&userden2);
    if(userden2==0){ /*error control for undefined fractional number*/
        printf("Error: pick denominator different from 0\n");
        return 0;
    }
    
    printf("Multiplication: ");
    fraction_mul(usernum1, userden1, usernum2, userden2, &usernum3, &userden3);
    fraction_print(usernum3, userden3);
    printf("\n");

    printf("Division: ");
    fraction_div(usernum1, userden1, usernum2, userden2, &usernum3, &userden3);
    fraction_print(usernum3, userden3);
    printf("\n");

    return(0);
}