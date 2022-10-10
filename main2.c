#include <stdio.h>

int s(int n);

int main() {
    int result = s(4);
    printf("%d", result);

    return 0;
}

int s(int n) {
    int sum;
    if (n == 0)sum = 0;
    else {
        int x;
        scanf("%d", &x);
        sum = s(n - 1) + x;
    }
    return sum;
}