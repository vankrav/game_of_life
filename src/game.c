#include <ncurses.h>
#include <stdio.h>

#define SIZE_X 80
#define SIZE_Y 25
#define CELL "  "
#define BASE_SPEED 500

int run_game(int matrix[SIZE_Y][SIZE_X], int matrix_next[SIZE_Y][SIZE_X], int s);
int input(int matrix[SIZE_Y][SIZE_X], const char* filename);
void draw(int matrix[SIZE_Y][SIZE_X], int s);
void logic(int matrix[SIZE_Y][SIZE_X], int matrix_next[SIZE_Y][SIZE_X]);
int count_neighbors(int y, int x, int matrix[SIZE_Y][SIZE_X]);

int main(int argc, char* argv[]) {
    initscr();
    curs_set(0);
    noecho();

    start_color();
    init_color(COLOR_BLACK, 100, 100, 100);
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);

    int speed = 1;
    int prev_speed = 1;

    int matrix[SIZE_Y][SIZE_X] = {0};
    int matrix_next[SIZE_Y][SIZE_X] = {0};

    if (argc == 2 && input(matrix, argv[1])) {
        timeout(BASE_SPEED);
        char command = 0;

        while (command != 'q') {
            command = getch();
            speed = command - 48;  // считывает скорость 1-9
            if (speed > 0 && speed < 10) prev_speed = speed;
            if (speed <= 0) speed = prev_speed;

            run_game(matrix, matrix_next, speed);
        }
    }

    endwin();
    return 0;
}

int run_game(int matrix[SIZE_Y][SIZE_X], int matrix_next[SIZE_Y][SIZE_X], int speed) {
    timeout(BASE_SPEED / speed);
    clear();
    draw(matrix, speed);
    logic(matrix, matrix_next);
    for (int y = 0; y < SIZE_Y; y++)
        for (int x = 0; x < SIZE_X; x++) matrix[y][x] = matrix_next[y][x];

    return 1;
}

int input(int matrix[SIZE_Y][SIZE_X], const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return 0;
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
    return 1;
}

void draw(int matrix[SIZE_Y][SIZE_X], int speed) {
    int sum_around = 0;
    printw("\nSpeed(from 1 to 9): %d\n", speed);

    printw(" ");
    for (int i = 0; i < SIZE_X * 2; i++) printw("-");
    printw("\n");
    for (int y = 0; y < SIZE_Y; y++) {
        printw("|");
        for (int x = 0; x < SIZE_X; x++) {
            sum_around = count_neighbors(y, x, matrix);
            if (matrix[y][x]) {
                int color_pair;
                if (sum_around < 2)
                    color_pair = 4;  // Меньше 2 соседей
                else if (sum_around == 2 || sum_around == 3)
                    color_pair = 5;  // 2 или 3 соседа
                else
                    color_pair = 6;  // Больше 3 соседей

                attron(COLOR_PAIR(color_pair));
                printw(CELL);
                attroff(COLOR_PAIR(color_pair));
            } else {
                printw("  ");
            }
        }
        printw("|\n");
    }

    printw(" ");
    for (int i = 0; i < SIZE_X * 2; i++) printw("-");
    printw("\n");
    printw("PRESS Q TO EXIT");
}

void logic(int matrix[SIZE_Y][SIZE_X], int matrix_next[SIZE_Y][SIZE_X]) {
    int sum_around = 0;
    for (int y = 0; y < SIZE_Y; y++) {
        for (int x = 0; x < SIZE_X; x++) {
            sum_around = count_neighbors(y, x, matrix);
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

int count_neighbors(int y, int x, int matrix[SIZE_Y][SIZE_X]) {
    int sum_around = 0;
    sum_around += matrix[(SIZE_Y + y + 1) % SIZE_Y][(SIZE_X + x) % SIZE_X];
    sum_around += matrix[(SIZE_Y + y + 1) % SIZE_Y][(SIZE_X + x + 1) % SIZE_X];
    sum_around += matrix[(SIZE_Y + y) % SIZE_Y][(SIZE_X + x + 1) % SIZE_X];
    sum_around += matrix[(SIZE_Y + y - 1) % SIZE_Y][(SIZE_X + x + 1) % SIZE_X];
    sum_around += matrix[(SIZE_Y + y - 1) % SIZE_Y][(SIZE_X + x) % SIZE_X];
    sum_around += matrix[(SIZE_Y + y - 1) % SIZE_Y][(SIZE_X + x - 1) % SIZE_X];
    sum_around += matrix[(SIZE_Y + y) % SIZE_Y][(SIZE_X + x - 1) % SIZE_X];
    sum_around += matrix[(SIZE_Y + y + 1) % SIZE_Y][(SIZE_X + x - 1) % SIZE_X];
    return sum_around;
}