#include <stdio.h>
#include <stdlib.h>

struct XY { int x; int y; };
int get_input(int *n, int *m);
void turn(struct XY *dir);
char **matrix_mem_alloc(int height, int width);
void matrix_init(char **matrix, int n, int m);
void matrix_spiral(char **matrix, int n, int m);
void matrix_print(char **matrix, int n, int m);


int main() {
    int res = 1;
    int n = 0;
    int m = 0;
    char **matrix = NULL;
    if (!get_input(&n, &m)) {
        res = 0;
    }
    if (res) {
        matrix = matrix_mem_alloc(n, m);
        if (!matrix) {
            res = 0;
        }    
    } 
    if (res) {
        matrix_init(matrix, n, m);
        matrix_spiral(matrix, n, m);
        matrix_print(matrix, n, m);
        if (matrix) {
            free(matrix); 
            matrix = NULL;
        }
    } else {
        printf("ERROR");
    }
    return 0;
}


int get_input(int *n, int *m) {
    int res = 1;
    if (scanf("%d %d", n, m) != 2) {
        res = 0;
    }
    if (res) {
        if (*n < 1 || *m < 1) {
            res  = 0;
        }
    }
    return res;
}

void turn(struct XY *dir) {
    if (dir->x == 0 && dir->y == 1) {
        dir->x = 1;
        dir->y = 0;
    }
    else if (dir->x == 1 && dir->y == 0) {
        dir->x = 0; 
        dir->y = -1;
    }
    else if (dir->x == 0 && dir->y == -1) {
        dir->x = -1;
        dir->y = 0;
    } else {
        dir->x = 0;
        dir->y = 1;
    }
}

char **matrix_mem_alloc(int height, int width) {
    int sz = height * width * sizeof(char) + height * sizeof(char *);
    char **matrix = (char **)malloc(sz);
    char *ptr = (char *)(matrix + height);
    for (int i = 0; i < height; ++i) {
        matrix[i] = ptr + width * i;
    }
    return matrix;
}

void matrix_init(char **matrix, int n, int m) {
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            matrix[x][y] = 0;
        }
    }
}

void matrix_spiral(char **matrix, int n, int m) {
    struct XY dir = {0, 1};
    for (int x = 0, y = 0, cnt = 1; cnt <= n*m; ++cnt) {
        matrix[x][y] = cnt;
        int next_x = x + dir.x;
        int next_y = y + dir.y;
        if (next_x >= n || next_x < 0 || next_y >= m 
            || next_y < 0 || matrix[next_x][next_y] != 0) {
            turn(&dir);
        }
        x += dir.x;
        y += dir.y;
    }
}

void matrix_print(char **matrix, int n, int m) {
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (y == m - 1) {
                printf("%d", matrix[x][y]);
            } else {
                printf("%d ", matrix[x][y]);
            }
        }
        printf("\n");
    }   
}
