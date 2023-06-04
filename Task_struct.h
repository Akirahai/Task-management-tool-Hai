#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define STD_STRING_SIZE 30
#define STD_TASKS_COUNT 100


/* Structure and Interface(s) to handle date */
struct date {
    int day;
    int month;
    int year;
};
typedef struct date Date;

Date* initialize_date(int day, int month, int year) {
    Date *container = (Date*)malloc(sizeof(Date));
    container->day = day;
    container->month = month;
    container->year = year;
    return container;
}


Date* get_current_local_date() {
    time_t periodic_time = time(NULL);
    struct tm* formatted_time = localtime(&periodic_time);

    Date *local_date = initialize_date(
        formatted_time->tm_mday,
        // the time structure stores months from the range 0-11
        1 + formatted_time->tm_mon,
        // the time structure stores years since 1900!
        1900 + formatted_time->tm_year 
    );
    printf("%d", local_date->day);
    return local_date;
}

int compare_dates(Date *d1, Date *d2) {
    if (d1->year != d2->year) {
        return d1->year - d2->year;
    } else if (d1->month != d2->month) {
        return d1->month - d2->month;
    } else {
        return d1->day - d2->day;
    }
}

/* ---------- */

/* Structure and Interface(s) to handle task(s) */

struct task {
    int priority;
    char text[STD_STRING_SIZE];   
    Date deadline;
};
typedef struct task Task;

Task* initialize_task(const char *text, int priority, Date *d) {
    Task *new_task = (Task*)malloc(sizeof(Task));
    strcpy(new_task->text, text);
    new_task->priority = priority;
    new_task->deadline = *d; 
    return new_task;
}

// Declarations
char* get_printable_task(Task*);
char* get_printable_complete_task(Task *task);
Task** read_all_tasks_from_file(const char*, int*);


Task** read_all_tasks_from_file(const char *filepath, int *num_tasks) {
    Task **tasks = (Task**)malloc(sizeof(Task*)*STD_TASKS_COUNT);
    *num_tasks = 0;
    // Read from file
    FILE *fp;
    char line[STD_TASKS_COUNT];
    char status[20];
    char pr[10];
    char text[50];
    char deadline[20];
    int priority,day,month,year;
    // Open the file in read mode
    fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("Error: could not open file\n");
        return NULL;
    }

    // Read the file line by line
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Extract the priority, task, and deadline information from the line
        sscanf(line, "[%[^]]] Priority %[^:]: \"%[^\"]\" - Deadline: %[^\n]", 
            status, pr, text, deadline);
        sscanf(pr, "%d", &priority);
        sscanf(deadline, "%d/%d/%d", &day, &month, &year);

        tasks[*num_tasks] = initialize_task(text,priority,initialize_date(day,month,year));
        (*num_tasks)++;
    }
    
    fclose(fp);

    if(*num_tasks == 0) {
        free(tasks);
        return NULL;
    }
    tasks = (Task**)realloc(tasks, sizeof(Task*)*(*num_tasks));
    return tasks;
}



// Get information from task_struct as incomplete task
char* get_printable_task(Task *task) {
    // Calculate the required size for the task string
    int size = snprintf(NULL, 0, "[ ] Priority %d: \"%s\" - Deadline: %d/%d/%d\n",
                        task->priority, task->text, task->deadline.day,
                        task->deadline.month, task->deadline.year) + 1;

    // Allocate memory for the task string
    char *task_str = malloc(size);

    // Write the task string to the buffer
    snprintf(task_str, size, "[ ] Priority %d: \"%s\" - Deadline: %d/%d/%d\n",
             task->priority, task->text, task->deadline.day,
             task->deadline.month, task->deadline.year);

    return task_str;
}

// Get information from task_struct as complete task
char* get_printable_complete_task(Task *task) {
    // Calculate the required size for the task string
    int size = snprintf(NULL, 0, "[X] Priority %d: \"%s\" - Deadline: %d/%d/%d\n",
                        task->priority, task->text, task->deadline.day,
                        task->deadline.month, task->deadline.year) + 1;

    // Allocate memory for the task string
    char *task_str = malloc(size);

    // Write the task string to the buffer
    snprintf(task_str, size, "[X] Priority %d: \"%s\" - Deadline: %d/%d/%d\n",
             task->priority, task->text, task->deadline.day,
             task->deadline.month, task->deadline.year);

    return task_str;
}
