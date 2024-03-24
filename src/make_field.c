#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_X 80
#define SIZE_Y 24

int main() {
    srand(time(NULL)); 

    for (int y = 0; y < SIZE_Y; y++) {
        for (int x = 0; x < SIZE_X; x++)
            printf("%d", rand() % 2);
        printf("%d\n", rand() % 2);
    }
    return 0;
}