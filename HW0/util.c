#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    printf("%d//%d", numerator, denominator);
}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1 * d2 - n2 * d1;
    *d3 = d1 * d2;
    fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3=n1*n2;
    *d3=d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3=n1*d2; 
    *d3=d1*n2;
    fraction_simplify(n3, d3);
} /* end fraction_div */

/* Simplify the given fraction such that they are divided by their GCD */
void fraction_simplify(int * n, int * d) {
    int s; /*for loop variable*/
    int f1=1; /*flag for returing the absolute value*/
    int f2=1; /*flag for returing the absolute value*/
    int gcd=1;
    if(*n<0){ /*taking absolute value for the gcd procedure*/
        *n= -*n;
        f1= -1;
    }

    if(*d<0){ /*taking absolute value for the gcd procedure*/
        *d= -*d;
        f2= -1;
    }

    for(s=1;s<=*n && s<=*d;s++){ /*finding greatest common divisor*/
        if(*n%s==0 && *d%s==0){
            gcd=s;
        }
    }
    *n=*n/gcd; /*simplification*/
    *n=*n*f1; /*turning number to original form if changed*/
    *d=*d/gcd; /*simplification*/
    *d=*d*f2; /*turning number to original form if changed*/
} /* end fraction_simplfy */
