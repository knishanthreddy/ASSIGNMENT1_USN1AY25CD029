
#include <stdio.h>

#define MAX 100

typedef struct {
    int row, col, value;
} term;

/* Fast transpose using counting and starting positions */
void fast_transpose(term a[], term b[]) {
    int row_terms[MAX] = {0};
    int starting_pos[MAX] = {0};
    int i, j, num_cols, num_terms;

    num_cols = a[0].col;
    num_terms = a[0].value;

    /* Header of the transposed matrix */
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    /* Step 1: Count terms in each column */
    for (i = 1; i <= num_terms; i++)
        row_terms[a[i].col]++;

    /* Step 2: Calculate starting positions */
    starting_pos[0] = 1;

    for (i = 1; i < num_cols; i++)
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];

    /* Print arrays for verification */
    printf("\nrow_terms[]:\n");
    for (i = 0; i < num_cols; i++)
        printf("%d ", row_terms[i]);

    printf("\nstarting_pos[]:\n");
    for (i = 0; i < num_cols; i++)
        printf("%d ", starting_pos[i]);

    printf("\n");

    /* Step 3: Place terms directly in their correct positions */
    for (i = 1; i <= num_terms; i++) {
        j = starting_pos[a[i].col]++;

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
    }
}

/* Display triples */
void display(term a[]) {
    int i;

    printf("Row\tColumn\tValue\n");

    for (i = 0; i <= a[0].value; i++)
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
}

int main() {
    term a[MAX], b[MAX];
    int matrix[MAX][MAX];
    int rows, cols, i, j, k = 1;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter matrix elements row by row:\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);

            if (matrix[i][j] != 0) {
                a[k].row = i;
                a[k].col = j;
                a[k].value = matrix[i][j];
                k++;
            }
        }
    }

    /* Header: rows, columns, non-zero terms */
    a[0].row = rows;
    a[0].col = cols;
    a[0].value = k - 1;

    printf("\nOriginal matrix triples:\n");
    display(a);

    fast_transpose(a, b);

    printf("\nTransposed matrix triples:\n");
    display(b);

    printf("\nThe transposed triples are in row-major order.\n");

    return 0;
}

