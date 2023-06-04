#include "Task_struct.h"

#include "Task_ls.h"

#include "Task_add.h"

#include "Task_del.h"

#include "Task_done.h"

#include "Task_ls_remind.h"

#include "Task_report.h"


int main() {
    char input[STD_STRING_SIZE];
    int option;
    int sort_option;
    int delete_index;
    int done_index;
    char task_text[STD_STRING_SIZE];
    int task_priority, task_day, task_month, task_year;
    
    printf("------TASK MANAGEMENT----- \n");

    do {
        printf("\n------MENU------- \n");
        printf("Enter an option:\n");
        printf("1. Add a task\n");
        printf("2. Display all tasks\n");
        printf("3. Delete a task\n");
        printf("4. Show due tasks \n");
        printf("5. Mark done task\n");
        printf("6. Report task\n");
        printf("0. Exit\n");
        printf("Note: only input a number from 0 to 6\n");
        printf("Option: ");
        //fgets(input, sizeof(input), stdin);
        // option = atoi(input);
        scanf("%d", &option);
        system("taskkill /im notepad.exe /f");
        switch (option) {
            case 1: // Add a task
                printf("Enter task text: ");
                getchar();
                gets(task_text);
                printf("Enter task priority: ");
                fgets(input, sizeof(input), stdin);
                task_priority = atoi(input);
                printf("Enter task deadline (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &task_day, &task_month, &task_year);
                getchar(); // consume newline character from scanf
                task_add(task_priority, task_text, initialize_date(task_day, task_month, task_year), "task.txt");
                system("start notepad.exe display.txt");
                //
                break;

            case 2: // Display all tasks
                printf("Choose an option to display the task list: \n");
                printf("1. Sorting by the index \n");
                printf("2. Sorting by priority \n");
                printf("3. Sorting by deadline \n");
                printf("Option: ");
                scanf("%d", &sort_option);
                

               if (sort_option == 1) {
                    task_ls();
                    system("start notepad.exe display.txt");
                    
               } else if (sort_option == 2) {
                    task_ls_priority();
                    system("start notepad.exe display.txt");
                    
               } else if (sort_option == 3) {
                    task_ls_deadline();
                    system("start notepad.exe display.txt");
                    
               }
                
                break;

            case 3: // Delete a task
                task_ls();
                system("start notepad.exe display.txt");
                printf("Type in the index of the tasks you want to delete: ");
                scanf("%d", &delete_index);
                task_del(delete_index, "task.txt");
                system("start notepad.exe display.txt");
                break;
                

            case 4: // Show due tasks
                task_ls_remind();
                system("start notepad.exe display.txt");
                break;
                
            
            case 5: // Mark done task
                task_ls();
                system("start notepad.exe display.txt");
                printf("Type in the index of the tasks you want to mark done: ");
                scanf("%d", &done_index);
                task_done(done_index);
                system("start notepad.exe display.txt");
                break;
                

            case 6: // Report task
                task_report();
                system("start notepad.exe display.txt");
                break;
                
            case 0: // Exit
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid option. Please enter a valid option.\n");
        }

    } while (option != 0);

    return 0;
}