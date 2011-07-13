objects := main.o     
PREFIX := /usr/local/bin
autogen := post_commit_hook.h

default: tigger

install: tigger rubydeps
	@echo "Copying Tigger into /usr/local/bin"
	@echo "Please ensure the /usr/local/bin is in your path!"
	cp tigger $(PREFIX) 
	@echo "Finished. Tigger is installed. Type 'tigger' for usage."

rubydeps:
	@echo "Installing Ruby dependency Grit"
	@echo "Note that Ruby must be installed for this to work"
	gem install grit                                         

tigger : $(autogen) $(objects)
	@echo "Linking source files..."
	cc -o $@ $(objects) -ljansson       

post_commit_hook.h : post_commit_hook.rb
	@echo "Generating commit_hook header"
	./rb2h.rb POST_COMMIT_HOOK

main.o : tigger_util.h main.c
	@echo "Installing Tigger....."
	cc -Wall -c main.c 

clean :
	rm edit $(objects) $(generated_dependencies)
