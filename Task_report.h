/*-----*/
/*task_report*/

void task_report()
{

    // print undone task
    int num_tasks;
    Task **task_list = read_all_tasks_from_file("task.txt", &num_tasks);

    if (task_list == NULL || num_tasks == 0) {
        printf("No task to do\n");
    }

    printf("\nPending: %d\n", num_tasks);
    for(int i=0; i<num_tasks; i++)
    {   
        printf("%d.", i+1);
        printf("%s",get_printable_task(*(task_list+i)));
    }

    // print done task

    int num_tasks_completed = 0;
    Task **task_list_completed = read_all_tasks_from_file("done.txt", &num_tasks_completed);
    
    if(task_list_completed==NULL)
    {
        printf("No tasks done.\n");
    }

    printf("\nDone task: %d\n", num_tasks_completed);
    for(int i=0; i<num_tasks_completed; i++)
    {   
        printf("%d.", i+1);
        printf("%s",get_printable_complete_task(*(task_list_completed+i)));
    }

    FILE *f = fopen("display.txt", "w");
    if (task_list == NULL || num_tasks == 0) {
        fprintf(f,"No task to do\n");
    }
    fprintf(f,"Pending: %d\n", num_tasks);
    for(int i=0; i<num_tasks; i++)
    {   
        fprintf(f,"%d.", i+1);
        fprintf(f,"%s",get_printable_task(*(task_list+i)));
    }

    if(task_list_completed==NULL)
    {
        fprintf(f,"No tasks done.\n");
    }        
    fprintf(f,"Done task: %d\n", num_tasks_completed);
    for(int i=0; i<num_tasks_completed; i++)
    {   
        fprintf(f,"%d.", i+1);
        fprintf(f,"%s",get_printable_complete_task(*(task_list_completed+i)));
    }
    fclose(f);
}
