objects = main.o     
tigger : $(objects)
	@echo "Linking source files..."
	cc -o tigger $(objects)       
	# @echo "Copying Tigger into homebrew's path"
	# cp tigger /usr/bin                                
	@echo "Finished. Tigger is installed. Type 'tigger' for usage."

main.o : main.c tigger_util.h
	@echo "Installing Tigger....."
	cc -c main.c                     

clean :
	rm edit $(objects)
