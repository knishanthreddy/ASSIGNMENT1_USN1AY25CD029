#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FULL_TIME,
    CONTRACT
} EmployeeType;

typedef struct {
    char name[20];
    int emp_id;
    EmployeeType type;

    union {
        float salary;
        struct {
            float hourly_rate;
            int hours_worked;
        } contract_info;
    } pay;

} Employee;

int main(void) {
    Employee *e = NULL;
    int n, i;
    float total_bill = 0.0f;

    // a. Dynamically allocate an array of Employee based on n
    printf("Enter number of employees: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }

    e = (Employee *)malloc(n * sizeof(Employee));
    if (e == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // b. Read data and load union fields based on employee type
    for (i = 0; i < n; i++) {
        int temp_type;

        printf("\n--- Employee %d ---\n", i + 1);
        printf("Enter employee name: ");
        scanf("%19s", (e + i)->name);

        printf("Enter employee ID: ");
        scanf("%d", &(e + i)->emp_id);

        printf("Enter type (0 = Full-time, 1 = Contract): ");
        scanf("%d", &temp_type);

        if (temp_type == 0) {
            (e + i)->type = FULL_TIME;
            printf("Enter monthly salary: ");
            scanf("%f", &(e + i)->pay.salary);
        } else if (temp_type == 1) {
            (e + i)->type = CONTRACT;
            printf("Enter hourly rate: ");
            scanf("%f", &(e + i)->pay.contract_info.hourly_rate);
            printf("Enter hours worked: ");
            scanf("%d", &(e + i)->pay.contract_info.hours_worked);
        } else {
            printf("Invalid employee type entered.\n");
            free(e);
            return 1;
        }
    }

    // c. Print payslips and calculate total pay per employee
    printf("\n================ EMPLOYEE PAYSLIPS ================\n");

    for (i = 0; i < n; i++) {
        float amount = 0.0f;

        printf("\nEmployee ID : %d\n", (e + i)->emp_id);
        printf("Name        : %s\n", (e + i)->name);

        if ((e + i)->type == FULL_TIME) {
            amount = (e + i)->pay.salary;
            printf("Type        : Full-Time\n");
            printf("Base Salary : %.2f\n", (e + i)->pay.salary);
        } else {
            amount = (e + i)->pay.contract_info.hourly_rate * 
                     (e + i)->pay.contract_info.hours_worked;
            printf("Type        : Contract\n");
            printf("Hourly Rate : %.2f\n", (e + i)->pay.contract_info.hourly_rate);
            printf("Hours Worked: %d\n", (e + i)->pay.contract_info.hours_worked);
        }

        printf("Total Pay   : %.2f\n", amount);
        total_bill += amount;
    }

    // d. Print company's total salary bill and free heap memory
    printf("===================================================\n");
    printf("Total Salary Bill of Company: %.2f\n", total_bill);
    printf("===================================================\n");

    free(e);
    e = NULL;

    return 0;
}
