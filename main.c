#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

char * commit_hook = "#!/usr/bin/env ruby \n"

"require 'grit' \n"
"include Grit \n"

"puts 'Running tigger....' \n"
"puts 'Matching tasks and commit messages.' \n"

"repo = Repo.new('./') \n"
"commits = repo.commits \n"

"tigger = File.new('.tigger', 'r') \n"
"tasks = Array.new \n"
"completed_tasks = Array.new \n"

"tigger.each_line { |line|  tasks << line } \n"

"tasks.each do | task | \n"
"commits.each do | commit | \n"                                                         
"if (task.strip.upcase == commit.message.strip.upcase) \n"
"completed_tasks << task \n"
"tasks.delete task \n" 
"puts('Completed task: ' + commit.message + '.')\n "
"end \n"
"end  \n"  
"end\n "

"tigger.close\n "

"tigger = File.new('.tigger', 'w') \n"

"tasks.each { |task| tigger.write task } \n"

"tigger.close  \n"

"tigger_completed = File.new('.tigger_completed', 'a+') \n"
"completed_tasks.each { |task| tigger_completed.write task } \n"
"tigger_completed.close ";

char * tigger = "Task Management is What Tiggers Do Best!\n"
"			                          _.- -.- -._     ..                                                 \n"
"			                             .;;'  .oe$$$eeu.. ,?;UU.                                        \n"
"   		                          ,+'!!  e$$$$$$$R$$$$x ?xd$)                                        \n"
"			                        ,'  !~ u$$$$F,$$$by,?$'e $F'        _ -                              \n"
"			              .,;,.   ,dm  :! $$$$$$d( )$( )?d$F       _ -       _                           \n"
"			             !?????X!!!!~!!!X!.'?????$$$F'.:::::::   -   .  - ~                              \n"
"			             +$$$$$m@`!!   ~? `!kCCU$$$$ ::::::::: g~  ~ -  _                                \n"
"			              '$BeCeW$:`~..__~x W$$$$$$$e `:::::'.$F           ~                             \n"
"			                '****'      ,``~~?$:=$$$$$$epppe$F`                                          \n"
"			                        , '   ,    ?W.''??$$FFF' *.                                          \n"
"			                      '     .     . ?$$e. ==+* ..$f                                          \n"
"			                   '     . '      H!.?$$$$$$$$$$$f                                           \n"
"			                      . '        !!!! ?$$$$$$$$$$                                            \n"
"			                             . ~!!!!!? ?$$$$$$$f.                                            \n"
"			                         . '     !!!!~*..****C.-!:..                                         \n"
"			                  . -  ~!!!:.    ?!!~.$$$$$$$$$$.!!!!:` .                                    \n"
"			             .- ~!::.    !!!!!.  ?X e$$$$$$$$$$$$.`!!!   .! - _                              \n"
"			         . `~!?: ~!!!!!  !!!!!!!!! $$$$$$$$$$$$$$$  !!   !!     !?                           \n"
"			        '      !!:!!!!!!!!!!!!!!!`:$$$$$$$$$$$$$$$U ~ :!!!!    !!~ `                         \n"
"			     .:::::...  !!!!!!!!~~~~!!!!X $$$$$$$$$$$$$$$$$  !!!!!...:&lt;~`   `                     \n"
"			    +   ~~!!!!!!!!~~     ::!!!!!':$$$$$$$$$$$$$$$$$~ *~~!!!!*`     .:!                       \n"
"			   ::::::::!!!!          '`~~!!~ *""$$$$$$$$$$$$$$$~       !!!!!!!!!``                       \n"
"			  ,'`~~!!!!!!~           :        u$$$$$$$$$$$$$$$$~       !!!!``'   ;                       \n"
"			 . .... ~!!!             .   ..+ $$$$$$$$$$$$$$$$$$~      .!!!!!!?:::-                       \n"
"			 !!!!!!!!!!!!::::+       !!~~~~~ **''$$$$$$$$$$$$$*    .+!!!!!!!!(  ,                        \n"
"			;!!!!!!!!!!!!!!!~        !!!::.. ue$$$$$$$$$$$$$$$~ !!!!!!!!!!!!!!!!                         \n"
"			!!!!!!!!!!!``            ~!!!!!! $$$$$$$$$$$$$$$$$     !!!!!!!!!!!!                          \n"
"			!!!!!!!!!!!             .   `~~! $$$$$$$$$$$$$$$$`    :!!!!!!!!!!X`                          \n"
"			~!!!!!!!!!!             ....::!! $$$$$$$$$$$$$$$$     !!!!!!!!!!~                            \n"
"			 `~!!!!!!!!             !!!!!!!!m$$$$$$$$$$$$$$$      !!!!!!!*`                              \n"
"			   `*~X!~*              !!!!!!!*:$$$$$$$$$$$$$$~      ``((`                                  \n"
"			                      :!!::   ` '?I$$$$$$$$$$$`                                              \n"
"			                      `~!!!!!- e$$$$$$$$$$$$$~                                               \n"
"			                   '     `*~! $$$$$$$$$$$$$$' .                                              \n"
"			                .:!:.     .: e$$$$$$$$$$$$$' ~  `                                            \n"
"			              '    `~!!!!!!~:$$$$$$$$$$$$* :*    :!       ......                             \n"
"			           ::::::..   ~!!!` $$$$$$$$$$$$':!~  :!!` `  .!!!!!!!!!!                            \n"
"			          -~!!!!!!!!::..!! 8$$$$$$$$$$*.!!!..!!~ ..- :!!!!!!!~!!!~                           \n"
"			        '     '~~!!!!!!!!! #$$$$$$$$*(!!!!!!!!!.+!~ :!!!!!~`- -`!                            \n"
												  "			      ;            `!!!!!!!.'*$$**' `````'`!!!!!!! !!!!!~                                    \n"
												  "			                ..  .!!!!!~~`               `!!!!`:!!!`        '                             \n"
												  "			      `.:!!!!!!!!!!!!!!~:                     !!!!!!!~       '                               \n"
												  "			       ~!!!!!!!~~`~!!!!!!:::                  ~!!!!!!      '                                 \n"
												  "			                .:!!!!!!!!!!!!:                `!!!!!_  '                                    \n"
												  "			              :::::::!?!!!!!!!!!                                                             \n"
												  "			           :!!!!!!!!!!!!!!!!!!~                                                              \n"
												  "			           `~!!!!!!!!!!!!!~~                                                                 \n";


typedef char * string;

const int COMMAND_SIZE = 4;
string commands[4];

int tiggerExists(){
	FILE * file = fopen(".tigger", "r");
	if(file){        
		fclose(file);        
		return 1;    
	}    
	return 0;

}

void printUsage(){
	printf("Tigger -v: 0.11\nSorry we didn't recognize your command. Commands include:\n\t-init\n\t-new \"task-name\"\n\t-tasks\n\t-tig\n");
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
		printf("Sorry tigger has already been initialized.\n");
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
		printf("Sorry you need to initialize tigger before using this command.\n");
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
		printf("Sorry tigger has already been initialized.\n");
		return 0;
	}
	FILE *file = fopen(".tigger", "rt");
	printf("\nLoading tasks from tigger...\n--------------------------------------------------------------\n--------------------------------------------------------------\n\n");
	while(fgets(line, 255, file) != NULL){
		if(!protectedText(line)){
			count += 1;
			printf("Task %d: \n", count);
			printf(line);
			printf("\n");
			
		}
	}
	if (count > 0){
		printf("\n--------------------------------------------------------------\n--------------------------------------------------------------\n");
		printf("You have %d tasks waiting to be completed.\n", count);
	}else{
		printf("Yay! You have no tasks remaining. Go have a beer.\n");
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
		}
	}
	return 0;
}




void loadCommands(){
	commands[0] = "init";
	commands[1]	 = "new";
	commands[2] = "tasks";
	commands[3] = "tig";
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
