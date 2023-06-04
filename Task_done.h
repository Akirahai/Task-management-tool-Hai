/*-----*/
/*Mark done task*/
void task_done(int task_index)
{
    int num_tasks;
    Task **task_list = read_all_tasks_from_file("task.txt", &num_tasks);
    if (task_list == NULL || num_tasks == 0) {
        printf("No task to do\n");
        return;
    }

    if (task_index < 0 || task_index >= num_tasks) {
        printf("Index %d does not exist\n", task_index);
        return;
    }

    Task *done_task = task_list[task_index-1];
    for (int i = task_index - 1; i < num_tasks - 1; i++) {
        task_list[i] = task_list[i + 1];
    }

    printf("Completed task at index %d:\n%s\n", task_index, get_printable_task(done_task));
    FILE *done_f = fopen("done.txt", "a");
        fprintf(done_f, "%s", get_printable_complete_task(done_task));
    fclose(done_f);


    FILE *f_d = fopen("display.txt","w");
        fprintf(f_d, "Completed task at index %d:\n%s", task_index, get_printable_task(done_task));
    fclose(f_d);

    free(done_task);
    task_list[num_tasks - 1] = NULL;
    num_tasks--;

    FILE *f = fopen("task.txt", "w");
    for (int i = 0; i < num_tasks; i++) {
        fprintf(f, "%s", get_printable_task(task_list[i]));
    }
    fclose(f);

    return;
}