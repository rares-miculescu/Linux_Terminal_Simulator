/* MICULESCU Rares-Dumitru -Linux Terminal Simulator*/
The program simulates the basic commands of a linux terminal
We have the following commands:
    1. touch
    2. mkdir
    3. ls
    4. rm
    5. rmdir
    6. cd
    7. pwd
We have 3 structures that we use:
    1. directory, contains the data of a directory
    2. files, contains the data of a file
    3. arboref, the structure for a generic binary tree
To make the program work we used these functions:
    1.  genroot:    initializes the root
    2.  checkDir:   searches the directory tree for an element with that name
    3.  checkFiles: searches the files tree for an element with that name
    4.  genFile:    function that generates a file type cell
    5.  AddARF:     function that adds the file in the file tree
    6.  touch:      makes a new file
    7.  genDir:     function that generates a directory type cell
    8.  AddARD:     function that adds the directory in the directory tree
    9.  mkdir:      makes a new directory
    10. ParcD:      goes through the directory tree and prints it 
    11. ParcF:      goes through the file tree and prints it
    12. ls:         calls the two previous functions
    13. swapCel:    swaps the content of two tree cells
    14. rmStDrF:    deletes from the lexicographical list the given file
    15. rm:         deletes the file  
    16. rmStDrD:    deletes from the lexicographical list the given directory
    17. rmdir:      deletes the directory
    18. pwd:        goes untill root and then prints
    19. cd:         checks if the given directory exists and then switches to it