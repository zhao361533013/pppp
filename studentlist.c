/*******************************************************************************
List of header files - do NOT use any other header files. Note that stdlib and
cstring are included in case you want to use any of the functions in there.
However the task can be achieved with stdio only.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*******************************************************************************
List preprocessing directives - you may define your own.
*******************************************************************************/
/* Maximum number of students in the class */
#define MAX_CLASS_SIZE 5
/* Maximum length of the string - student name. Note that all strings in C are
NULL terminated i.e. '\0' at the end of the string. Hence the length of the
actual name can be 10 characters at most*/
#define MAX_NAME_SIZE 11 
/* Static file name of the text file where student list is stored */
#define DB_FILE_NAME "database"


/*******************************************************************************
List structs - you may define struct date and struct student only. Each struct
definition should have only the fields mentioned in the assignment description.
*******************************************************************************/
struct date
{
	int day;
	int month;
	int year;
};typedef struct date date_t;

struct student
{
	char name [MAX_NAME_SIZE];
	float gpa;
	date_t birthday;
};typedef struct student student_t;


/*******************************************************************************
Function prototypes - do NOT change the given prototypes. However you
may define your own functions if required.
*******************************************************************************/
void printMenu(void);
student_t add(void);
int readChoice(void);
void display(int num, const student_t array[]);
int save(const student_t studentlist[], int *num);
int read(int*num, student_t studentlist[]);
/*******************************************************************************
Main2
*******************************************************************************/
int main(void)
{
	int choice;
	int num = 0;
	student_t studentlist [MAX_CLASS_SIZE];
	while ((choice = readChoice())!= 6)
	{
		switch (choice)
		{
	    case 1 : 
	        if (num >= 5)
			{
				printf ("Class is full\n");
			}
			if (num < 5)
			{
				studentlist[num] = add();
				num++;
			}
			break;
		case 2 :
			if (num == 0)
			{ 
				printf("Class is empty\n");
			} 
			if (num != 0)
			{ 
				num--;
			} 
			break;
		case 3 :
			if (num == 0)
			{
				printf("Class is empty\n");
		    } 
	        if (num != 0)
			{	
				display(num, studentlist);
		    }
			break;
		case 4: 
			save (studentlist, &num);
			break;
		case 5:
			read (&num, studentlist);
			break;
		default:
			printf ("Invalid choice.\n");
			break;
		}
	}
	return 0;
}


/*******************************************************************************
printMenu
This function prints the initial menu with all instructions on how to use this
program.
inputs:
- none
outputs:
- none
*******************************************************************************/
void printMenu(void)
{
	printf("\n\n"
	"1. add student\n"
	"2. delete last student\n"
	"3. display student list\n"
	"4. save the student list to the database\n"
	"5. read the student list from the database\n"
	"6. exit the program\n"
	"Enter your choice>");
}


/*******************************************************************************
readChoice
This function read the choice from the user and return it to the main function
inputs:
- none
outputs:
- int, the choice of the user. 
*******************************************************************************/
int readChoice()
{
	int choice;
	printMenu ();
	scanf ("%d", &choice);
	return choice;
}


/*******************************************************************************
add
This function get the information from the user and return a new student_t to 
the main function
inputs:
- none
outputs:
- student_t. a new student.
*******************************************************************************/
student_t add()
{   
    int count;
    char input;
	student_t new;
    getchar();
	printf ("Enter name>"); 
    for  (count =0;(input = getchar() )!= '\n'; count ++)
    {
    	if (count < 10)
    		{
    			new.name[count] = input ;
			}
	}
    printf("Enter birthday: day>"); 
    scanf("%d", &new.birthday.day);
	while (new.birthday.day > 31 || new.birthday.day < 1)
    {
	  	printf("Invalid day. Enter birthday: day>");
    	scanf("%d", &new.birthday.day);
	}
	printf("Enter birthday: month>");
    scanf("%d", &new.birthday.month);
    while (new.birthday.month>12 || new.birthday.month<1)
	{
		printf("Invalid month. Enter birthday: month>");
	    scanf("%d", &new.birthday.month);
	}
    printf("Enter birthday: year>");
    scanf("%d", &new.birthday.year);
    while (new.birthday.year>2017 || new.birthday.year<1800)
	{
		printf("Invalid year. Enter birthday: year>");
        scanf("%d", &new.birthday.year);
	}
	printf ("Enter GPA>");
	scanf ("%f", &new.gpa);
	while (new.gpa>4.0 || new.gpa<0.0)
	{	
	    printf ("Invalid GPA. Enter GPA>");
	    scanf ("%f", &new.gpa);
	}
	return new;
}


/*******************************************************************************
display
This function shows all of the student in the studentlist,
when the number is 0, It will display "The class is empty".
inputs:
- int num, student_t studentlist
outputs:
- none
*******************************************************************************/
void display(int num, const student_t studentlist[])
{
	int count;
	printf("Name       Birthday   GPA\n");
	printf("---------- ---------- ------\n");
	for(count = 0; count<num; count++)
	{
		printf ("%-10.10s ", studentlist[count].name);
		printf ("%02d-", studentlist[count].birthday.day);
		printf ("%02d-", studentlist[count].birthday.month);
		printf ("%04d ", studentlist[count].birthday.year);
		printf ("%6.4lf\n", studentlist[count].gpa);
	}
}


/*******************************************************************************
save
This function save the studentlist into the Systemfile named database, If the 
file not exit, this function will create a new one. 
- int *num, student_t studentlist
outputs:
- int return 1 means save fail,return 0 means save successful. 
*******************************************************************************/ 
int save(const student_t studentlist[], int *num)
{
	FILE *fp = fopen(DB_FILE_NAME, "wb");
	if (fp == NULL) 
	{
		return 1;
	}
	fwrite(num, sizeof(int), 1, fp);
	fwrite(studentlist, sizeof(student_t), *num,fp);
	fclose (fp);
	return 0;
}


/*******************************************************************************
read
This function read the studentlist from the Systemfile named database.
input
- int *num, student_t studentlist.
outputs:
- int return 1 means read fail,return 0 means read successful. 
*******************************************************************************/        	
int read(int* num, student_t studentlist[])
{
	FILE *fp = fopen(DB_FILE_NAME, "rb");
    if(fp == NULL)
    {
    	printf ("Read error\n");
    	return 1;
    }
	fread(num, sizeof(int), 1, fp);
    fread(studentlist, sizeof(student_t), *num, fp);
	fclose (fp);
	return 0;
}
