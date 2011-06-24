#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>    
#include <time.h>
#include "tigger_util.h"

char *trimwhitespace(char *str)
{
	char *end;

	// Trim leading space
	while(isspace(*str)) str++;

	if(*str == 0)  // All spaces?
		return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace(*end)) end--;

	// Write new null terminator
	*(end+1) = 0;

	return str;
}

int tiggerExists(){
	FILE * file = fopen(".tigger", "r");
	if(file){        
		fclose(file);        
		return 1;    
	}    
	// printf("Sorry you need to initialize tigger before using this command.\n");
	return 0;

}

void printUsage(){
	printf("Tigger -v: 0.21\nSorry we didn't recognize your command. Usage: tigger [COMMAND] [PARAMS] \nCommands include but are not limited to:\n\tinit\n\tnew [\"task-name\"]\n\ttasks\n\ttig\n\tcompleted\n\tdelete [\"task-name\"]\n\ttoday\n");
}

int isCommand(char *command){
	int i;
	for (i = 0; i < COMMAND_SIZE; i++){
		if(command && !strcmp(command, commands[i])){
			return 1;
		}
	}
	return 0;
}

int checkForGit(){
	DIR *dp;
	struct dirent *ep;

	dp = opendir ("./");
	if (dp != NULL)
    {
		while ((ep = readdir(dp))){
			if(!strcmp(ep->d_name, ".git")){
				printf("Found Git repo....\n");
				return 1;
			}
		}
	}
	else{
		printf("Could not open directory. Please try again later.");
		return 0;
	}
	printf("Could not find git repository. Please make sure git is initialized in this directory and then try again.\n");
	return 0;
}

int initialize(char *args[]){
	/*This function does the following: 
	 -check to see if the current directory has a git repository in it
	 -if so add a post-commit hook to the $GIT_DIR/hooks
	 -create a .tigger file which contains all of our tasks
	 */
	if(tiggerExists()){  
		if (args[2] == NULL || strcmp("-f",args[2]) != 0){
			printf("Tigger has already been initialized in this directory.\n");
			printf("Reinitializing will overwrite all of your current tasks.\n");
			printf("If you really want to reinitialize, you can use the -f flag after tigger init.\n\n");
			return 0; 
		}                           
	}
	if (checkForGit()){
		//now we go in and modify the post-commit hook file to our liking 
		FILE *file;
		file = fopen(".git/hooks/post-commit", "w");
		fprintf(file, commit_hook);
		fclose(file);
		system("chmod 744 .git/hooks/post-commit");
		file = fopen(".tigger", "w");
		fprintf(file, "BEGIN_TIGGER\n");
		fclose(file);  
		system("git add .tigger");
		file = fopen(".tigger_completed", "w"); \
		fclose(file);                            
		system("git add .tigger_completed");
		printf("Done.\n");
		return 1;
	}else{
		return 0;
	}
	return 0;
}



int addTask(char *args[]){
	/*This function does the following:
	 -open up the .tigger file
	 -write the task to the .tigger file
	 -close the .tigger file
	 */
	if(!tiggerExists(args)){
		return 0;
	}
	if(args[2]){
		if(strlen(args[2]) < 255){
			FILE *file = fopen(".tigger", "a+");
			fprintf(file, args[2]);
			fprintf(file, "\n");
			fclose(file);
			printf("Just added new task to tigger.\n");
			printf(args[2]);
			printf("\n");
			return 1;
		}else{
			printf("Sorry you must enter a description that is less than 255 characters long.\n");
			return 0;
		}

	}else{
		printUsage();
		return 0;
	}
}

int protectedText(char line[255]){
	if(!strcmp(line, "BEGIN_TIGGER\n")){
		return 1;
	}else{
		return 0;
	}
}

int listTasks(){
	/*This function does the following:
	 -open up the .tigger file
	 -print out all of the tasks in the .tigger file
	 -close the .tigger file
	 */
	char line[255];
	int count = 0;
	if(!tiggerExists()){
		return 0;
	}
	FILE *file = fopen(".tigger", "rt");
	printf("\nLoading tasks from tigger...\n-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
	while(fgets(line, 255, file) != NULL){
		if(!protectedText(line)){
			count += 1;
			printf("Task %d: \n", count);
			printf(trimwhitespace(line));
			printf("\n");

		}
	}
	if (count > 0){
		printf("You have %d tasks waiting to be completed.\n", count);
		printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");

	}else{
		printf("Yay! You have no tasks remaining. Go have a beer.\n");
	}
	fclose(file);
	return 1;
}    

int tiggerToday(){                                           
	int count = 0;
	char * found;
	char * delim = "<?TIG?>"; 
	char line[255];
	char stime[10]; 
	int itime = 0;
	FILE *file = fopen(".tigger_completed", "r");             
	while(fgets(line, 255, file) != NULL){
		if(!protectedText(line)){     
			found = strstr(line, delim); 
			int place = found-line;
			strncpy(stime, line, place);
			itime = atoi(stime);
			if(itime > (time(NULL) - 86400)){
				count += 1; 
			}
		}
	}
	printf("%d tasks have been completed today.\n", count);
}
     

int completedTasks(){
	/*This function does the following:
	 -open up the .tigger_completed file
	 -print out all of the tasks in the .tigger_completed file
	 -close the .tigger_completed file
	 */
	char line[255];
	int count = 0; 
	char * delim = "<?TIG?>";
	char * found;   
	size_t index;  
	char *new_string;
	if(!tiggerExists()){
		return 0;
	}
	FILE *file = fopen(".tigger_completed", "rt");
	printf("\nLoading completed tasks from tigger...\n-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
	while(fgets(line, 255, file) != NULL){
		if(!protectedText(line)){
			count += 1;    
			found = strstr(line, delim);
			if(found != NULL){
				index = found - line;
			}  
			new_string = &line[index+7];
			printf("Task %d: \n", count);
			printf(trimwhitespace(new_string));
			printf("\n");

		}
	}
	if (count > 0){
		printf("You have completed %d tasks. Congrats!\n", count);
		printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");

	}else{
		printf("You haven't completed any tasks and are lazy. That is all.\n");
	}
	fclose(file);
	return 1;

} 


int deleteTask(char * task){ 
	char line[255];
	const char *TIGGER_FILE_NAME = ".tigger";
	const char *TIGGER_TEMP = ".tigger_temp";
	int found = 0;
	if(task == NULL){
		printf("Can't delete a null task.\n");
		return 0;
	}     
	FILE *file = fopen(TIGGER_FILE_NAME, "r");
	FILE *temp = fopen(TIGGER_TEMP, "w");                                                                      
	while(fgets(line, 255, file) != NULL){
		if(strcmp(trimwhitespace(line), trimwhitespace(task)) != 0){
			fprintf(temp, line);
			fprintf(temp, "\n");  
		}else{
			found = 1;
		}
	}
	fclose(file);
	fclose(temp);
	if(found){
		printf("We found your task and deleted it.\n");
		system("rm .tigger");
		rename(TIGGER_TEMP, TIGGER_FILE_NAME);  
	}else{
		system("rm .tigger_temp");
		printf("Sorry we couldn't find the task to delete.\n");
		return 0;
	}
}

int processCommand(char *args[]){
	if(args[1] != NULL){
		if(!strcmp(args[1], "init")){
			printf("Initializing Tigger in the current directory.\n");
			return initialize(args);
		}else if(!strcmp(args[1], "new")){
			return addTask(args);
		}else if(!strcmp(args[1], "tasks")){
			return listTasks();
		}else if(!strcmp(args[1], "tig")){
			printf(tigger);
			return 1;
		}else if(!strcmp(args[1], "completed")){
			return completedTasks();
		}else if(!strcmp(args[1], "delete")){
			return deleteTask(args[2]);
		}else if(!strcmp(args[1], "today")){
			tiggerToday();   
			return 1;
		}
	}
	return 0;
}




void loadCommands(){
	commands[0] = "init";
	commands[1]	= "new";
	commands[2] = "tasks";
	commands[3] = "tig";
	commands[4] = "completed";
	commands[5] = "delete"; 
	commands[6] = "today";
}

int main (int argc, char * argv[]) {
	loadCommands();
	if(argv[1] && isCommand(argv[1])){
		//then we want to process the command
		if (!processCommand(argv)){
			printf("Your command was not processed.\n");
		}
	}else{
		printUsage();
	}
    return 0;
}
