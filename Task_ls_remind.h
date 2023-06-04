/*-----*/
/* Remind of tasks */
// Get_days_left for date
int get_days_left(Date d) {
    time_t t = time(NULL);
    struct tm *local_time = localtime(&t);

    int curr_day = local_time->tm_mday;
    int curr_month = local_time->tm_mon + 1;
    int curr_year = local_time->tm_year + 1900;

    // calculate the number of days left by subtracting the current date from the task's deadline date
    int days_left = (d.year - curr_year) * 365 + (d.month - curr_month) * 30 + (d.day - curr_day);

    return days_left;
}


void task_ls_remind() {
    time_t t = time(NULL);
    struct tm *local_time = localtime(&t);
    int uncompleted_today_count = 0;
    int uncompleted_future_count = 0;
    int uncompleted_past_count = 0;

    printf("Current local date: %02d/%02d/%04d\n", local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900);

    int num_tasks = 0;

    // Use read_all_tasks_from_file() to read the list of tasks from the file
    Task **task_list = read_all_tasks_from_file("task.txt", &num_tasks);
    if (task_list == NULL) {
        printf("\n\nNo tasks to do.");
        return;
    }
    
    // sort the tasks in the list by priority using qsort()
    qsort(task_list, num_tasks, sizeof(Task*), compare_tasks_priority);
    
    // display all contents whose deadline is the same as the date today by iterating using get_printable_task()
    printf("\nToday tasks: \n");
    for (int i = 0; i < num_tasks; i++) {
        int days_left = get_days_left((*(task_list + i))->deadline);
        if (days_left == 0) {
            printf("%d. ", i+1);
            printf("%s", get_printable_task(*(task_list + i)));
            uncompleted_today_count ++;
        }
    }
    if (uncompleted_today_count == 0) {
        printf("No tasks have deadline today.\n");
    }
    printf("The number of incomplete tasks today: %d\n",uncompleted_today_count);

    // display all contents whose deadline in the future by iterating using get_printable_task()
    printf("\nFuture tasks: \n");
    for (int i = 0; i < num_tasks; i++) {
        int days_left = get_days_left((*(task_list + i))->deadline);        
        if (days_left > 0 ) {
            printf("%s", get_printable_task(*(task_list + i)));
            printf("Due in %d day(s).\n", days_left);
            uncompleted_future_count++;
        }
    }
    if (uncompleted_future_count == 0) {
        printf("No tasks have deadline in the future .\n");
    }
    printf("The number of incomplete tasks in the future: %d\n",uncompleted_future_count);

    // display all contents whose deadline in the past by iterating using get_printable_task()
    printf("\nPast tasks: \n");
    for (int i = 0; i < num_tasks; i++) {
        int days_left = get_days_left((*(task_list + i))->deadline);        
        if (days_left <0 ) {
            printf("%s", get_printable_task(*(task_list + i)));
            uncompleted_past_count++;
        }
    }
    printf("The number of incomplete tasks in the past: %d\n",uncompleted_past_count);

    // print into display.txt file
    FILE *f = fopen("display.txt", "w");
    fprintf(f,"Current local date: %02d/%02d/%04d\n", local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900);
    fprintf(f,"\nToday tasks: \n");
    for (int i = 0; i < num_tasks; i++) {
        int days_left = get_days_left((*(task_list + i))->deadline);
        if (days_left == 0) {
            fprintf(f, "%s", get_printable_task(*(task_list + i)));
        } 
    }
    if (uncompleted_today_count == 0) {
        fprintf(f, "No tasks have deadline today.\n");
    }
    fprintf(f,"The number of incomplete tasks today: %d\n",uncompleted_today_count);
    /*----*/
    fprintf(f,"\nFuture tasks: \n");
    for (int i = 0; i < num_tasks; i++) {
        int days_left = get_days_left((*(task_list + i))->deadline);        
        if (days_left > 0 ) {
            fprintf(f,"%s", get_printable_task(*(task_list + i)));
            fprintf(f,"Due in %d day(s).\n", days_left);
        }
    }
    if (uncompleted_future_count == 0) {
        fprintf(f,"No tasks have deadline in the future .\n");
    }
    fprintf(f,"The number of incomplete tasks in the future: %d\n",uncompleted_future_count);  
    
    /*----*/
    fprintf(f,"\nPast tasks: \n");
    for (int i = 0; i < num_tasks; i++) {
        int days_left = get_days_left((*(task_list + i))->deadline);        
        if (days_left <0 ) {;
            fprintf(f,"%s", get_printable_task(*(task_list + i)));
        }
    }
    fprintf(f,"The number of incomplete tasks in the past: %d\n",uncompleted_past_count);
    fclose(f);
}