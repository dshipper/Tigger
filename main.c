#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
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
	printf("Sorry you need to initialize tigger before using this command.\n");
	return 0;

}

void printUsage(){
	printf("Tigger -v: 0.18\nSorry we didn't recognize your command. Usage: tigger [COMMAND] [PARAMS] \nCommands include but are not limited to:\n\tinit\n\tnew [\"task-name\"]\n\ttasks\n\ttig\n\tcompleted\n");
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

int initialize(){
	/*This function does the following: 
	 -check to see if the current directory has a git repository in it
	 -if so add a post-commit hook to the $GIT_DIR/hooks
	 -create a .tigger file which contains all of our tasks
	 */
	if(tiggerExists()){
		return 0;
	}
	if (checkForGit()){
		//now we go in and modify the post-commit hook file to our liking
		FILE *file;
		file = fopen(".git/hooks/post-commit", "w+");
		fprintf(file, commit_hook);
		fclose(file);
		system("chmod 744 .git/hooks/post-commit");
		file = fopen(".tigger", "w+");
		fprintf(file, "BEGIN_TIGGER\n");
		fclose(file);
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
	if(!tiggerExists()){
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

int completedTasks(){
	/*This function does the following:
	 -open up the .tigger_completed file
	 -print out all of the tasks in the .tigger_completed file
	 -close the .tigger_completed file
	 */
	char line[255];
	int count = 0;
	if(!tiggerExists()){
		return 0;
	}
	FILE *file = fopen(".tigger_completed", "rt");
	printf("\nLoading completed tasks from tigger...\n-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
	while(fgets(line, 255, file) != NULL){
		if(!protectedText(line)){
			count += 1;
			printf("Task %d: \n", count);
			printf(trimwhitespace(line));
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

int processCommand(char *args[]){
	if(args[1] != NULL){
		if(!strcmp(args[1], "init")){
			printf("Initializing Tigger in the current directory.\n");
			return initialize();
		}else if(!strcmp(args[1], "new")){
			return addTask(args);
		}else if(!strcmp(args[1], "tasks")){
			return listTasks();
		}else if(!strcmp(args[1], "tig")){
			printf(tigger);
			return 1;
		}else if(!strcmp(args[1], "completed")){
			return completedTasks();
		}
	}
	return 0;
}




void loadCommands(){
	commands[0] = "init";
	commands[1]	 = "new";
	commands[2] = "tasks";
	commands[3] = "tig";
	commands[4] = "completed";
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
