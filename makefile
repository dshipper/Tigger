objects = main.o     
tigger : $(objects)
	@echo "Linking source files..."
	cc -o tigger $(objects)       
	@echo "Installing Ruby dependency Grit"
	@echo "Note that Ruby must be installed for this to work"
	gem install grit                                         
	@echo "Copying Tigger into /usr/bin"
	@echo "Please ensure the /usr/bin is in your path!"
	cp tigger /usr/bin                                
	@echo "Finished. Tigger is installed. Type 'tigger' for usage."

main.o : main.c tigger_util.h
	@echo "Installing Tigger....."
	cc -c main.c                     

clean :
	rm edit $(objects)