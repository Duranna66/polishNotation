//
// Created by Wull Harm on 09.07.2023.
//
#include "print.h"
int **createGrid() {
    int **grid = calloc(HEIGHT, sizeof(int *));
    for (int i = 0; i < HEIGHT; i++) {
        grid[i] = calloc(WIDTH, sizeof(int));
    }
    return grid;
}

// На основе данных из матрицы отрисовываем поле
void showGrid(int **grid) {
    for (int rows = 0; rows < HEIGHT; rows++) {
        for (int cols = 0; cols < WIDTH; cols++) {
            char value = (grid[rows][cols]) ? '*' : '.';
            printf("%c", value);
        }
        if (rows != HEIGHT - 1) {
            printf("\n");
        }
    }
}