objects = main.o
generated_dependencies = post_commit_hook.h

tigger : $(generated_dependencies) $(objects)
	@echo "Linking source files..."
	cc -o tigger $(objects)       
	# @echo "Copying Tigger into homebrew's path"
	# cp tigger /usr/bin                                
	@echo "Finished. Tigger is installed. Type 'tigger' for usage."

post_commit_hook.h : post_commit_hook.rb
	@echo "Generating commit_hook header"
	./rb2h.rb POST_COMMIT_HOOK

main.o : tigger_util.h main.c
	@echo "Installing Tigger....."
	cc -c main.c                     

clean :
	rm edit $(objects) $(generated_dependencies)
