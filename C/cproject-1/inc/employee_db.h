#ifndef EMPLOYEE_DB_H
#define EMPLOYEE_DB_H

#include <stdio.h>

typedef struct {
    char id[10];
    char first_name[20];
    char last_name[20];
    char email[30];
    char hire_date[15];
    char job_id[15];
    char salary[10];
} Employee;

int load_employees(FILE *fp, Employee **list);
void write_all_employees(FILE *fp, Employee *list, int count);
void update_employee(Employee *list, int count);
void print_employee_by_id(Employee *list, int count, const char *id);
void print_all_employees(Employee *list, int count);
int add_employee(Employee **list, int *count);
void free_employee_list(Employee *list);

#endif
