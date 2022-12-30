# UNIX-SHELL
Operating System - SIMPLE UNIX SHELL
Developed By :
    Ali.M Tabatabaee (Ali Ninja)
    Hamid Zehtab     (The Honey Badger)

A brief introduction and Summary :
this is a unix shell with an addition of some useful commands.
each command is executed after calling the fork function.
you can also use pipe and all other builtin commands of a regular unix shell. also added the extra feature of handeling Ctrl+c in our shell.

First clone the project using :
git clone https://github.com/hamidzehtab/UNIX-SHELL.git

compile the shell.c file using :
gcc shell.c -lreadline

Run an instance of the program :
./a.out

Specific Commands :
1-nl 'name of the file'  : (number of lines ) this command will return the number of lines in the given file 

2-rws 'name of the file' : (remove white spaces) this command will remove all the white spaces in hte given file and print the result in the bash.

3-suc 'name of the file' : (show uncommented) will print out all the lines in the file that are not commented 

4-fw 'name of the file' : (first word in each line) this will print the first word of every line in file.

5-mwf 'name of the file' : (most frequent word) as the name suggests this command will print out the most repeated word in the given file.

6-head 'name of the file' : (head) this will print out the first ten lines of the file.
