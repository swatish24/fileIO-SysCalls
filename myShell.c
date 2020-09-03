#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>

#define MAXLINE_LEN 300

int main(int argc, char *argv[]){
	/* 
		Program that acts like your own basic shell which
		will process single or multiple commands entered by the user
		for example ls, it will list directory contents.
	*/

	while(1){
		char strLine[MAXLINE_LEN];
		pid_t pid; 
		int status;
		
		printf("$>> ");
		char *line = fgets(strLine, MAXLINE_LEN, stdin);
		
		strLine[strlen(strLine)-1] = '\0';
		
		if( !strcasecmp(strLine, "exit") || line == NULL ){
			printf("Bye Bye\n");
			exit(0);
		}
		
		char *tokencmd = strtok(strLine, ";");
		
		while(tokencmd){
			pid = fork();
			if (pid<0){
				perror("Something went wrong\n");
				exit(1);
			}
			
			if( pid > 0 ){
				wait(&status);
				printf("child process finished pid= %d and status= %d\n", pid, WEXITSTATUS(status));
				
			}else{
				while(1){
					system(tokencmd);
					printf("\n");
					sleep(1);
					
					exit(EXIT_SUCCESS);
				}
			}
			tokencmd = strtok(NULL,";");
		}
		
	}
	return 0;
}