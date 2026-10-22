#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int roll_no;
    char name[20];
    float marks;
} Student;

int main(void) {
    Student *ptr = NULL;
    Student *temp = NULL;
    int n, i;
    char choice;

    // a. Ask user for n and allocate memory using malloc
    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    ptr = (Student *)malloc(n * sizeof(Student));
    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // b. Read initial n records from the user using pointer arithmetic
    for (i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Roll No: ");
        scanf("%d", &(ptr + i)->roll_no);
        printf("Name: ");
        scanf("%19s", (ptr + i)->name);
        printf("Marks: ");
        scanf("%f", &(ptr + i)->marks);
    }

    do {
        // c. Traverse with pointer arithmetic to calculate average and find topper
        float sum = 0.0f;
        int top_index = 0;

        for (i = 0; i < n; i++) {
            sum += (ptr + i)->marks;

            if ((ptr + i)->marks > (ptr + top_index)->marks) {
                top_index = i;
            }
        }

        printf("\n------------- Results -------------\n");
        printf("Average Marks : %.2f\n", sum / n);
        printf("Highest Scorer: %s (Roll No: %d, Marks: %.2f)\n",
               (ptr + top_index)->name,
               (ptr + top_index)->roll_no,
               (ptr + top_index)->marks);
        printf("-----------------------------------\n");

        // e. Ask to add 2 more students and dynamically grow with realloc
        printf("\nAdd 2 more students? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            temp = (Student *)realloc(ptr, (n + 2) * sizeof(Student));

            if (temp == NULL) {
                printf("Memory reallocation failed.\n");
                free(ptr);
                return 1;
            }

            ptr = temp;

            // Read the 2 new records
            for (i = n; i < n + 2; i++) {
                printf("\nEnter details for student %d:\n", i + 1);
                printf("Roll No: ");
                scanf("%d", &(ptr + i)->roll_no);
                printf("Name: ");
                scanf("%19s", (ptr + i)->name);
                printf("Marks: ");
                scanf("%f", &(ptr + i)->marks);
            }

            n += 2;
        }

    } while (choice == 'y' || choice == 'Y');

    // d. Free allocated memory before exit
    free(ptr);
    ptr = NULL;

    return 0;
}

