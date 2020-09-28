# c-finder
An easy and very simple C program to find if a certain string is in an file or not!

How to:

    If you want to compile, just:
         gcc c-finder.c -o c-finder

    To run the program:
         ./c-finder name_of_the_file

If you need any help, consult the help option: 
    - c-finder h


File-Name.txt will be the file that will contain the name of the files that matched the search word.

This is a work in progress. If you detect any problem or issue, contact me! And of course, if you have any suggestions for improvement (and I know
you have!), contact me!

Know Issues: 
    - The Array Texto[] has an allocated memory limit of 400 bytes. If the file is longer than that, it will only store up to 400 bytes. And even worse if the array has not stored everything, it may give a false return in relation to that in the text it may not have the searched string but in the file it has... 

    - Working to solve this Issue!