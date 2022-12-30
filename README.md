Operating System - SIMPLE UNIX SHELL

Autumn 2022

Developed By : Ali.M Tabatabaee (Ali Ninja) Hamid Zehtab (The Honey Badger)

A brief introduction and Summary : this is a unix shell with an addition of some useful commands. each command is executed after calling the fork function. you can also use pipe and all other builtin commands of a regular unix shell. also added the extra feature of handeling Ctrl+c in our shell.

First clone the project using :   git clone https://github.com/hamidzehtab/UNIX-SHELL.git

compile the shell.c file using : gcc shell.c -lreadline

Run an instance of the program : ./a.out

Specific Commands : 1-head : head -> shows the first 10 lines of each file

2-rws : removeWhiteSpace -> removes all the white spaces such as 'space , /t , /n' from the text file and shows the result

3-nl : numOfLines -> shows the number of lines in each file

4-suc : show uncommented -> shows the lines which are not commented (with # charachter)

5-mfw : mostFrequentWord -> returns the string which is the most repeated

6-fw : FirstWordofLines -> returns the beginning of every text file which is seprated by space from the rest of the line

all other general commands available in UNIX shell

Featured pipe handling
improper space handling
