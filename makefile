objects = main.o     
tigger : $(objects)
	cc -o tigger $(objects)

main.o : main.c tigger_util.h
	echo "Starting Tigger installation..."
	cc -c main.c                         
	echo "Compiled source files..."
	echo "Copying Tigger into /usr/bin"
	cp tigger /usr/bin            
	echo "Installing Ruby dependencies...."  
	gem install grit                       
	@echo Finished. For usage type 'tigger'
	
	
	
clean :
	rm edit $(objects)  
	
finish:
