/* ---------- */
/*Declaration*/
void task_ls(); // print the list of tasks 
void task_ls_priority(); // print the list of tasks sorting in priority
void task_ls_deadline(); // print the list of tasks sorting in deadline
/* ---------- */

// print the list of tasks
void task_ls() {
    int num_tasks = 0;

    // Use read_all_tasks_from_file() to read the list of tasks from the file
    Task **task_list = read_all_tasks_from_file("task.txt", &num_tasks);
    if (task_list == NULL) {
        printf("\nNo tasks to do.");
        return;
    }

    printf("\nList of incomplete tasks in order of tasks_index you have added:\n");
    
    // display all contents by iterating using get_printable_task() 
    for (int i = 0; i < num_tasks; i++) {
        printf("%d. ", i+1);
        printf("%s", get_printable_task(*(task_list + i)));
    }
    printf("The number of incomplete tasks: %d\n",num_tasks);

    FILE *f = fopen("display.txt", "w");
    fprintf(f,"\nList of incomplete tasks in order of tasks_index you have added:\n");
    for (int i = 0; i < num_tasks; i++) {
        fprintf(f,"%d. ", i+1);
        fprintf(f, "%s", get_printable_task(*(task_list + i)));
    }
    fprintf(f,"The number of incomplete tasks: %d\n",num_tasks);
    fclose(f);
}

// print the list of tasks sorting in priority
int compare_tasks_priority(const void* t1, const void* t2) {
    Task* task1 = *(Task**)t1;
    Task* task2 = *(Task**)t2;
    return task1->priority - task2->priority;
}

void task_ls_priority() {
    int num_tasks = 0;

    // Use read_all_tasks_from_file() to read the list of tasks from the file
    Task **task_list = read_all_tasks_from_file("task.txt", &num_tasks);
    if (task_list == NULL) {
        printf("\nNo tasks to do.");
        return;
    }
    
    // sort the tasks in the list by priority using qsort()
    qsort(task_list, num_tasks, sizeof(Task*), compare_tasks_priority);

    printf("\nList of incomplete tasks in priority order:\n");
    
    // display all contents by iterating using get_printable_task() 
    for (int i = 0; i < num_tasks; i++) {
        printf("%d. ", i+1);
        printf("%s", get_printable_task(*(task_list + i)));
    }
    printf("The number of incomplete tasks: %d\n",num_tasks);

    // print into a file display.txt
    FILE *f = fopen("display.txt", "w");
    fprintf(f,"\nList of incomplete tasks in priority order:\n");
    for (int i = 0; i < num_tasks; i++) {
        fprintf(f, "%s", get_printable_task(*(task_list + i)));
    }
    fprintf(f,"The number of incomplete tasks: %d\n",num_tasks);
    fclose(f);
    
}


// print the list of tasks sorting in deadline
int compare_tasks_by_deadline(const void *task1, const void *task2) {
    Task *t1 = *(Task**)task1;
    Task *t2 = *(Task**)task2;

    if (t1->deadline.year != t2->deadline.year) {
        return t1->deadline.year - t2->deadline.year;
    } else if (t1->deadline.month != t2->deadline.month) {
        return t1->deadline.month - t2->deadline.month;
    } else {
        return t1->deadline.day - t2->deadline.day;
    }
}


void task_ls_deadline() {
    int num_tasks = 0;
    Task **task_list = read_all_tasks_from_file("task.txt", &num_tasks);
    if (task_list == NULL) {
        printf("\nNo tasks to do.");
        return;
    }

    // Sort tasks based on deadline using mergesort
    qsort(task_list, num_tasks, sizeof(Task*), compare_tasks_by_deadline);

    // Print sorted tasks
    printf("\nList of incomplete tasks in deadline order:\n");
    for (int i = 0; i < num_tasks; i++) {
        printf("%d. ", i+1);
        printf("%s", get_printable_task(*(task_list + i)));
    }
    printf("The number of incomplete tasks: %d\n",num_tasks);
    
    // print into a task_dl file
    FILE *f = fopen("display.txt", "w");
    fprintf(f,"\nList of incomplete tasks in deadline order:\n");
    for (int i = 0; i < num_tasks; i++) {
        fprintf(f, "%s", get_printable_task(*(task_list + i)));   
    }
    fprintf(f,"The number of incomplete tasks: %d\n",num_tasks);
    fclose(f);
    
}




