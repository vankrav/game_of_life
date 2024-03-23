#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define SIZE_X 80
#define SIZE_Y 25

int** create_matrix(int col, int row);

void draw(int** matrix, int col, int row);

void logic(int** matrix, int** matrix_next, int col, int row);

int run_game(int** matrix, int** matrix_next);
/*------------------------------------MAIN------------------------------------*/

int main() {


    initscr();
    curs_set(0);
    noecho();
    timeout(300);


    int** matrix = create_matrix(SIZE_Y, SIZE_X);
    int** matrix_next = create_matrix(SIZE_Y, SIZE_X);

    for (int y = 1; y < SIZE_Y - 1; y++) {
        for (int x = 1; x < SIZE_X - 1; x++) {
            matrix[y][SIZE_X / 2] = 1;
            matrix[SIZE_Y / 2][x] = 1;
        }
    }

    char c = 0;

    while (c != 'q') {
        c = getch();
        run_game(matrix, matrix_next);
    }

    free(matrix);
    free(matrix_next);
    return 0;
}

int run_game(int** matrix, int** matrix_next) {
    clear();
    draw(matrix, SIZE_Y, SIZE_X);
    logic(matrix, matrix_next, SIZE_Y, SIZE_X);
    for (int y = 0; y < SIZE_Y; y++)
        for (int x = 0; x < SIZE_X; x++) matrix[y][x] = matrix_next[y][x];

    return 1;
}

void logic(int** matrix, int** matrix_next, int col, int row) {
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

int** create_matrix(int m, int n) {
    int** matrix = malloc(m * n * sizeof(int) + m * sizeof(int*));
    int* ptr = (int*)(matrix + m);

    for (int i = 0; i < m; i++) matrix[i] = ptr + n * i;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) matrix[i][j] = 0;

    return matrix;
}

void draw(int** matrix, int col, int row) {
    
    printw("\n\n");

    printw(" ");
    for (int i = 0; i < SIZE_X; i++) printw("-");
    printw("\n");
    for (int y = 0; y < SIZE_Y; y++) {
        printw("|");
        for (int x = 0; x < SIZE_X; x++) {
            if (matrix[y][x])
                printw("#");
            else
                printw(" ");
        }
        printw("|\n");
    }

    printw(" ");
    for (int i = 0; i < SIZE_X; i++) printw("-");
    printw("\n");
}