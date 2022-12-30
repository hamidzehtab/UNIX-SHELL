# UNIX-SHELL
Operating System - SIMPLE UNIX SHELL

Autumn 2022

Developed By :
    Ali.M Tabatabaee (Ali Ninja)
    Hamid Zehtab     (The Honey Badger)

A brief introduction and Summary :
this is a unix shell with an addition of some useful commands.
each command is executed after calling the fork function.
you can also use pipe and all other builtin commands of a regular unix shell. also added the extra feature of handeling Ctrl+c in our shell.

First clone the project using :
<<<<<<< HEAD
git clone 'the project github URL'(you can copy it from above the page)

compile the shell.c file using :
 gcc shell.c -lreadline


Run an instance of the program :
./a.out



Specific Commands :
1-head : head
-> shows the first 10 lines of each file

2-rws : removeWhiteSpace
-> removes all the white spaces such as 'space , /t , /n' from the text file and shows the result

3-nl : numOfLines
-> shows the number of lines in each file

4-suc : show uncommented
-> shows the lines which are not commented (with # charachter)

5-mfw : mostFrequentWord
-> returns the string which is the most repeated

6-fw : FirstWordofLines
-> returns the beginning of every text file which is seprated by space from the rest of the line   



all other general commands available in UNIX shell

Featured pipe handling

improper space handling
=======
git clone https://github.com/hamidzehtab/UNIX-SHELL.git

compile the shell.c file using :
gcc shell.c -lreadline

Run an instance of the program :
./a.out

Specific Commands :

1-nl 'name of the file'  : (number of lines ) this command will return the number of lines in the given file 

2-rws 'name of the file' : (remove white spaces) this command will remove all the white spaces in the given file and print the result in the shell.

3-suc 'name of the file' : (show uncommented) will print out all the lines in the file that are not commented 

4-fw 'name of the file' : (first word in each line) this will print the first word of every line in file.

5-mwf 'name of the file' : (most frequent word) as the name suggests this command will print out the most repeated word in the given file.

6-head 'name of the file' : (head) this will print out the first ten lines of the file.
>>>>>>> 028117c0c4825422bd4dcaf10a11e9ab206abf9d
