#include <assert.h>
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

    /* while (node) */
    /* { */
    /*     data = node->data; */
    /*     print_student_detail(data); */
    /*     node = node->right; */
    /* } */

    ITERATIVE_LIST_BEGIN(student_db, node) {
        data = node->data;
        print_student_detail(data);
    } ITERATIVE_LIST_END
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

//Callback search function implementation
int match_student_rec_by_key(void const *data, void const *key)
{
    int rollno = *(int *)key;

    if (((student_t *)data)->rollno == rollno)
        return 0;

    return -1;
}

int match_employee_rec_by_key(void const *data, void const *key)
{
    int emp_id = *(int *)key;

    if (((employee_t *)data)->emp_id == emp_id)
        return 0;

    return -1;
}

//Callback comparison function implementation
int compare_student_record(void const *stud1, void const *stud2)
{
    student_t *student1 = (student_t *)stud1;
    student_t *student2 = (student_t *)stud2;

    if (student1->rollno > student2->rollno)
        return 1;
    else if (student1->rollno < student2->rollno)
        return -1;
    else if (student1->age > student2->age)
        return 1;
    else if (strncmp(student1->name, student2->name, 31) > 0)
        return 1;
    else if (strncmp(student1->name, student2->name, 31) < 0)
        return -1;
    else if (student1->weight > student2->weight)
        return 1;
    else if (student1->weight < student2->weight)
        return -1;

    assert(0);
}

int compare_employee_record(void const *empl1, void const *empl2)
{
    employee_t *employee1 = (employee_t *)empl1;
    employee_t *employee2 = (employee_t *)empl2;

    if (employee1->emp_id > employee2->emp_id)
        return 1;
    else if (employee1->emp_id < employee2->emp_id)
        return -1;
    else if (strncmp(employee1->name, employee2->name, 31) > 0)
        return 1;
    else if (strncmp(employee1->name, employee2->name, 31) < 0)
        return -1;
    else if (strncmp(employee1->designation, employee2->designation, 31) > 0)
        return 1;
    else if (strncmp(employee1->designation, employee2->designation, 31) < 0)
        return -1;
    else if (employee1->salary > employee2->salary)
        return 1;
    else if (employee1->salary < employee2->salary)
        return -1;

    assert(0);
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

    callback_compare_registration(student_db, compare_student_record);

    dll_priority_add_new(student_db, (void *)student1);
    dll_priority_add_new(student_db, (void *)student2);
    dll_priority_add_new(student_db, (void *)student3);

    print_student_db(student_db);
    /* add_data_to_dll(student_db, student1); */
    /* add_data_to_dll(student_db, student2); */
    /* add_data_to_dll(student_db, student3); */

    /* /1* student_t *student = search_student_by_rollno(student_db, 800400); *1/ */

    /* callback_search_registration(student_db, match_student_rec_by_key); */
    /* int rollno = 800000; */
    /* student_t *student = (student_t *)dll_search_by_key(student_db, (void *)&rollno); */ 

    /* if(!student){ */
    /*     printf("Student record not found\n"); */
    /* } */
    /* else{ */
    /*     print_student_detail(student); */
    /* } */

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

