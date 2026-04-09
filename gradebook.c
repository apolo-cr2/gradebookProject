/*****************************************************************************************************************************************************************
    Project Name: Gradebook Project
  
    Project Collaborators: 
                          1. Alejandro Polo Bicenio (Group Leader)
                          2. Ivan Ceballos
                          3. Frederick H. Fox
                          4. Luqman Shah
                          
    Project file name: gradebook.c


    Project Objectives:


    Project Notes: This is the basic structure in C.
  
****************************************************************************************************************************************************************/    
#include <stdio.h>

int main()
{
    int modify_choice, selection_choice;
    
    /*int student_ID; or int id*/
    /*double grade_point_average;*/
    /*char student_name; or char name;*/
    
    
    
    printf("Greetings, you are now logged in the Gradebook program...\n\n");
    printf("Do you want to modify the gradebook?\nYes = Press any number>>\nNo = Press 0 >>\n\n");
    scanf("%d", &modify_choice);
    
    
    while(modify_choice != 0)
    {
        
        printf("Activating case statement...\n\n");
        printf("Make a selection from these choices: \n\n1. Add\n2. Find\n3. Update\n4. Delete\n5. List\n\n");
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
                
            default:
                printf("Invalid selection!!!\n\n");
                
            
        }
        
        
        /*We will call the print procedure here...*/
        printf("Printing out  gradebook results!!!\n\n");
        
        
        
        
        printf("Do you want to keep modifying the gradebook?\nYes = Press any button>>\nNo = Press 0 >>\n\n");
        scanf("%d", &modify_choice);
    }
    
    
    
    printf("You have pressed 0\nExiting Program...");
    
    return 0;
}

