#include <stdio.h>
#include <stdlib.h>
#include "skiplist.h"

int main()
{
    SkipList list;
    initSkipList(&list);

    // Load Demo Students
    insertStudent(&list, 101, "Rehan Mokashi", 88.5);
    insertStudent(&list, 102, "Sakshi Patil", 92.0);
    insertStudent(&list, 103, "Aarav Sharma", 79.4);
    insertStudent(&list, 104, "Sneha Kulkarni", 85.2);
    insertStudent(&list, 105, "Arjun Rao", 91.3);
    insertStudent(&list, 106, "Neha Singh", 76.8);
    insertStudent(&list, 107, "Manish Deshmukh", 83.0);
    insertStudent(&list, 108, "Kiran Joshi", 89.1);
    insertStudent(&list, 109, "Ritika Mehta", 95.0);
    insertStudent(&list, 110, "Sagar Pawar", 72.5);

    printf("\n10 demo student records loaded successfully!\n");

    int choice;

    int roll;
    char name[50];
    float marks;
    Node *found;

    while (1)
    {
        printf("\n===== Student Database using Skip List =====\n");
        printf("1. Insert / Update Student\n");
        printf("2. Search Student by Roll\n");
        printf("3. Delete Student by Roll\n");
        printf("4. Display All Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter roll number: ");
            scanf("%d", &roll);

            printf("Enter name: ");
            scanf(" %[^\n]", name);   // read full line

            printf("Enter marks: ");
            scanf("%f", &marks);

            insertStudent(&list, roll, name, marks);
            break;

        case 2:
            printf("Enter roll number to search: ");
            scanf("%d", &roll);

            found = searchStudent(&list, roll);
            if (found != NULL)
            {
                printf("Record found:\n");
                printf("Roll: %d\nName: %s\nMarks: %.2f\n",
                       found->key, found->name, found->marks);
            }
            else
            {
                printf("Record with roll %d not found.\n", roll);
            }
            break;

        case 3:
            printf("Enter roll number to delete: ");
            scanf("%d", &roll);

            if (deleteStudent(&list, roll))
            {
                printf("Record deleted.\n");
            }
            else
            {
                printf("Record with roll %d not found.\n", roll);
            }
            break;

        case 4:
            displayStudents(&list);
            break;

        case 5:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
