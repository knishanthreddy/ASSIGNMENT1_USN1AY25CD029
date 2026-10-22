
#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];  /* coef[i] = coefficient of x^(degree-i) */
} polynomial;

/* Function to add two polynomials */
polynomial add(polynomial a, polynomial b) {
    polynomial result;
    int i, exp;

    result.degree = (a.degree > b.degree) ? a.degree : b.degree;

    for (i = 0; i <= result.degree; i++) {
        exp = result.degree - i;

        float ca = 0, cb = 0;

        if (exp <= a.degree)
            ca = a.coef[a.degree - exp];

        if (exp <= b.degree)
            cb = b.coef[b.degree - exp];

        result.coef[i] = ca + cb;
    }

    return result;
}

/* Function to display a polynomial */
void display(polynomial p) {
    int i, exp, first = 1;
    float c;

    for (i = 0; i <= p.degree; i++) {
        c = p.coef[i];
        exp = p.degree - i;

        /* Skip zero coefficients */
        if (c == 0)
            continue;

        /* Print sign */
        if (!first) {
            if (c > 0)
                printf(" + ");
            else
                printf(" - ");
        } else if (c < 0) {
            printf("-");
        }

        /* Print absolute coefficient */
        if (c < 0)
            c = -c;

        /* Print coefficient and exponent */
        if (exp == 0) {
            printf("%g", c);
        } else {
            if (c != 1)
                printf("%g", c);

            printf("x");

            if (exp != 1)
                printf("^%d", exp);
        }

        first = 0;
    }

    if (first)
        printf("0");

    printf("\n");
}

int main() {
    polynomial a, b, sum;
    int i;

    printf("Enter degree of first polynomial: ");
    scanf("%d", &a.degree);

    printf("Enter coefficients from highest power to constant:\n");
    for (i = 0; i <= a.degree; i++)
        scanf("%f", &a.coef[i]);

    printf("Enter degree of second polynomial: ");
    scanf("%d", &b.degree);

    printf("Enter coefficients from highest power to constant:\n");
    for (i = 0; i <= b.degree; i++)
        scanf("%f", &b.coef[i]);

    sum = add(a, b);

    printf("First polynomial: ");
    display(a);

    printf("Second polynomial: ");
    display(b);

    printf("Sum: ");
    display(sum);

    return 0;
}

