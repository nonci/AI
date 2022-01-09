/* Simple implementation of the Toeplitz transformation.
 * Subject to the "GNU General Public License v3.0". */

#include <stdio.h>
#include <stdlib.h>
#define fill(S,X,Y) (S.x=X, S.y=Y, S)
#define DATA {\
    00, 01, 02, 03, 04, 05,\
    10, 11, 12, 13, 14, 15,\
    20, 21, 22, 23, 24, 25,\
    30, 31, 32, 33, 34, 35,\
    40, 41, 42, 43, 44, 45,\
    50, 51, 52, 53, 54, 55 \
}

typedef struct {__uint16_t x:16; __uint16_t y:16; } size2d;

__uint16_t * toep(__uint16_t data[], size2d mat_size, size2d win_size, size2d* new_size) {
    new_size->y = (mat_size.y-win_size.y+1)*(mat_size.x-win_size.x+1),
    new_size->x = (win_size.x*win_size.y);
    long int c=0;
    __uint16_t * new_mat = malloc(new_size->x * new_size->y * sizeof(__uint16_t));
    
    for (int wj=0; wj<=mat_size.y-win_size.y; wj++)
        for (int wi=0; wi<=mat_size.x-win_size.x; wi++)
            for (int j=0; j<win_size.y; j++)
                for (int i=0; i<win_size.x; i++)
                    new_mat[c++] = data[wi + wj*mat_size.x + j*mat_size.x + i];
    return new_mat;
}

void print_mat(__uint16_t* data, size2d* size) {
    for (int j=0; j<size->y; j++, putchar('\n'))
        for (int i=0; i<size->x; i++)
            printf("%2d ", (int)data[i+j*size->x]);
}

int main(int n, char ** argv) {
    __uint16_t data[] = DATA;
    size2d mat_size, win_size, new_size;
    
    __uint16_t * tm = toep(data, fill(mat_size, 6,6), fill(win_size, 3,3), &new_size);
    print_mat(tm, &new_size);
    
    free(tm);
    return 0;
}
