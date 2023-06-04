/* ---------- */
/*Add task to task.txt*/
void task_add(int task_priority, char* task_text, Date *d, const char *filepath) {
    int num_tasks;
    Task **task_list = read_all_tasks_from_file(filepath, &num_tasks);

    // Check if the new task already exists in the file
    for (int i = 0; i < num_tasks; i++) {
        if (strcmp(task_list[i]->text, task_text) == 0 && compare_dates(&task_list[i]->deadline, d) == 0) {
            printf("Task already exists:\n");
            printf("%s", get_printable_task(task_list[i]));
            FILE *f = fopen("display.txt", "w");
                fprintf(f,"Task already exists:\n");
                fprintf(f,"%s", get_printable_task(task_list[i]));
            fclose(f);
            return; // Exit function if task already exists
        }
    }

    Task *new_task = initialize_task(task_text, task_priority, d);
    FILE *f = fopen(filepath, "a");
    fprintf(f, "%s", get_printable_task(new_task));
    fclose(f);
    printf("Added task:\n");
    
    // display the task using - get_printable_task()
    char *task_str = get_printable_task(new_task);
    printf("%s", task_str);


    // print in display.txt
    FILE *f1 = fopen("display.txt", "w");
        fprintf(f1,"Added task:\n");
        fprintf(f1,"%s", task_str);
    fclose(f1);

}