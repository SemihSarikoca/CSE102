#include <stdio.h>
#include "util.h"

void func_gcd(int n1, int n2, int gcd){ /* Euclidean method for more detailed information --> https://en.wikipedia.org/wiki/Euclidean_algorithm*/    
    printf("====== GCD CALCULATOR ======\n");
    printf("First number :");
    scanf("%d",&n1);
    printf("%d\n",n1);
    printf("Second number:");
    scanf("%d",&n2);
    printf("%d\n",n2);
    while(1){
        if(n1>n2){
            n1=n1-n2;
        }
        if(n2>n1){
            n2=n2-n1;
        }
        if(n1==n2){
            gcd = n1;
            break;
        }
    }
   printf("GCD of the two number: %d",gcd);
   printf("\n\n");
}

void visual_add(int n1, int n2, int sum){
    printf("====== Visual Addition ======\n");
    printf("First number :");
    scanf("%d",&n1);
    printf("%d\n",n1);
    printf("Second number:");
    scanf("%d",&n2);
    printf("%d\n",n2);
    sum=n1+n2; /*main result-sum*/
    printf("Result:\n");
    printf("%7d\n",n1);
    printf("%7d\n",n2);
    printf("+\n-------\n");
    printf("%7d",sum);
    printf("\n\n");
}

void visual_mul(int n1, int n2, int mul){
    printf("====== Visual Multiplication ======\n");
    printf("First number :");
    scanf("%d",&n1);
    printf("%d\n",n1);
    printf("Second number:");
    scanf("%d",&n2);
    printf("%d\n",n2);
    mul=n1*n2; /*main result-product*/
    printf("Result:\n");
    printf("%7d\n",n1);
    printf("%7d\n",n2);
    int prod1,prod2,prod3;
    prod1=(n2%10)*n1; /*intermediate product 1*/
    prod2=((n2%100)/10)*n1; /*intermediate product 2*/
    prod3=(n2/100)*n1; /*intermediate product 3*/
    printf("*\n-------\n");
    printf("%7d\n",prod1);
    printf("%6d\n",prod2);
    printf("%5d\n",prod3);
    printf("+\n-------\n");
    printf("%7d",mul);
    printf("\n\n");
}

void func_bigorless(int n1){
    printf("====== Big or Less ======");
    printf("Enter an integer between [1,10]:");
    scanf("%d",&n1);
    printf("%d\n",n1);
    if(n1<1 || n1>10){/*check for invalid input*/
        printf("Invalid input\n");
    }
    if(n1>5 && n1<=10){
        printf("The integer you entered is greater than 5\n");
    }
    if(n1>=1 && n1<=5){
        printf("The integer you entered is less than or equal to 5\n");
    }
}