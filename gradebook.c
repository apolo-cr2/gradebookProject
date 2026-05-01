/*****************************************************************************************************************************************************************
                        Project Name: Gradebook Project.
  
                    Project Collaborators: 
                    1. Alejandro Polo Bicenio (Group Leader)
                    2. Ivan Ceballos
                    3. Frederick H. Fox
                    4. Luqman Shah
                          
                          
        Project file name: gradebook.c


        Project Objectives:


        Project Notes: This is the final basic structure of this project.
  
****************************************************************************************************************************************************************/    
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define GRADEBOOK_DATA_FILE "gradebook.txt"
#define GRADEBOOK_TEMPORARY_FILE "gradebook.tmp"


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

            trim_my_newline method  

*************************************************************************/
static void trim_my_newline(char *s)
{
   
   size_t length;
   
   if(s == NULL)
   {
      return;
   }
   
   length = strlen(s);
   
   while (length > 0 && (s[length - 1] == '\n' || s[length - 1] == '\r'))
   {
      s[length - 1] = '\0';
      length--;
   }
}
/***********END OF trim_my_newline method*********************************/



/**************************************************************************

                     trim_my_whitespace method

**************************************************************************/
static void trim_my_whitespace(char *s)
{
   char *my_start;
   char *my_end;
   size_t len;
   
   if (s == NULL || s[0] == '\0')
   {
      return;
   }
   
   
   my_start = s;
   while (*my_start != '\0' && isspace((unsigned char)*my_start))
   {
      my_start++;
   }
   
   if(my_start != s)
   {
      memmove(s, my_start, strlen(my_start) + 1);
   }
   
   len = strlen(s);
   if(len == 0)
   {
      return;
   }
   
   my_end = s + len - 1;
   
   while(my_end >= s && isspace((unsigned char)*my_end))
   {
      *my_end = '\0';
      if(my_end == s)
      {
         break;
      }   
      my_end--;
   }
   
}
/*********************************************************************/


/**************************************************************************

                     read_line_stdin method

**************************************************************************/
static int read_line_stdin(char *buffer, size_t size)
{
   int ch;

   if(buffer == NULL || size == 0U)
   {
      return 0;
   }
   
   if(fgets(buffer, (int)size, stdin) == NULL)
   {
      return 0;
   }
   
   if (strchr(buffer, '\n') == NULL)
   {
      ch = getchar();
      
      while (ch != '\n' && ch != EOF)
      {
         ch = getchar();
      }
   }
   trim_my_newline(buffer);
   return 1;

}
/******************************************************************/





/*************************************************************************
  
                    parse_int_strict method       
    
/*************************************************************************/
static int parse_int_strict(const char *text, int *my_out_value)
{
   char *endptr;
   long value;

   if(text == NULL || my_out_value == NULL)
   {
      return 0;
   }


   errno = 0;
   endptr = NULL;
   
   value = strtol(text, &endptr, 10);
   
   if (errno != 0 || endptr == text)
   {
      return 0;
   }
   
   while (*endptr != '\0') 
   {
        if (!isspace((unsigned char)*endptr)) {
            return 0;
        }
        endptr++;
   }

    if (value <= 0L || value > 2147483647L) {
        return 0;
    }

    *my_out_value = (int)value;
    return 1;
}

/************************************************************/


/**************************************************************************

                    parse_double_strict method                    

**************************************************************************/
static int parse_double_strict(const char *text, double *out_value) {
    char *endptr;
    double value;

    if (text == NULL || out_value == NULL) 
    {
        return 0;
    }

    errno = 0;
    endptr = NULL;
    value = strtod(text, &endptr);

    if (errno != 0 || endptr == text) {
        return 0;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return 0;
        }
        endptr++;
    }

    *out_value = value;
    return 1;
}
/***********************************************************************/



/**************************************************************************

                    parse_double_strict method                    

************************************************************************/
static int valid_my_score(double my_score)
{
   return my_score >= 0.0 && my_score <= 100.0;
}
/*************************************************************************/


/**************************************************************************

                   valid_my_name method                    

/*************************************************************************/
static int valid_my_name(const char *my_name)
{
   size_t i;
   size_t length;
   
   if (my_name == NULL)
   {
      return 0;
   }
   
   length = strlen(my_name);
   
   if (length == 0U || length > MAX_LENGTH_OF_NAME) {
        return 0;
    }

    for (i = 0U; i < length; i++) {
        if (my_name[i] == '|') {
            return 0;
        }
    }

    return 1;   
}

/*****************************************************************/



/**************************************************************************

                   student_is_valid Method                    

/*************************************************************************/
static int student_is_valid(const Student *s)
{
   int i;
   
   if(s == NULL)
   {
      return 0;
   }
   
   
   
   if (s->student_id_nmbr <= 0 || !valid_my_name(s->student_name)) 
   {
        return 0;
   }

    for (i = 0; i < NUMBR_OF_SCORES; i++) {
        if (!valid_my_score(s->student_score[i])) {
            return 0;
        }
    }

    return 1;

}
/*************************************************************************/



/**************************************************************************

                   student_is_valid Method                    

/*************************************************************************/
static double average_of_student(const Student *s)
{
   int i;
   double my_sum = 0.0;
   
   if (s == NULL)
   {
      return 0.0;
   }
   
   for(i = 0; i < NUMBR_OF_SCORES; i++)
   {
      my_sum += s->student_score[i];
   }
   
   return my_sum / (double)NUMBR_OF_SCORES;
   
}
/************************************************************************/




/*************************************************************************
         
                    find_my_student_index_by_id Method                  

/*************************************************************************/
static int find_my_student_index_by_id(const Student my_students[], int count, int id)
{
   int i;
   
   for(i = 0; i < count; i++)
   {
      if(my_students[i].student_id_nmbr == id)
      {
         return i;
      }
   }
   return -1;
}

/*************************************************************************/




/*************************************************************************
         
                     write_my_student Method                  

/*************************************************************************/
static int write_my_student(FILE *fptr, const Student *s)
{
   if(fptr == NULL || s == NULL)
   {
      return 0;
   }

   return fprintf(fptr, "%d|%s|%.2f|%.2f|%.2f\n", s->student_id_nmbr, s->student_name, s->student_score[0], s->student_score[1], s->student_score[2]) >= 0;


}
/****************************************************************************/



/*************************************************************************
         
                      parse_my_student_line Method                  

/*************************************************************************/
static int parse_my_student_line(const char *my_line, Student *out_my_student)
{
   char my_buffer[MAX_LENGTH_OF_LINE];
   char *parts[5];
   char *cursor;
   char *sep;
   
   int i;
   Student s;
   
   
   if(my_line == NULL || out_my_student == NULL)
   {
      return 0;
   }

   if (strlen(my_line) >= sizeof(my_buffer)) 
   {
        return 0;
   }
   
   strcpy(my_buffer, my_line);
   cursor = my_buffer;
   
   for (i = 0; i < 5; i++) 
   {
        parts[i] = cursor;
        sep = strchr(cursor, '|');
        
        if (i < 4) 
        {
            if (sep == NULL) 
            {
                return 0;
            }
            *sep = '\0';
            cursor = sep + 1;
        } else {
            if (sep != NULL) 
            {
                return 0;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        trim_my_whitespace(parts[i]);
    }

    if (!parse_int_strict(parts[0], &s.student_id_nmbr)) {
        return 0;
    }

    if (!valid_my_name(parts[1])) {
        return 0;
    }
    strcpy(s.student_name, parts[1]);

    if (!parse_double_strict(parts[2], &s.student_score[0])) {
        return 0;
    }
    if (!parse_double_strict(parts[3], &s.student_score[1])) {
        return 0;
    }
    if (!parse_double_strict(parts[4], &s.student_score[2])) {
        return 0;
    }

    if (!student_is_valid(&s)) {
        return 0;
    }

    *out_my_student = s;
    return 1;
}
/*************************************************************************************/


/**************************************************************************

            load_students_from_gradebook method

***************************************************************************/
static int load_students_from_gradebook(Student myStudents[], int *count)
{
    FILE * fptr;
 
   char max_line[MAX_LENGTH_OF_LINE];
   int line_number = 0;
   int loaded = 0;
 
 
   if(myStudents == NULL || count == NULL)
   {
      return 0;
   }
   
   *count = 0;
   
    //Open a file in read mode.
    fptr = fopen(GRADEBOOK_DATA_FILE, "r");
    
    
    if (fptr == NULL)
    {
      return 1;
    }
    
    //
    while(fgets( max_line, sizeof(max_line), fptr) != NULL)
    {
       Student s;
       int duplication = 0;
       int i;
       
       line_number++;
       trim_my_newline(max_line);
       trim_my_whitespace(max_line);
       
       
       if(max_line[0] == '\0')
       {
         continue;
       }
       
       if(!parse_my_student_line(max_line, &s))
       {
         fprintf(stderr,"Alert: The system has skipped a malformed line %d\n", line_number);
         continue;
       }
       
       for(i = 0; i < loaded; i++)
       {
         if(myStudents[i].student_id_nmbr == s.student_id_nmbr)
         {
            duplication = 1;
            fprintf(stderr, "Alert: Duplicate ID detected!!!\n\tDuplicate ID %d has been skipped on line %d\n", s.student_id_nmbr, line_number);
            break;
         
         }
       
       }
       
       if (duplication)
       {
         continue;
       }
       
       if (loaded >= MAX_NUMBR_OF_STUDENTS)
       {
         fprintf(stderr, "Alert: Max capacaity has been reached.\n\tThe rest of the lines are iognored...\n");
         break;
       }
       
       myStudents[loaded] = s;
       loaded++;
    }
    
    if(fclose(fptr) != 0)
    {
      perror("fclose");
      return 0;    
    }
    
    *count = loaded; 
    return 1;
}
/****************************************************************************/


/*****************************************************************************

                          save_my_students method 

******************************************************************************/
static int save_my_students(const Student my_students[], int count)
{
   FILE * fptr;
   int i;

   fptr = fopen(GRADEBOOK_TEMPORARY_FILE, "w");
   
   if(fptr == NULL)
   {
      perror("fopen temporary file for gradebook.\n");
      return 0;
   }
   
   for (i = 0; i < count; i++)
   {
      if (!write_my_student(fptr, &my_students[i]))
      {
         fclose(fptr);
         remove(GRADEBOOK_TEMPORARY_FILE);
         
         fprintf(stderr, "Software Error:\n\tReason---The system was not able to write a temp file\n");
         return 0;
      
      }
   }
   
   
   if(fflush(fptr) != 0)
   {
      perror("fflush");
      fclose(fptr);
      
      remove(GRADEBOOK_TEMPORARY_FILE);
      return 0;
   
   }


   if(fclose(fptr) != 0)
   {
      perror("fclose");
      remove(GRADEBOOK_TEMPORARY_FILE);
      return 0;
   }


   if (remove(GRADEBOOK_DATA_FILE) != 0)
   {
      if (errno != ENOENT)
      {
         perror("System is removing the old data file.");
         remove(GRADEBOOK_TEMPORARY_FILE);
         return 0;
      }
   }
   
   if(rename(GRADEBOOK_TEMPORARY_FILE, GRADEBOOK_DATA_FILE) != 0)
   {
      perror("rename temp");
      remove(GRADEBOOK_TEMPORARY_FILE);
      return 0;
   
   }
   
   return 1;
}
/************************************************************************/






/*************************************************************************

               compare_my_students Method

/*************************************************************************/
static int compare_my_students(const Student *s1, const Student *s2, SortKey my_key)
{

   if(my_key == SORT_ID)
   {
      if (s1->student_id_nmbr < s2->student_id_nmbr)
      {
         return -1;
      } else if (s1->student_id_nmbr > s2->student_id_nmbr)
      {
         return 1;
      }
          
      return 0;
   }
   
   if(my_key == SORT_NAME)
   {
      int cmp = strcmp(s1->student_name, s2->student_name);
      
      if(cmp != 0)
      {
         return cmp;
      } else if(s1->student_id_nmbr < s2->student_id_nmbr)
      {
         return -1;
      } else if(s1->student_id_nmbr > s2->student_id_nmbr)
      {
         return 1;
      }
      
      return 0;
   }
   
   if(my_key == SORT_AVRG)
   {
      double avg_s1 = average_of_student(s1);
      double avg_s2 = average_of_student(s2);
      
      if(avg_s1 > avg_s2)
      {
         return -1;
      } else if(avg_s1 < avg_s2)
      {
         return 1;
      }
      else if(s1->student_id_nmbr < s2->student_id_nmbr)
      {
         return -1;
      } else if(s1->student_id_nmbr > s2->student_id_nmbr)
      {
         return 1;
      }
      
      return 0;
      
   }
   
   return 0;
}


/********************************************************************************/






/*********************************************************************************/
/*IVAN ADD insertion_sort_my_students SORT HERE */
/**********************************************************************************/










/******************************************************************************************

                    Method print_header

*******************************************************************************************/
static void print_header(void)
{
   printf("********************************************************************************************************\n");
   printf("\n%-10s %-30s %-10s %-10s %-10s %-10s\n", "ID #", "NAME", "SCORE1", "SCORE2", "SCORE3", "AVERAGE");
   printf("********************************************************************************************************\n");
}
/********************************************************************************************/





/********************************************************************************************

                    Method print_student_info

/********************************************************************************************/
static void print_student_info(const Student *s)
{
   printf("\n%-10d %-30s %-10.2f %-10.2f %-10.2f %-10.2f\n", 
            s->student_id_nmbr, 
            s->student_name, 
            s->student_score[0], 
            s->student_score[1],
            s->student_score[2], 
            average_of_student(s));
    
}
/*********************************************************************************************/







/*********************************************************************************************

                        Method list_my_students

/*********************************************************************************************/
static void list_my_students(const Student my_students[], int my_count)
{
   int i;
   
   
   if(my_count == 0)
   {
      printf("\nWARNING: No student records are found.\n");
      return;
   }
   
   print_header();
   for(i = 0; i < my_count; i++)
   {
      print_student_info(&my_students[i]);
   }
   printf("\n********************************************************************************************************\n");

} 
/*********************************************************************************************/


/**************************************************************************
                    
                        Method prompt_my_int

***************************************************************************/
static int my_prompt_int(const char *my_prompt, int *out_my_value)
{
   char my_line[MAX_LENGTH_OF_LINE];

   for(;;)
   {
      printf("%s", my_prompt);
      
      if(!read_line_stdin(my_line, sizeof(my_line)))
      {
         return 0;
      }
      
      trim_my_whitespace(my_line);
      
      if(parse_int_strict(my_line, out_my_value))
      {
         return 1;
      }

      printf("Invalid integer.\n");
   
   }


}
/**************************************************************************/


/**************************************************************************
                    
                        Method prompt_my_score

***************************************************************************/
static int prompt_my_score(const char *my_prompt, double *out_my_value)
{
   char my_line[MAX_LENGTH_OF_LINE];
   double my_value;

   for(;;)
   {
      printf("%s", my_prompt);
      
      if(!read_line_stdin(my_line, sizeof(my_line)))
      {
         return 0;
      }
      
      trim_my_whitespace(my_line);
      
      if(parse_double_strict(my_line, &my_value) && valid_my_score(my_value))
      {
         *out_my_value = my_value;
         return 1;
      }

      printf("Invalid integer.\n");
   }

}  
/**************************************************************************/


/**************************************************************************
                    
                        Method prompt_my_name

***************************************************************************/
static int prompt_my_name(const char *my_prompt, char *out_my_name, size_t out_my_size)
{
   char my_line[MAX_LENGTH_OF_LINE];

   for(;;)
   {
       printf("%s", my_prompt);
       
      if(!read_line_stdin(my_line, sizeof(my_line)))
      {
         return 0;
      }

      trim_my_whitespace(my_line);
       
       
      if(!valid_my_name(my_line))
      {
         printf("Invalid name.\n");
         continue;
      }
       
      if(strlen(my_line) >= out_my_size)
      {
         printf("Name too long\n");
         continue;
      }
      
      strcpy(out_my_name, my_line);
      return 1;
       
   }
}
/**************************************************************************/




/****************************************************************************
luqman put add method here:
    
****************************************************************************/
/****************************************************************************
Luqman put delete method here:
   
****************************************************************************/


/****************************************************************************
Alejandro put find method here:
    
****************************************************************************/


/****************************************************************************
Ivan put update method here:
   
****************************************************************************/



/****************************************************************************
Ivan put sort method here:
   
****************************************************************************/


/****************************************************************************
Frederick put stats method here:
   stats_ui()
****************************************************************************/

/****************************************************************************
Frederick put demo method here:
   run_gradebook_demo(myStudents, &count);
****************************************************************************/

































/**************************************************************************
                    
                        Method print_gradebook_menu

***************************************************************************/
static void print_gradebook_menu(void){
   printf("\n****************Gradebook*Menu******************\n");
   
   printf("Make a selection from the commands below:\n\n"); 
   printf("\t1. Add student>>\n");
   printf("\t2. Find student>>\n");
   printf("\t3. Update student>>\n");
   printf("\t4. Delete Student>>\n");
   printf("\t5. List Student>>\n" );
   printf("\t6. Sort Student>>\n");
   printf("\t7. Statistics>>\n");
   printf("\t8. Run demo>>\n\n");
   printf("\t9. To EXIT program>>\n\n");
   
   printf("***********************************************\n");
/***************************print_gradebook_menu() ENDS HERE***************/   




/**************************************************************************
                    
                            Method print_exit_message

***************************************************************************/
}

static void print_exit_message(void){
    printf("\n========================================================");
    printf("\nYou have pressed 9\n\nThank you for using the gradebook program.\nExiting Program...\nHave a nice day!!!");
    printf("\n========================================================");
    
}
/***************************print_exit_message() ENDS HERE*****************/




/**************************************************************************
                    
                            Method Main

***************************************************************************/
int main(void)
{
    Student myStudents[MAX_NUMBR_OF_STUDENTS];
    int modify_choice, selection_choice;
    int count = 0;
    
    
    
    printf("Starting Program...              <\nWelcome to the Gradebook program!<\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^<\n\n\n");
    
    
    if (!load_students_from_gradebook(myStudents, &count))
    {
      fprintf(stderr, "Loading unsuccessful:\n\tERROR CODE 505: File does not exist\n");
      return 1; 
    }
    
    printf("==================================================================================================\n");   
    printf("The program has loaded %d valid record(s) from the choosen file\n", count);
    printf("==================================================================================================\n");
    
    my_prompt_int("\n\nPress 1 to go to menu: \n", &modify_choice);
    
    
    while(1)
    {
        print_gradebook_menu();
        my_prompt_int("Make a selection: ", &selection_choice);
        
        
        switch (selection_choice)
        {
            
            case 1:
                /*We will call the Add method here...*/
                printf("Activating ADD Method...\n");
                add_my_student(myStudents, &count);    
                break;
                
            case 2: 
                /*We will call the Find method here...*/
                printf("Activating Find Method...\n");
                find_student_ui(myStudents, count);
                break;
            
            case 3: 
                /*We will call the Update method here...*/
                printf("Activating Update Method...\n");
                update_student(myStudents, count);
                break;
                
            case 4: 
                /*We will call the Delete method here...*/
                printf("Activating Delete Method...\n");
                delete_student(myStudents, &count);
                break;
                
            case 5: 
                /*We will call the List method here...*/
                printf("Activating List Method...\n");
                list_my_students(myStudents, count);
                break;
            
            case 6: 
                /*We will call the Sort method here...*/
                printf("Activating Sort Method...\n");
                sort_students_ui(myStudents, count);
                break;
                
            case 7: 
                /*We will call the statistics method below...*/
                printf("Activating statistics Method...\n");
                stats_ui(myStudents, count);
                break;
                
            case 8:
                printf("Running Demo...\n");
                run_gradebook_demo(myStudents, &count);
                break;
                
            case 9:
                print_exit_message();
                return 0;
                
            default:
                printf("Invalid selection!!!\n\n");
                
        }
    
        
        printf("\n\n");
        my_prompt_int("Press 1 to go the menu: ", &modify_choice);
    }
    
    
   
    return 0;
}
/*************************Method main ENDS HERE*******************************/


