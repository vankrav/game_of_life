#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE_X 80
#define SIZE_Y 25

int fillMatrixFromFile(int matrix[SIZE_Y][SIZE_X], const char* filename);

void draw(int matrix[SIZE_Y][SIZE_X]);

void logic(int matrix[SIZE_Y][SIZE_X], int matrix_next[SIZE_Y][SIZE_X]);

int run_game(int matrix[SIZE_Y][SIZE_X], int matrix_next[SIZE_Y][SIZE_X]);
/*------------------------------------MAIN------------------------------------*/

int main(int argc, char* argv[]) {
    int matrix[SIZE_Y][SIZE_X] = {0};
    int matrix_next[SIZE_Y][SIZE_X] = {0};

    fillMatrixFromFile(matrix, argv[1]);
    printf("okay");

    char c = 0;
    int s = 0;
    while (scanf("%c", &c) && c != 'q') {
        // printf("yyyyyyy %d yyyyyyyyyyy", s);
        run_game(matrix, matrix_next);
        // usleep(500000);
    }

    return 0;
}

int fillMatrixFromFile(int matrix[SIZE_Y][SIZE_X], const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка при открытии файла");
        return -1;
    }

    char buffer[SIZE_X * 2];
    for (int y = 0; y < SIZE_Y; ++y) {
        if (!fgets(buffer, SIZE_X * 2, file)) {
            break;  // Достигнут конец файла или ошибка чтения
        }
        for (int x = 0; x < SIZE_X; ++x) {
            matrix[y][x] = buffer[x] == '0' ? 0 : 1;
        }
    }

    fclose(file);
    return 0;
}

int run_game(int matrix[SIZE_Y][SIZE_X], int matrix_next[SIZE_Y][SIZE_X]) {
    draw(matrix);
    logic(matrix, matrix_next);
    for (int y = 0; y < SIZE_Y; y++)
        for (int x = 0; x < SIZE_X; x++) matrix[y][x] = matrix_next[y][x];

    return 1;
}

void logic(int matrix[SIZE_Y][SIZE_X], int matrix_next[SIZE_Y][SIZE_X]) {
    int sum_around = 0;
    for (int y = 0; y < SIZE_Y; y++) {
        for (int x = 0; x < SIZE_X; x++) {
            sum_around = 0;
            sum_around += matrix[(SIZE_Y + y + 1) % SIZE_Y][(SIZE_X + x) % SIZE_X];
            sum_around += matrix[(SIZE_Y + y + 1) % SIZE_Y][(SIZE_X + x + 1) % SIZE_X];
            sum_around += matrix[(SIZE_Y + y) % SIZE_Y][(SIZE_X + x + 1) % SIZE_X];
            sum_around += matrix[(SIZE_Y + y - 1) % SIZE_Y][(SIZE_X + x + 1) % SIZE_X];
            sum_around += matrix[(SIZE_Y + y - 1) % SIZE_Y][(SIZE_X + x) % SIZE_X];
            sum_around += matrix[(SIZE_Y + y - 1) % SIZE_Y][(SIZE_X + x - 1) % SIZE_X];
            sum_around += matrix[(SIZE_Y + y) % SIZE_Y][(SIZE_X + x - 1) % SIZE_X];
            sum_around += matrix[(SIZE_Y + y + 1) % SIZE_Y][(SIZE_X + x - 1) % SIZE_X];
            if (matrix[y][x]) {
                if (sum_around == 2 || sum_around == 3)
                    matrix_next[y][x] = 1;
                else
                    matrix_next[y][x] = 0;
            } else {
                if (sum_around == 3)
                    matrix_next[y][x] = 1;
                else
                    matrix_next[y][x] = 0;
            }
        }
    }
}

void draw(int matrix[SIZE_Y][SIZE_X]) {
    printf("\n\n");

    printf(" ");
    for (int i = 0; i < SIZE_X; i++) printf("⎯");
    printf("\n");
    for (int y = 0; y < SIZE_Y; y++) {
        printf("|");
        for (int x = 0; x < SIZE_X; x++) {
            if (matrix[y][x])
                printf("#");
            else
                printf(" ");
        }
        printf("|\n");
    }

    printf(" ");
    for (int i = 0; i < SIZE_X; i++) printf("⎯");
    printf("\n");
}
