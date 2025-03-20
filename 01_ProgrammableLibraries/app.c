#include <stdlib.h>
#include <stdio.h>
#include "dll.h"
#include <string.h>

//Define data structure
typedef struct student_
{
    char name[32];
    int age;
    int weight;
    unsigned int rollno;
} student_t;

typedef struct employee_
{
    char name[32];
    char designation[32];
    unsigned int salary;
    unsigned int emp_id;
} employee_t;

//Printf data detail
static void print_student_detail(student_t const *student)
{
    printf("Name: %s\n", student->name);
    printf("Age: %d\n", student->age);
    printf("Weight: %d\n", student->weight);
    printf("rollno: %u\n", student->rollno);

}

static void print_student_db(dll_t const *student_db)
{
    if (!student_db || !student_db->head)
        return;

    dll_node_t *node = student_db->head;
    student_t *data = NULL;

    while (node)
    {
        data = node->data;
        print_student_detail(data);
        node = node->right;
    }
}

static void print_employee_detail(employee_t const *employee)
{
    printf("Name: %s\n", employee->name);
    printf("Designation: %s\n", employee->designation);
    printf("Salary: %u\n", employee->salary);
    printf("emp_id: %u\n", employee->emp_id);
}

static void print_employee_db(dll_t const *employee_db)
{
    if (!employee_db || !employee_db->head)
        return;

    dll_node_t *node = employee_db->head;
    employee_t *data = NULL;

    while (node)
    {
        data = node->data;
        print_employee_detail(data);
        node = node->right;
    }
}

//Search function

student_t *
search_student_by_rollno(dll_t const *student_db, unsigned int const rollno)
{
    if (!student_db || !student_db->head)
        return NULL;

    dll_node_t *node = student_db->head;
    student_t *data = node->data;

    while (node)
    {
        data = node->data;
        if (data->rollno == rollno)
            return data;
        node = node->right;
    }

    return NULL;
}

employee_t *
search_employee_by_emp_id(dll_t const *employee_db, unsigned int const rollno)
{
    if (!employee_db || !employee_db->head)
        return NULL;

    dll_node_t *node = employee_db->head;
    employee_t *data = node->data;

    while (node)
    {
        data = node->data;
        if (data->emp_id == rollno)
            return data;
        node = node->right;
    }

    return NULL;
}

int 
main()
{
    //Student database
    student_t *student1 = calloc(1, sizeof(student_t));
    strncpy(student1->name, "Abhishek", sizeof student1->name);
    student1->age = 31;
    student1->weight = 75;
    student1->rollno = 800000;

    student_t *student2 = calloc(1, sizeof(student_t));
    strncpy(student2->name, "Joseph", sizeof student2->name);
    student2->age = 41;
    student2->weight = 70;
    student2->rollno = 800400;

    student_t *student3 = calloc(1, sizeof(student_t));
    strncpy(student3->name, "Jack", sizeof student3->name);
    student3->age = 29;
    student3->weight = 55;
    student3->rollno = 800400;

    dll_t *student_db = get_new_dll();
    add_data_to_dll(student_db, student1);
    add_data_to_dll(student_db, student2);
    add_data_to_dll(student_db, student3);

    student_t *student = search_student_by_rollno(student_db, 800400);
    if(!student){
        printf("Student record not found\n");
    }
    else{
        print_student_detail(student);
    }

    //Employee database
    employee_t *employee1 = calloc(1, sizeof(employee_t));
    strncpy(employee1->name, "Harsh", sizeof employee1->name);
    strncpy(employee1->designation, "Vice President", sizeof employee1->designation);
    employee1->salary = 11131;
    employee1->emp_id = 10000;

    employee_t *employee2 = calloc(1, sizeof(employee_t));
    strncpy(employee2->name, "Huma", sizeof employee2->name);
    strncpy(employee2->designation, "CEO", sizeof employee2->designation);
    employee1->salary = 127000;
    employee1->emp_id = 10001;

    employee_t *employee3 = calloc(1, sizeof(employee_t));
    strncpy(employee3->name, "Neena", sizeof employee3->name);
    strncpy(employee2->designation, "Manager", sizeof employee3->designation);
    employee1->salary = 139000;
    employee1->emp_id = 10002;

    dll_t *employee_db = get_new_dll();
    add_data_to_dll(employee_db, employee1);
    add_data_to_dll(employee_db, employee2);
    add_data_to_dll(employee_db, employee3);

    employee_t *employee = search_employee_by_emp_id(employee_db, 10002);
    if(!employee){
        printf("Student record not found\n");
    }
    else{
        print_employee_detail(employee);
    }



    return 0;
}

