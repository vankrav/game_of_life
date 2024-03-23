#include <stdio.h>  
#include <stdlib.h> 

#define SIZE_X 80  
#define SIZE_Y 25  

/*-------------МАТРИЦЫ-------------*/

int** create_matrix(int col, int row);
/*-------------ОТРИСОВКА-------------*/

void draw(int** matrix, int col, int row);  // Прототип функции отрисовки игрового поля
void draw_zero(int** matrix, int col, int row);
/*---------ОТРИСОВКА В ПОЛЕ---------*/

int input_int(int* c);
int** input(int** matrix);


/*---------ЛОГИКА---------*/

int** logic(int** matrix, int col, int row);

/*------------------------------------MAIN------------------------------------*/

int run_game(int** matrix);

int main() {

    int** matrix = create_matrix(SIZE_Y, SIZE_X);
    matrix = input(matrix);
char c = 0;

    // draw_zero(matrix, SIZE_Y, SIZE_X);
    while(scanf("%c", &c))
    run_game(matrix);
    return 0;  // Возвращение 0 при успешном завершении программы
}


int run_game(int** matrix) {
    
   
        draw(matrix, SIZE_Y, SIZE_X);
        matrix = logic(matrix, SIZE_Y, SIZE_X);
        

    
    return 1;
}

/*------------------------------------LOGIC------------------------------------*/

int** logic(int** matrix, int col, int row) {
    int** matrix_next = create_matrix(SIZE_Y, SIZE_X);
    int sum_around = 0;
     for (int y = 0; y < SIZE_Y; y++){                              
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
            if(matrix[y][x]) {
                if(sum_around == 2 || sum_around == 3) matrix_next[y][x] = 1;
                else matrix_next[y][x] = 0;
            }
            else {
                if(sum_around == 3) matrix_next[y][x] = 1;
                else matrix_next[y][x] = 0;
            }
            
        }
     }
    return matrix_next;
}

/*------------------------------------DRAW------------------------------------*/



/*------------------------------------МАТРИЦЫ------------------------------------*/

int** create_matrix(int m, int n) {
    int** matrix = malloc(m * n * sizeof(int) + m * sizeof(int*));
    int* ptr = (int*)(matrix + m);

    for (int i = 0; i < m; i++) matrix[i] = ptr + n * i;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) matrix[i][j] = 0;

    return matrix;
}


void draw(int** matrix, int col, int row) {
    printf("\n\n");

    printf(" ");
    for (int i = 0; i < SIZE_X; i++) printf("⎯");
    printf("\n");        
    for (int y = 0; y < SIZE_Y; y++) {       
        printf("|");                       
        for (int x = 0; x < SIZE_X; x++) {   
            if(matrix[y][x])
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


void draw_zero(int** matrix, int col, int row) {
          
    for (int y = 0; y < SIZE_Y; y++) {                              
        for (int x = 0; x < SIZE_X; x++) {   
                printf("0");
        }
        printf("\n"); 
    }
                          
}
int** input(int** matrix) {
    int n = 0;
    for (int y = 0; y < SIZE_Y; y++) {                              
        for (int x = 0; x < SIZE_X; x++) {  
            if (input_int(&n))
                matrix[y][x] = n;
            
        }
    }

    return matrix;
}


int input_int(int* c) {
    int valid = 1;
    char ch = 0;
    if (scanf("%d%c", c, &ch) == 2 && (ch == '\n' || ch == ' ')) {
        valid = 1;
    } else
        valid = 0;
    return valid;
}
