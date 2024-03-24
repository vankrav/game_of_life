#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE_X 80
#define SIZE_Y 25
#define CELL "o"

int fillMatrixFromFile(int matrix[SIZE_Y][SIZE_X], const char* filename);

void draw(int matrix[SIZE_Y][SIZE_X], int s);

void logic(int matrix[SIZE_Y][SIZE_X], int matrix_next[SIZE_Y][SIZE_X]);

int run_game(int matrix[SIZE_Y][SIZE_X], int matrix_next[SIZE_Y][SIZE_X], int s);
/*------------------------------------MAIN------------------------------------*/

int main(int argc, char* argv[]) {
    initscr();
    curs_set(0);
    noecho();

    int s = 1;
    int prev_s = 1;

    int matrix[SIZE_Y][SIZE_X] = {0};
    int matrix_next[SIZE_Y][SIZE_X] = {0};

    fillMatrixFromFile(matrix, argv[1]);
    printw("okay");

    timeout(100);
    char c = 0;

    while (1) {
        s = getch() - 48;
        if (s > 0) prev_s = s;
        if (s <= 0) s = prev_s;
        run_game(matrix, matrix_next, s);
    }

    endwin();
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

int run_game(int matrix[SIZE_Y][SIZE_X], int matrix_next[SIZE_Y][SIZE_X], int s) {
    timeout(1000 / s);
    clear();
    draw(matrix, s);
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

void draw(int matrix[SIZE_Y][SIZE_X], int s) {
    printw("%d\n", s);

    printw(" ");
    for (int i = 0; i < SIZE_X; i++) printw("-");
    printw("\n");
    for (int y = 0; y < SIZE_Y; y++) {
        printw("|");
        for (int x = 0; x < SIZE_X; x++) {
            if (matrix[y][x])
                printw(CELL);
            else
                printw(" ");
        }
        printw("|\n");
    }

    printw(" ");
    for (int i = 0; i < SIZE_X; i++) printw("-");
    printw("\n");
}
