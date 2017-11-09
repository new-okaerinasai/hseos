#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

typedef struct Figure
{
    int iter_count, row, col, incr;
    int** lul;
} Figure;

int cols, rows, thrs;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* thread_fig(void* what) {
    pthread_mutex_lock(&m);
    Figure now = *(Figure*)what;
    int** lul = now.lul;
    if (now.col == -1) {
        for (int i = 0; i != now.iter_count; ++i) {
            for (int j = 0; j != cols; ++j) {
                lul[now.row][j] += now.incr;
            }
        }
    } else if (now.row == -1) {
        for (int i = 0; i != now.iter_count; ++i) {
            for (int j = 0; j != rows; ++j) {
                //pthread_mutex_lock(&m);
                lul[j][now.col] += now.incr;
                //pthread_mutex_unlock(&m);
            }
        }
    }
    pthread_mutex_unlock(&m);
    return NULL;
}

int main() {
    scanf("%d%d%d", &rows, &cols, &thrs);
    int** m = (int**)calloc(rows, sizeof(*m));
    for (int i = 0; i != rows; ++i) {
        m[i] = calloc(cols, sizeof(*(m[i])));
    }
    pthread_t all[thrs];
    for (int i = 0; i != thrs; ++i) {
        int iter_count, row, col, incr;
        scanf("%d%d%d%d", &iter_count, &row, &col, &incr);
        Figure tmp;
        tmp.row = row;
        tmp.col = col;
        tmp.iter_count = iter_count;
        tmp.incr = incr;
        tmp.lul = m;
        pthread_create(&all[i], NULL, thread_fig, (void*)&tmp);
    }
    for (int i = 0; i != thrs; ++i) {
        pthread_join(all[i], NULL);
    }
    for (int i = 0; i != rows; ++i) {
        for (int j = 0; j != cols; ++j) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i != rows; ++i) {
        free(m[i]);
    }
    free(m);
}