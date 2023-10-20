#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "print.h"
#include "rpn.h"

void init();
int **createGrid();
void showGrid(int **grid);
void destroyGrid(int **grid);

int updateGrid(int **grid, int x, int y);

int main() {
    // printf("HEIGHT = %d, WIDTH = %d, X = %d, Y = %d, XMAX = %d, XMIN = %d, YMAX = %d, YMIN = %d\n", HEIGHT,
    //    WIDTH, X, Y, XMAX, XMIN, YMAX, YMIN);
    init();
    return 0;
}

// Отрисовывем одну точку в матрице (меняем 0 на 1)
int updateGrid(int **grid, int x, int y) {
    int result = 1;
    if (x > XMAX || x < XMIN || y > YMAX || y < YMIN) {
        result = -1;
    } else if (y <= 10 && y >= -10) {
        grid[Y + y][X + x] = 1;
    }
    return result;
}

// Инициализация программы
void init() {
    int **grid = createGrid();

    // Функция построения графика
    struct list *token = getToken();
    struct list *prn = getPRN(token);
    for (float x = 0; x <= 4 * PI; x += 0.1) {
        float y;
        y = f(prn, x);
        // TODO: replace rintf
        updateGrid(grid, rintf(x * 7), rintf(y * 10));
        // print x/y
        // printf("x = %.2f,\ty = %.2f\n", x, y);
    }

    showGrid(grid);
    destroyGrid(grid);
    listDestroy(prn);
}

// Выделяем память под матрицу 80x25 и зануляем ее

// Очищаем память, выделенную под матрицу
void destroyGrid(int **grid) {
    for (int i = 0; i < HEIGHT; i++) {
        free(grid[i]);
    }
    free(grid);
}
