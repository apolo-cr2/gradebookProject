/*****************************************************************************************************************************************************************
                        Project Name: Gradebook Project.
  
                    Project Collaborators: 
                    1. Alejandro Polo Bicenio (Group Leader)
                    2. Ivan Ceballos
                    3. Frederick H. Fox
                    4. Luqman Shah
                          
                          
        Project file name: gradebook.c


        Project Objectives:


        Project Notes: This is the basic structure in C with an updated print_gradebook_menu method.
  
****************************************************************************************************************************************************************/    
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>




#define GRADEBOOK_DATA_FILE "gradebook.txt"
/*#define GRADEBOOK_TEMPORARY_FILE "gradebook.tmp"*/


#define MAX_NUMBR_OF_STUDENTS 5808   //The biggest highschool in the United States has over 5800 students. This school is Brooklyn Technical High School.  
#define MAX_LENGTH_OF_NAME 70  
#define MAX_LENGTH_OF_LINE 400
#define NUMBR_OF_SCORES 3


typedef struct {
    int student_id_nmbr;   
    char student_name[MAX_LENGTH_OF_NAME + 1];
    double student_score[NUMBR_OF_SCORES];
} Student;

typedef enum {
    SORT_ID = 1,
    SORT_NAME = 2,
    SORT_AVRG = 3
} SortKey;


/**************************************************************************
                    
                        Method print_gradebook_menu

***************************************************************************/
static void print_gradebook_menu(void){
   printf("******************Gradebook*******************\n");
   
   printf("Make a selection from the commands below:\n\n"); 
   printf("\t1. Add student>>\n");
   printf("\t2. Find student>>\n");
   printf("\t3. Update student>>\n");
   printf("\t4. Delete Student>>\n");
   printf("\t5. List Student>>\n" );
   printf("\t6. Sort Student>>\n");
   printf("\t7. Statistics || Calculate class average>>\n\n");
   
   printf("***********************************************\n");
/***************************print_gradebook_menu() ENDS HERE***************/   




/**************************************************************************
                    
                            Method print_exit_message

***************************************************************************/
}

static void print_exit_message(void){
    printf("You have pressed 0\nExiting Program...\nHave a nice day!!!");
}
/***************************print_exit_message() ENDS HERE*****************/




/**************************************************************************
                    
                            Method Main

***************************************************************************/
int main()
{
    int modify_choice, selection_choice;
    
    
    
    printf("logging in...\nWelcome to the Gradebook program...\n\n");
    
    
    FILE * fptr;
    
    //Open a file in read mode.
    fptr = fopen(GRADEBOOK_DATA_FILE, "r");
    
    // Store the content of the file.
    char gradebook_string[MAX_LENGTH_OF_LINE];
    
    
    //If the file does exist:
    if (fptr != NULL)
    {
      printf("***********************************************************\n");
      printf("Presenting preliminary information extracted from the file:\n\n");
    
      //Read the file's content and print it to the user:
      while(fgets(gradebook_string, MAX_LENGTH_OF_LINE, fptr))
      {
         printf("\t%s", gradebook_string);
      }
      
      
      
    } else {
       printf("Loading unsuccessful:\n\tERROR CODE 505: File does not exist\n"); 
    }
    
    fclose(fptr);
    
    
    
    printf("\n\nDo you want to use the gradebook program?\n\tYes = Press any whole number>>\n\tNo = Press 0>>\n\n");
    scanf("%d", &modify_choice);
    
    
    while(modify_choice != 0)
    {
        print_gradebook_menu();
        scanf("%d", &selection_choice);
        
        
        
        switch (selection_choice)
        {
            case 1:
                /*We will call the Add method here...*/
                printf("Activating ADD Method...\n");
                /*add();*/     /*This is a method Call...*/
                break;
                
            case 2: 
                /*We will call the Find method here...*/
                printf("Activating Find Method...\n");
                break;
            
            case 3: 
                /*We will call the Update method here...*/
                printf("Activating Update Method...\n");
                break;
                
            case 4: 
                /*We will call the Delete method here...*/
                printf("Activating Delete Method...\n");
                break;
                
            case 5: 
                /*We will call the List method here...*/
                printf("Activating List Method...\n");
                break;
            
            case 6: 
                /*We will call the Sort method here...*/
                printf("Activating calculateAverage Method...\n");
                break;
                
            case 7: 
                /*We will call the statistics method below...*/
                printf("Activating statistics Method...\n");
                break;

                
            default:
                printf("Invalid selection!!!\n\n");
                
        }
        
        /*We will call the print procedure here...*/
        printf("Printing out  gradebook results!!!\n\n");
        
        
        
        
        printf("Do you want to keep modifying the gradebook?\n\tYes = Press any button>>\n\tNo = Press 0 to exit>>\n\n");
        scanf("%d", &modify_choice);
    }
    
    print_exit_message();
   
    
    return 0;
}
/*************************Method main ENDS HERE*******************************/

