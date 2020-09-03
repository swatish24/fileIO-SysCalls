#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include <sys/types.h>
#include<string.h>

void findfile(char *file_to_find,char *path_directory);
int main(int argc,char *argv[]){

    
    char *file_name;

    /* 
       To exit and show error if the argument count is not equal to 2
       and giving a meaningful error to rectifiy the mistake of not putting 
       the name of the file to search as command line argumnet
    */

    if(argc != 2){
    	printf("Error :(Provide the file name like) %s <filename>\n", argv[0]);
    	exit(0);
    }
  
    file_name=argv[1];

    findfile(file_name, ".");
    return 0;
}

void findfile(char *file_to_find,char *path_directory){
    DIR *dp;
    struct dirent *dirp;
    char *file_name;
    char file_path[100];

    file_name = file_to_find;

    dp = opendir(path_directory);

    /*
       Reads the current directory if it's not null it will compare files in the current 
       directory with the file that we are searching for and if the file is there it prints the 
       file name with the name of directory it is inside and if its not in the the current 
       directory it searches in the subdirectory.
    */
    while((dirp = readdir(dp)) != NULL){
        if(!strcmp(dirp->d_name, file_name)){
            printf("%s %s %s%s\n", file_name,"is in",path_directory, "/ directory");
            }
        else if(strcmp(dirp->d_name, file_name)){
            if(dirp->d_type == DT_DIR){ 
                if(strcmp(dirp->d_name, ".")==0 || strcmp(dirp->d_name, "..")==0 ){
                    continue;
                }
                strcpy(file_path, path_directory);
                strcat(file_path, "/");
                strcat(file_path, dirp->d_name);
                

                findfile(file_name, file_path);

            }
            
        }

    }

    closedir(dp);
}
