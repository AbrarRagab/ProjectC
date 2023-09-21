#ifndef SDB_H_INCLUDED
#define SDB_H_INCLUDED
#include "STD.h"

typedef struct SimpleDb
{
    uint32 Student_ID;
    uint32 Student_year;
    uint32 Course1_ID;
    uint32 Course1_grade;
    uint32 Course2_ID;
    uint32 Course2_grade;
    uint32 Course3_ID;
    uint32 Course3_grade;
    struct SimpleDb* link; //making the struct self referential by using pointer link to point to the struct of the same type to allow do Linked List.
} student;

//functions headers
bool SDB_IsFull(void); //checking the database is full or not
uint8 SDB_GetUsedSize(void); //knowing the number of students in the database by using counter
bool SDB_AddEntry(); //for adding a new student
void SDB_DeleteEntry(uint32 id); //for deleting a student from the database by their ID
bool SDB_ReadEntry(uint32 id); //for reading the student data
void SDB_GetList(uint32 *list); //to get the number of IDs in the database and print them
bool SDB_IsIdExist(uint32 id); //to know whether the student exists or not
void SDB_APP(void); //running program
void SDB_action(uint8 choice); //executing certain function based on the user's choice



#endif // SDB_H_INCLUDED
