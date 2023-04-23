#include <stdbool.h>
#include <stdio.h>
#include <math.h>

int N = 16;

bool is_safe(int *, int, int, int);
int solve_sudoku(int *, int, int);
void print_sudoku(int *);
void read_puzzle(int *);
void write_puzzle(int *);

int main(){
    int board[N * N];
    read_puzzle(board);
    solve_sudoku(board, 0, 0);
    write_puzzle(board);
}

bool is_safe(int *grid, int row, int col, int num){
    for (int i = 0; i <= (N - 1); i++) {
        if (grid[N * row + i] == num) {
            return false;
        }
    }
    for (int i = 0; i <= (N - 1); i++) {
        if (grid[N * i + col] == num) {
            return false;
        }
    }

    int a, b, mini_grid = (int) sqrt(N);
    a = row / mini_grid;
    b = col / mini_grid;

    for (int i = 0; i < mini_grid; i++) {
        for(int j = 0; j < mini_grid; j++){
            if (grid[ ((a * mini_grid) + i) * N + ((b * mini_grid) + j) ] == num) {
                return false;
            }
        }
    }
    
    return true;
}

int solve_sudoku(int *grid, int row, int col){
    if (row == (N - 1) && col == N){
        return 1;
    }

    if (col == N){
        row++;
        col = 0;
    }

    if (grid[(row * N) + col] > 0) {
        return solve_sudoku(grid, row, col + 1);
    }

    for (int num = 1; num <= N; num++) {
        //print_sudoku(grid);
        if (is_safe(grid, row, col, num) == true) {
            grid[(row * N) + col] = num;
            if (solve_sudoku(grid, row, col + 1) == true) {
                return 1;
            }
        }
        grid[row * N + col] = 0;
    }
    return 0;
}

void print_sudoku(int *grid) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(" %d ", grid[i * N + j]);
        }
        printf("\n");
    }
}

void read_puzzle(int *grid) {
    FILE *sudoku;
    int num = 0;

    sudoku = fopen("sudoku.txt", "r");

    if (NULL == sudoku) {
        printf("the file can't be oppened \n");
    }

    while (!feof (sudoku)) {
        fscanf(sudoku, "%d", &grid[num]);
        num++;
        if (num >= N * N) {
            break;
        }
    }
}

void write_puzzle(int *grid) {
    FILE *sudoku;

    sudoku = fopen("solved.txt", "w");

    if (NULL == sudoku) {
        printf("the solved can't be oppened \n");
    }

    for (int i = 0; i < (N * N); i++) {
        fprintf(sudoku, " %d ", grid[i]);
        if ((i + 1) % N == 0 && i > 0) {
            fprintf(sudoku, "\n");
        }
    }
}