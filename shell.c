// C Program to design a shell in Linux
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

// Greeting shell during startup
void init_shell()
{
	clear();
	printf("\n\n\n\n******************"
		"************************");
	printf("\n\n\n\t****MY SHELL****");
	printf("\n\n\t-USE AT YOUR OWN RISK-");
	printf("\n\n\n\n*******************"
		"***********************");
	char* username = getenv("USER");
	printf("\n\n\nUSER is: @%s", username);
	printf("\n");
	sleep(1);
	clear();
}

// Function to take input
int takeInput(char* str)
{
	char* buf;

	buf = readline(">>> ");
	if (strlen(buf) != 0) {
		add_history(buf);
		strcpy(str, buf);
		return 0;
	} else {
		return 1;
	}
}

// Function to print Current Directory.
void printDir()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s", cwd);
}

// Function where the system command is executed
void execArgs(char** parsed)
{
	// Forking a child
	pid_t pid = fork();

	if (pid == -1) {
		printf("\nFailed forking child..");
		return;
	} else if (pid == 0) {
		if (execvp(parsed[0], parsed) < 0) {
			printf("\nCould not execute command..");
		}
		exit(0);
	} else {
		// waiting for child to terminate
		wait(NULL);
		return;
	}
}

// Function where the piped system commands is executed
void execArgsPiped(char** parsed, char** parsedpipe)
{
	// 0 is read end, 1 is write end
	int pipefd[2];
	pid_t p1, p2;

	if (pipe(pipefd) < 0) {
		printf("\nPipe could not be initialized");
		return;
	}
	p1 = fork();
	if (p1 < 0) {
		printf("\nCould not fork");
		return;
	}

	if (p1 == 0) {
		// Child 1 executing..
		// It only needs to write at the write end
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(parsed[0], parsed) < 0) {
			printf("\nCould not execute command 1..");
			exit(0);
		}
	} else {
		// Parent executing
		p2 = fork();

		if (p2 < 0) {
			printf("\nCould not fork");
			return;
		}

		// Child 2 executing..
		// It only needs to read at the read end
		if (p2 == 0) {
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execvp(parsedpipe[0], parsedpipe) < 0) {
				printf("\nCould not execute command 2..");
				exit(0);
			}
		} else {
			// parent executing, waiting for two children
			wait(NULL);
			wait(NULL);
		}
	}
}

// Help command builtin
void openHelp()
{
	puts("\n***WELCOME TO MY SHELL HELP***"
		"\nCopyright @ Suprotik Dey"
		"\n-Use the shell at your own risk..."
		"\nList of Commands supported:"
		"\n>cd"
		"\n>ls"
		"\n>exit"
		"\n>all other general commands available in UNIX shell"
		"\n>pipe handling"
		"\n>improper space handling");

	return;
}

int numOfLines(char parsed[])
{
	FILE *fp;
		int count = 0;  // Line counter (result)
		char filename[50];
		char c;  // To store a character read from file
	
		// Get file name from user. The file should be
		// either in current folder or complete path should be provided
		fp = fopen(parsed, "r");
	
		// Check if file exists
		if (fp == NULL)
		{
			printf("Could not open file %s", parsed);
			return 0;
		}
		// Extract characters from file and store in character c
		for (c = getc(fp); c != EOF; c = getc(fp))
			if (c == '\n') // Increment count if this character is newline
				count = count + 1;
		// Close the file
		fclose(fp);
		printf("The file %s has %d lines\n ", parsed, count);
		return 1;
}
int head (char parsed[])
{
	FILE *myfile;
		char content[200];
		int max = 0;

		// Open file
		myfile = fopen(parsed, "r");
		if (myfile == NULL)
		{
			printf("Cannot open file \n");
			exit(0);
		}
		// Read the first 10 lines from file
		fgets(content, 200, myfile);
		while (content != EOF)
		{
			max++;
			if (max > 10)
				break;
			printf("%s", content);
			fgets(content, 200, myfile);
		}

		fclose(myfile);
		return 1;
}
int mostFrequentWord(char parsed[])
{
	FILE *file;  
	char ch, *line;  
	size_t len = 0, read;  
	char words[1000][1000], word[20];  
	int i = 0, j=0, k, maxCount = 0, count;  
		
	//Opens file in read mode  
	file = fopen(parsed,"r");  
		
	//If file doesn't exist  
	if (file == NULL){  
			printf("File not found");  
			exit(EXIT_FAILURE);  
	}  
		
	//Since, C doesn't provide in-built function,   
	//following code will split content of file into words  
	while ((read = getline(&line, &len, file)) != -1) {  
			printf ("%s", line);
		for(k=0; line[k]!='\0'; k++){  
			//Here, i represents row and j represents column of two-dimensional array words   
			if(line[k] != ' ' && line[k] != '\n' && line[k] != ',' && line[k] != '.' ){  
				words[i][j++] = tolower(line[k]);  
			}  
			else{  
				words[i][j] = '\0';  
				//Increment row count to store new word  
				i++;  
				//Set column count to 0  
				j = 0;  
			}  
		}  
	}  
	
	int length = i;  
	
	//Determine the most repeated word in a file  
	for(i = 0; i < length; i++){  
		count = 1;  
		//Count each word in the file and store it in variable count  
		for(j = i+1; j < length; j++){  
			if(strcmp(words[i], words[j]) == 0 && (strcmp(words[i]," ") != 0)){  
				count++;  
			}   
		}  
		//If maxCount is less than count then store value of count in maxCount   
		//and corresponding word to variable word  
		if(count > maxCount){  
			maxCount = count;  
			strcpy(word, words[i]);  
			//printf(word);
		}  
	}  
	
	printf("Most repeated word: %s", word);  
	fclose(file);  
	return 1;
}

int removeWhiteSpace(char parsed[])
{
	FILE *filePointer;
		char filebuffer[255];
		int fileChar;
		filePointer = fopen(parsed, "r");
		if (filePointer){
			fgets(filebuffer, 255, filePointer);
			//printf("%s", filebuffer);
			fseek(filePointer, 0, SEEK_SET);
			do{
				fileChar = fgetc(filePointer);
				if(isgraph(fileChar)){
					putchar(fileChar);
				}

			}while (fileChar != EOF);
			fclose(filePointer);
		}else{
			printf("\nfile cannot be opened");
		}
		return 1;
}

int showUncommented(char parsed[])
{
	FILE *mfile;
	int counter = 0, i, j;
	char line[200],c;
	// Open file
	mfile = fopen(parsed, "r");
	if (mfile == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}
	// Extract characters from file and store in character c
	for (c = getc(mfile); c != EOF; c = getc(mfile))
		if (c == '\n') // Increment count if this character is newline
			counter = counter + 1;
	fclose(mfile);
	//FILE *mfile;
	mfile = fopen(parsed, "r");
	fgets(line, 200, mfile);
	printf("first line %s\n", line);
	//while (line != EOF || feof(mfile))
	for ( i = 0; i < counter; i++)
	
	{
		if (line[0] != '#')
			printf("%s", line);;
		fgets(line, 200, mfile);
	}
	fclose(mfile);
	return 1;
}
// Function to execute builtin commands
int ownCmdHandler(char** parsed)
{
	int NoOfOwnCmds = 9, i, switchOwnArg = 0;
	char* ListOfOwnCmds[NoOfOwnCmds];
	char* username;

	ListOfOwnCmds[0] = "exit";
	ListOfOwnCmds[1] = "cd";
	ListOfOwnCmds[2] = "help";
	ListOfOwnCmds[3] = "hello";
	ListOfOwnCmds[4] = "head";
	ListOfOwnCmds[5] = "rws";
	ListOfOwnCmds[6] = "nl";
	ListOfOwnCmds[7] = "suc";
	ListOfOwnCmds[8] = "mfw";

	for (i = 0; i < NoOfOwnCmds; i++) {
		if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
			switchOwnArg = i + 1;
			break;
		}
	}

	switch (switchOwnArg) {
	case 1:
		printf("\nGoodbye\n");
		exit(0);
	case 2:
		chdir(parsed[1]);
		return 1;
	case 3:
		openHelp();
		return 1;
	case 4:
		username = getenv("USER");
		printf("\nHello %s.\nMind that this is "
			"not a place to play around."
			"\nUse help to know more..\n",
			username);
		return 1;
	case 5: 
		if (head(parsed[1])) return 1;
		else return 0;
	case 6:
		if (removeWhiteSpace(parsed[1])) return 1;
		else return 0;
	case 7:
		if(numOfLines(parsed[1])) return 1;
		else return 0;
	case 8:
		if(showUncommented(parsed[1]))	return 1;
		else return 0;
	case 9:
		if(mostFrequentWord(parsed[1]))	return 1;
		else return 0;
	default:
		break;
	}

	return 0;
}

// function for finding pipe
int parsePipe(char* str, char** strpiped)
{
	int i;
	for (i = 0; i < 2; i++) {
		strpiped[i] = strsep(&str, "|");
		if (strpiped[i] == NULL)
			break;
	}

	if (strpiped[1] == NULL)
		return 0; // returns zero if no pipe is found.
	else {
		return 1;
	}
}

// function for parsing command words
void parseSpace(char* str, char** parsed)
{
	int i;

	for (i = 0; i < MAXLIST; i++) {
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			i--;
	}
}

int processString(char* str, char** parsed, char** parsedpipe)
{

	char* strpiped[2];
	int piped = 0;

	piped = parsePipe(str, strpiped);

	if (piped) {
		parseSpace(strpiped[0], parsed);
		parseSpace(strpiped[1], parsedpipe);

	} else {

		parseSpace(str, parsed);
	}

	if (ownCmdHandler(parsed))
		return 0;
	else
		return 1 + piped;
}

int main()
{
	char inputString[MAXCOM], *parsedArgs[MAXLIST];
	char* parsedArgsPiped[MAXLIST];
	int execFlag = 0;
	init_shell();

	while (1) {
		// print shell line
		printDir();
		// take input
		if (takeInput(inputString))
			continue;
		// process
		execFlag = processString(inputString,
		parsedArgs, parsedArgsPiped);
		// execflag returns zero if there is no command
		// or it is a builtin command,
		// 1 if it is a simple command
		// 2 if it is including a pipe.

		// execute
		if (execFlag == 1)
			execArgs(parsedArgs);

		if (execFlag == 2)
			execArgsPiped(parsedArgs, parsedArgsPiped);
	}
	return 0;
}
