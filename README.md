**********************************************************************************************************************************************************
This is the final project for the course CSC251 at CSUDH for the Spring of 2026. Members of this repository include:
1. Alejandro Polo Briceno (Group Leader)
2. Ivan Ceballos
3. Frederick H. Fox
4. Luqman Shah

Our choice of the final project is "gradebook - persistent records with sorting and updates."
**********************************************************************************************************************************************************
Project Name: Gradebook Project

Project Purpose: The purpose of the gradebook final project is to manage student records such as ID number, names, and grades across multiple runs without corrupting the file.

Project Objectives:

1. Build a working gradebook menu that correctly takes an input from the user and takes them to their selection choice: adding/deleting, finding, updating, listing, sorting, statistics, demo.
2. Build a loop that takes the user back to the gradebook menu after making their previous selection choice.
3. Create methods for all selection choices and make sure they run as intended:
   - Adding/Removing: Adding and removing students from the gradebook list
   - Finding: Finding a student from the list from their ID.
   - Updating: Selecting a student from the list from their ID, and updating their name and grades.
   - Listing: Listing all students from the gradebook list.
   - Sorting: Sorting all students by either their ID first to last, name alphabetically, or grade averages.
   - Statistics: Printing the amount of students there are, the class average, highest and lowest averages of two students, and class pass rate.
   - Demo: Prints a demo output with pre-populated students, including any students the user enters themselves, and applies certain methods such as sorting by grade average and updating.
4. Run the program plenty of times with multiple students populated and ensure it does not break or terminate.

Project Notes:

- There are certain topics used in this project that were not covered in the lectures. Instead, we used w3schools.com to research the necessary material to create our program how we envisioned it. Some of these include:
  - Arrays
  - Typedef Structures
  - Parsing
  - Reading and Writing to Files
  - Enumeration
- Because C and Java are closely related, we used previous CSC Java courses that contained the same strucutre/thematics to build our code.
**********************************************************************************************************************************************************
BUILD/RUN INSTRUCTIONS:

1. Clone the git repository using SSH key and open the folder in VSCode.
2. Once the folder is open, click Run and in the terminal, press 1 and click enter to open the menu.
3. A series of options will appear, enter the corresponding number of your selection choice.
4. Follow the steps for each selection:
   - 1: Add Student
      - Enter the new student's ID number: cannot exceed number 5800.
      - Enter the new student's name: cannot exceed 70 characters total.
      - Enter the new student's 1st, 2nd, and 3rd score: must be in between 0.00 and 100.00
   - 2: Find Student
      - Enter a student's ID number to display all of their information.
   - 3: Update Student
      - Enter a student's ID number to update their information.
      - Enter a new name for the student. If you wish to keep the name, leave the field blank.
      - Enter a new score for the 1st, 2nd, and 3rd scores. If you wish to keep all, two, or one exam score, leave those fields blank.
   - 4: Delete Student
      - Enter a student's ID number to delete that student.
      - Once the student is selected, type "YES" to delete them. If you wish to keep them, leave the field blank.
   - 5: List Student
      - Once selected, the students will be listed.
   - 6: Sort Student
      - Enter the corresponding number of how the students should be listed: by ID, Name ascending, or Average descending.
      - Enter "y" to save the sorting choice to the file. Enter "n" to not save the sorting choice to the file.
   - 7: Statistics
      - Once selected, information regarding the class will be displayed.
   - 8: Run Demo
      - Once selected, the terminal will showcase the use cases for the add, sort, update, and statistics functions.
   - 9: Exit Program
      - Once selected, the program will terminate, closing the gradebook.
5. After selection choice is completed, press 1 to return to the gradebook menu.


INPUT FORMATS:

The input format for the students and their information are int, char, and double values respectively.


LIMITATIONS:

- All of our schedule's did not line up how we wanted, so that made the process of completing the code challenging.
- The Parsing in our code took many attempts to get right. Frederick was in charge of the parsing functions and ran through many iterations of the code to get it to how the group envisioned.
- Because our knowledge of C was limited to the material in the course, we used the website w3schools.com to research the necessary material to build our code. This took time to understand and implement certain topics in our code.


BREAKDOWN OF EACH MEMBER'S CONTRIUBTION:

1. IVAN
   - 'update_student'
   - 'sort_students_ui'
   - 'insertion_sort_my_students'
   - Constructing the README
2. FREDERICK
   - 'stats_ui'
   - 'parse_int_strict'
   - 'parse_double_strict'
   - 'run_gradebook_demo'
   - 'write_my_student'
   - 'parse_my_student_line'
   - 'print_gradebook_menu'
   - 'print_exit_message'
   - Constructing the Preliminary Logic before building code
3. LUQMAN
   - 'add_my_student'
   - 'delete_student'
   - Assisted with the creation of other methods
4. ALEJANDRO
   - 'find_my_student_index_by_id'
   - 'find_student_ui'
   - Creating the GitHub repository and handling any error cases

Any other methods not listed here was done with equal contribution from each member. 

**********************************************************************************************************************************************************
