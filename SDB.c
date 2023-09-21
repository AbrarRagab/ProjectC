#include <stdio.h>
#include <stdlib.h>
#include "SDB.h"
#include "STD.h"

uint8 count = 0; //global counter for students initialized with zero(even if it's not initialized it will get the value 0 as it's global)
student* start = NULL; //head pointer to the first node in dynamic memory allocation (global instead of passing it to each function)


bool SDB_IsFull ()    //for knowing if the database capacity is full or not
{   
    if(10 == count)
      {
          return true; //full
      }
    else
       {
          return false; //not full
       }
}
uint8 SDB_GetUsedSize() // to know and return the number of students in the database
{
    student* current = start;

    while (current != NULL) // I'll be able to know the size used as long as the count is less than 10 and we didn't reach the end of the list
    {
        count++;
        current = current->link;
    }

    return count;
}

bool SDB_AddEntry()  //to add a new student into the database
{
    if (SDB_IsFull())
    {
        printf("Database is full. Cannot add more students.\n");
        return false;
    }

    student* NewStudent =(student*)malloc(sizeof(student));  //creating a new node to have a place to add student
    if (!NewStudent)
    {
        return false; // Allocation failed
    }

    printf("Enter the database for %d student : \n",count+1);
    printf("Student ID: ");
    scanf("%u",&NewStudent->Student_ID);

    if (SDB_IsIdExist(NewStudent->Student_ID)) // To ask first whether the id existed before or not and if not then we will add it
    {
        if(start == NULL)
            return false;

        printf("Student ID already exists. Please enter a different ID.\n");
        free(NewStudent); // Free memory for the node
        return false;     // ID already exists, return false
    }

    printf("\nStudent year: ");
    scanf("%d",&NewStudent->Student_year);

    printf("\nCourse1 ID: ");
    scanf("%d",&NewStudent->Course1_ID);

    printf("\nCourse1 grade: ");
    scanf("%d",&NewStudent->Course1_grade);

    printf("\nCourse2 ID: ");
    scanf("%d",&NewStudent->Course2_ID);

    printf("\nCourse2 grade: ");
    scanf("%d",&NewStudent->Course2_grade);

    printf("\nCourse3_ID: ");
    scanf("%d",&NewStudent->Course3_ID);

    printf("\nCourse3 grade: ");
    scanf("%d",&NewStudent->Course3_grade);

    NewStudent->link = NULL;


    // Add the new node to the linked list
    if (start == NULL)
    {
        start = NewStudent; //assigning the head to the first node
    }
    else //if it is not the first node
    {
        student* current = start;
        while (current->link != NULL)
        {
            current = current->link;  //traversing through the next nodes
        }
        current->link = NewStudent;
    }
    count++; //Increment the global count variable to keep updating
    return true ;
}

void SDB_DeleteEntry(uint32 id)   //for deleting a student from the database by their ID
{
    student* temp=NULL;
    if(start == NULL) //list is empty, no nodes are created yet
    {
        printf("List is empty! There are no Students in our database.\n");
        return;
    }
    //Deleting if the id is found in the first node at the list
    if(start->Student_ID == id)
    {
        temp = start; //temporary pointer to have the address of the first node
        start = start->link;  // making the start or (the head) pointing to the address of the 2nd node
        free(temp);   //I can now free the temp, which means deleting that first node, since I cannot free the start
        count --; //decrementing the global count variable to keep updating
        printf("Student's Data is Deleted Successfully.\n");
        return; //now the start or (the head) is pointing at the previous called 2nd node, which makes it now the first
    }

    //Deleting in betweens
    student* ptr = start;
    while(ptr->link != NULL)
    {
        if(ptr->link->Student_ID == id) //standing on the previous node and asking if the next is the  one to delete so i can manage to link again, as i am using only one pointer
        {
            temp=ptr->link;
            break;
        }
        ptr = ptr->link; //moving the pointer to the next one(traversing)
    }
    if(ptr->link == NULL)
        printf(" .ID Not Found\n");
    else // if the break happens
    {
        ptr->link=temp->link;
        free(temp);
        printf("Student's Data is Deleted Successfully.\n");
        count --; //decrementing the global count variable to keep updating
    }
    return;
}
bool SDB_ReadEntry(uint32 id) //function to display other data of student when his/her ID is enterd
{
    student* current = start; //creating a pointer to use it to traverse the list
    while (current != NULL)
    {
        if (current->Student_ID == id)
        {
            //printing (showing) the data of the selsected student to the user
            printf("Student ID: %d\n", current->Student_ID);
            printf("Student Year: %d\n", current->Student_year);
            printf("Course1_ID: %d\n", current->Course1_ID);
            printf("Course1_grade: %d\n", current->Course1_grade);
            printf("Course2_ID: %d\n", current->Course2_ID);
            printf("Course2_grade: %d\n", current->Course2_grade);
            printf("Course3_ID: %d\n", current->Course3_ID);
            printf("Course3_grade: %d\n", current->Course3_grade);

            return true; // Data found
        }
        current = current->link;
    }
    
    if(start == NULL)  //if the database is empty
    {
        printf("there are no students in the database!\n");
        return false; //Data not found
    }
    else if((SDB_IsIdExist(id) == 0)) // to cover the case that the user may enter a wrong id.
    {
        printf("Student doesn't exist! Or try again and make sure you write the right ID.\n");
    }
    return false;//there is no student with this ID
}

void SDB_GetList(uint32 *list) //creating a list (array) to have all the entered students' IDs
{
    printf("Number of IDs : %d\n", count);
    student* current =start; //creating new pointer to struct student, have the adrdress of start
    uint8 index = 0; // Index to populate the list array
    while (current != NULL)
    {
        list[index]= current->Student_ID;  //assigning the current id of a student to the list array at the index position
        index++;
        current = current->link; //moving forward to the next node
    }
    if(start != NULL)  //if there are students in the database
    { 
        for(index = 0; index < count; index++)
        {
           printf("Student ID : %u  \n", list[index]);  // printing the student ID
        }
    }
   
}

bool SDB_IsIdExist(uint32 id)
{
    student* current = start;
    while (current != NULL)
    {
        if (current->Student_ID == id)
        {
            return true; // ID exists in the database
        }
        current = current->link;
    }
    return false; // ID not found in the database
}