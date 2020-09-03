#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h> 
#include <unistd.h> 
#include<string.h>
#include <fcntl.h>

int childFunction(char *line, ssize_t read);
char* encode(char* str);

int main(){
	/*
		This program uses system calls like fork, wait, open, read, close and write, 
		for creating the file named codes.txt and storing the inverted sentence in it and printing out
		that inverted sentence on the terminal.
	*/
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int status;
	int pid;
	FILE *file;
	char stringList;

	printf("\nThis program encodes text. To stop the infinite loop press ctrl-c (^C)\n");

	while(1){
		printf("Enter a scentence:- ");
		read = getline(&line, &len, stdin);
	// printf("%zd\n", read);
		pid = fork();
		if(pid > 0){
			printf("Created a child to perform task, waiting...\n");
			wait(&status);
			if(WEXITSTATUS(status)==10){
				printf("Empty line");
			}else{
				file = fopen("codes.txt", "r");
				printf("The FILE contains:-");
				while((stringList = fgetc(file)) != EOF){
					printf("%c", stringList);
				}
			}
		}else{
			childFunction(line, read);
		}
		printf("\n");
	}
	
	fclose(file);
		
}

int childFunction(char *line, ssize_t read){
	
	printf("I am a child working for my parent\n");
	char *str;
	int file;
	
	str = encode(line);
	if(read == 1){
		exit(10);
	}else{
		file = open("./codes.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
		write(file, str, strlen(str));
	}

	exit(0);
    close(file);

}

char* encode(char* str){
	/* 
		Inverts the sentence character-wise given by the user.
	*/
	char *strreversed;
	for(int i =0 ; i<strlen(str); i++){
		strreversed[strlen(str)-i-1] = str[i];
	}
	return (strreversed);
}
