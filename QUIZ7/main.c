#include <stdio.h>



int min_operations(char *s) {
    int count[26] = {0};
    int operations = 0;

    for (int i = 0; s[i]; i++) {
        count[s[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) {
            operations++;
        }
    }

    return operations;
}


int main() {
    char s[100];
    printf("Enter the string: ");
    scanf("%s", s);
    int result = min_operations(s);
    printf("Minimum number of operations: %d\n", result);

    return 0;
}


