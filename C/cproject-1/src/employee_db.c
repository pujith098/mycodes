#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "employee_db.h"

int load_employees(FILE *fp, Employee **list) {
    char line[200];
    int count = 0;
    Employee *temp = NULL;

    rewind(fp);
    fgets(line, sizeof(line), fp); // Skip header line

    while (fgets(line, sizeof(line), fp)) {
        temp = realloc(*list, sizeof(Employee) * (count + 1));
        if (!temp) {
            perror("realloc failed");
            free(*list);
            *list = NULL;
            return -1;
        }
        *list = temp;
        memset(&(*list)[count], 0, sizeof(Employee));

        char *token;
        int field_index = 0;

        token = strtok(line, ",\n");
        while (token != NULL && field_index < 7) {
            switch (field_index) {
                case 0:
                    strncpy((*list)[count].id, token, sizeof((*list)[count].id) - 1);
                    break;
                case 1:
                    strncpy((*list)[count].first_name, token, sizeof((*list)[count].first_name) - 1);
                    break;
                case 2:
                    strncpy((*list)[count].last_name, token, sizeof((*list)[count].last_name) - 1);
                    break;
                case 3:
                    strncpy((*list)[count].email, token, sizeof((*list)[count].email) - 1);
                    break;
                case 4:
                    strncpy((*list)[count].hire_date, token, sizeof((*list)[count].hire_date) - 1);
                    break;
                case 5:
                    strncpy((*list)[count].job_id, token, sizeof((*list)[count].job_id) - 1);
                    break;
                case 6:
                    strncpy((*list)[count].salary, token, sizeof((*list)[count].salary) - 1);
                    break;
            }
            field_index++;
            token = strtok(NULL, ",\n");
        }

        if (field_index != 7) {
            fprintf(stderr, "Skipping bad line at record %d: %s", count + 2, line);
            continue;
        }

        count++;
    }

    return count;
}

void write_all_employees(FILE *fp, Employee *list, int count) {
    rewind(fp);
    fprintf(fp, "EMPLOYEE_ID,FIRST_NAME,LAST_NAME,EMAIL,HIRE_DATE,JOB_ID,SALARY\n");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n",
                list[i].id, list[i].first_name, list[i].last_name,
                list[i].email, list[i].hire_date, list[i].job_id, list[i].salary);
    }
    fflush(fp);
    ftruncate(fileno(fp), ftell(fp));
}

void update_employee(Employee *list, int count) {
    char id[10], new_value[30];
    int choice;

    printf("Enter ID to update: ");
    scanf("%s", id);

    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].id, id) == 0) {
            printf("Employee found:\n1.First Name: %s\n2.Last Name: %s\n3.Email: %s\n"
                   "4.Hire Date: %s\n5.Job ID: %s\n6.Salary: %s\n",
                   list[i].first_name, list[i].last_name, list[i].email,
                   list[i].hire_date, list[i].job_id, list[i].salary);

            printf("Which field to update (1–6): ");
            scanf("%d", &choice);
            getchar();

            printf("Enter new value: ");
            scanf("%s", new_value);

            switch (choice) {
                case 1: strcpy(list[i].first_name, new_value); break;
                case 2: strcpy(list[i].last_name, new_value); break;
                case 3: strcpy(list[i].email, new_value); break;
                case 4: strcpy(list[i].hire_date, new_value); break;
                case 5: strcpy(list[i].job_id, new_value); break;
                case 6: strcpy(list[i].salary, new_value); break;
                default: printf("Invalid option\n"); return;
            }

            printf("Updated successfully.\n");
            return;
        }
    }

    printf("Employee ID not found.\n");
}

void print_employee_by_id(Employee *list, int count, const char *id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].id, id) == 0) {
            printf("ID: %s\nFirst Name: %s\nLast Name: %s\nEmail: %s\nHire Date: %s\nJob ID: %s\nSalary: %s\n",
                   list[i].id, list[i].first_name, list[i].last_name,
                   list[i].email, list[i].hire_date, list[i].job_id, list[i].salary);
            return;
        }
    }
    printf("Employee with ID %s not found.\n", id);
}

void print_all_employees(Employee *list, int count) {
    printf("\nAll Employees:\n");
    for (int i = 0; i < count; i++) {
        printf("%s, %s, %s, %s, %s, %s, %s\n",
               list[i].id, list[i].first_name, list[i].last_name,
               list[i].email, list[i].hire_date, list[i].job_id, list[i].salary);
    }
}

int add_employee(Employee **list, int *count) {
    Employee new_emp;
    printf("Enter new employee details:\n");

    printf("ID: "); scanf("%s", new_emp.id);
    printf("First Name: "); scanf("%s", new_emp.first_name);
    printf("Last Name: "); scanf("%s", new_emp.last_name);
    printf("Email: "); scanf("%s", new_emp.email);
    printf("Hire Date: "); scanf("%s", new_emp.hire_date);
    printf("Job ID: "); scanf("%s", new_emp.job_id);
    printf("Salary: "); scanf("%s", new_emp.salary);

    for (int i = 0; i < *count; i++) {
        if (strcmp((*list)[i].id, new_emp.id) == 0) {
            printf("Employee ID already exists.\n");
            return 0;
        }
    }

    Employee *temp = realloc(*list, sizeof(Employee) * (*count + 1));
    if (!temp) {
        perror("Failed to allocate memory for new employee");
        return 0;
    }

    *list = temp;
    (*list)[*count] = new_emp;
    (*count)++;

    printf("New employee added.\n");
    return 1;
}

void free_employee_list(Employee *list) {
    free(list);
}
