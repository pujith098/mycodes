#include <stdio.h>
#include <stdlib.h>
#include "employee_db.h"

int main() {
    FILE *fp = fopen("../src/employees_1.csv", "r+");
    if (!fp) {
        perror("Failed to open employees_1.csv");
        return 1;
    }

    Employee *list = NULL;
    int count = load_employees(fp, &list);
    if (count < 0) {
    fprintf(stderr, "Failed to load employee data\n");
    fclose(fp);
    return 1;
}


    int choice;
    char id[10];

    do {
        printf("\n==== Employee DB ====\n");
        printf("1 - View all employees\n");
        printf("2 - Search by ID\n");
        printf("3 - Update employee\n");
        printf("4 - Add new employee\n");
        printf("5 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                print_all_employees(list, count);
                break;
            case 2:
                printf("Enter ID to search: ");
                scanf("%s", id);
                print_employee_by_id(list, count, id);
                break;
            case 3:
                update_employee(list, count);
                write_all_employees(fp, list, count);
                break;
            case 4:
                if (add_employee(&list, &count))
                    write_all_employees(fp, list, count);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 5);

    free_employee_list(list);
    fclose(fp);
    return 0;
}
