#include <stdio.h>
#include "util.h"

int main(){
    int n1,n2;
    int gcd,sum,mul;
    
    func_gcd(n1,n2,gcd);
    visual_add(n1,n2,sum);
    visual_mul(n1,n2,mul);
    func_bigorless(n1);
    
    return 0;
}