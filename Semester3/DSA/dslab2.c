#include <stdio.h>


void n2_complexity(int *x, int *a) {
    int sum, count;
    for (int i=0;i<10;i++) {
        sum = 0;
        count = 0;
        for (int j = 0; j <= i; j++) {
            sum += x[j];
            count++;
        }
        a[i] = sum / count;
    }
}

void n_complexity(int *x, int *a) {
    int sum = 0, count = 0;
    for (int i=0;i<10;i++) {
        sum += x[i];
        count++;
        a[i] = sum / count;
    }
}

void print_array(int *a, int size, const char *message) {
    printf("%s: ", message);
    for (int i=0;i<size;i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int x[10]={10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int a[10];
    int size=10;

    //Order of N2
    n2_complexity(x, a);
    print_array(a, size, "Array A formed with O(n^2) time complexity");

    //Order of N
    n_complexity(x, a);
    print_array(a, size, "Array A formed with O(n) time complexity");
}
