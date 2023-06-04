/*-----*/
/*Delete task from task.txt*/
void task_del(int task_index, const char *filepath) {
    int num_tasks = 0;
    Task **task_list = read_all_tasks_from_file(filepath, &num_tasks);
    if (task_list == NULL || num_tasks == 0) {
        printf("No task to do\n");
        return;
    }
    if (task_index < 0 || task_index > num_tasks) {
        printf("Index %d does not exist\n", task_index);
        FILE *f_d = fopen("display.txt","w");
        fprintf(f_d, "Index %d does not exist\n", task_index);
        fclose(f_d);
        return;

    }
    Task *task_to_delete = task_list[task_index-1];
    for (int i = task_index - 1; i < num_tasks - 1; i++) {
        task_list[i] = task_list[i + 1];
    }
    printf("Deleted task at index %d:\n%s\n", task_index, get_printable_task(task_to_delete));

    FILE *f_d = fopen("display.txt","w");
        fprintf(f_d, "Deleted task at index %d:\n%s", task_index, get_printable_task(task_to_delete));
    fclose(f_d);

    free(task_to_delete);
    task_list[num_tasks - 1] = NULL;
    num_tasks--;

    // print after deleting task
    printf("List of incomplete task after deleting: \n");
    for (int i = 0; i < num_tasks; i++) {
        printf("%d. ", i+1);
        printf("%s", get_printable_task(*(task_list + i)));
    }

    // fix txt file
    FILE *f = fopen(filepath, "w");
    for (int i = 0; i < num_tasks; i++) {
        fprintf(f, "%s", get_printable_task(task_list[i]));
    }
    fclose(f);
}

