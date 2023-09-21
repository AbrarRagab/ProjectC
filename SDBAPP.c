#include <stdio.h>
#include <stdlib.h>
#include "STD.h"
#include "SDB.h"

//executing the function based on the choice
void SDB_action(uint8 choice) //function contains a super loop to preform a certain operation(case), depending on the choice of the user
{
    switch (choice)
    {
    case 1: //will be performed if pressed 1
        if (SDB_AddEntry()) //calling for the function to allow the user to add one more student to the database
        {
            printf("Student data added successfully.\n"); //one student added
        }
        else
        {
            printf("Failed to add student data.\n"); //couldn't add a student
        }
        break;

    case 2: //will be performed if pressed 2
        printf("Used size in database: %d\n", SDB_GetUsedSize()); //will print the size (number of students) currently in the database
        break;

    case 3: //will be performed if pressed 3
    {
        uint32 idToSearch; //creating new variable represents existing id, to read the student information
        printf("Enter student ID to read: ");
        scanf("%u", &idToSearch);
        if (SDB_ReadEntry(idToSearch)) //we will do the searching by calling the function ReadEntry
        {
            printf("Data found for student with ID %d.\n", idToSearch);
        }
        else
        {
            SDB_IsIdExist(idToSearch); //in case the user didn't enter an existing id
            printf("Data not found for student with ID %d.\n", idToSearch);
        }
        break;
    }

    case 4:  //will be performed if pressed 4
    {
        uint32 idList[10]; // Assuming you have a maximum of 10 students
        SDB_GetList(idList); //allowing the list of students' IDs to be created when the user wants to
        break;
    }

    case 5:  //will be performed if pressed 5
    {
        uint32 idToCheck;  //creating new variable represents id, to compare it with the existing IDs in the database to know whether it exists or not
        printf("Enter student ID to check: ");
        scanf("%u", &idToCheck);
        if (SDB_IsIdExist(idToCheck)) //the comparing will be preformed when IsExist function is called, giving it the new id (idToCheck)
        {
            printf("Student with ID %d is already registered.\n", idToCheck); //id already exits
        }
        else
        {
            printf("Student with ID %d isn't registered.\n", idToCheck); //id doesn't exixt
        }
        break;
    }

    case 6: //will be performed if pressed 6
    {
        uint32 idToDelete;
        printf("Enter student ID to delete: ");
        scanf("%d", &idToDelete);
        if (SDB_IsIdExist(idToDelete) == 0) // in case the user entered an Id that doesn't exist to be deleted
            printf("Sorry! you entered an invalid ID, please make sure you enter an existing ID");
        SDB_DeleteEntry(idToDelete);
        break;
    }

    case 7: //will be performed if pressed 7
        if (SDB_IsFull())
        {
            printf("Database is full.\n");
        }
        else
        {
            printf("Database is not full.\n");
        }
        break;

    case 0: //will be performed if pressed 0
        printf("Exiting the program.\n");
        exit(0);  //if the user wants no further operation to be done

    default:
        printf("Invalid choice. Please choose a valid option.\n"); //if the user entered an invalid case
    }
}

void SDB_APP()  // This function concludes the whole app
{
    while(count != 3) //to make sure at first we enter three students
    {
       SDB_AddEntry();
    }
	
    while (1)  // to ensure the program always working
    {
        uint8 choice;   //to allow the user to choose the operation he wants to be done unless exitted by the exit case

        printf("Please choose an option:\n");
        printf("1. Add entry\n");
        printf("2. Get used size in database\n");
        printf("3. Read student data\n");
        printf("4. Get the list of all student IDs\n");
        printf("5. Check if ID exists\n");
        printf("6. Delete student data\n");
        printf("7. Check if database is full\n");
        printf("0. Exit\n");
        fflush(stdin);

        printf("Enter your choice: ");
        scanf("%d", &choice);

        SDB_action(choice); //calling for the function that will enable the operation selected to be preformed
    }
}